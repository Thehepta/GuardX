package com.hepta.guardx;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.GuardedBy;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;


public class SshdService extends Service {


    static final String SERVICE_UI_REQUEST = "ServiceUIRequest";

    private static final String TAG = "SshdService";
    private boolean runInForeground = true;

    private String bindAddress = "2222";
    private static final String[] Z_STRING = new String[0];
    private static final Pattern CMD_OPTIONS_PATTERN = Pattern.compile(
            "\\S*\"([^\"]*)\"\\S*|(\\S+)");
    private static final Object lock = new Object();
    private static final int MIN_DURATION_MS = 10_000;
    private static final ExecutorService EXECUTOR_SERVICE = Executors.newSingleThreadExecutor();

    @GuardedBy("lock")
    private int sshdPid;
    @GuardedBy("lock")
    private long sshdStartTime;
    @GuardedBy("lock")
    private long sshdDuration;

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }




    static ComponentName startService( @NonNull final Context context) throws IllegalStateException {
        Intent intent = new Intent(context, SshdService.class);
        return context.getApplicationContext().startService(intent);
    }


    /**
     * Start the sshd process.
     *
     * @param intent The Intent supplied to Context.startService, as given.
     *               This may be null if the service is being restarted after
     *               its process has gone away.
     *               ==> Reminder: do NOT use for config data...
     */
    @Override
    public int onStartCommand(@Nullable final Intent intent,
                              final int flags,
                              final int startId) {
        Log.d(TAG + "|onStartCommand", "ENTER");
        startSshd();
        if (runInForeground) {
            final List<String> ipList = SshdSettings.getHostAddresses(3);
            if (ipList.isEmpty()) {
                throw new IllegalStateException();
            }

            final String s;
            if (ipList.size() > 1) {
                s = ipList.stream()
                        .collect(Collectors.joining(",", "[", "]"));
            } else {
                s = ipList.get(0);
            }

        }

        // If we (i.e. this service, which is != this sshd process) get killed,
        // after returning from here, restart
        return START_STICKY;
    }

    private void startSshd() {

        Log.d(TAG + "|startSshd", "ENTER");

        stopSshd();

        // See all options: cpp/dropbear/svr-runopts.c
        final List<String> argList = new ArrayList<>();
        argList.add("sshd");
        // Pass on the android system environment to the child process which allows
        // utilities like am (activity manager) and pm (package manager) to run,
        argList.add("-e");
        // Create host keys as required
        argList.add("-R");
        // Don't fork into background
        argList.add("-F");
        // Bind to [address:]port
        argList.add("-p");
        argList.add(Prefs.getPort(getApplicationContext()));
        // edit dropbear/config.h, add:  #define DEBUG_TRACE 1
        // before enabling the next line
//        args.add("-v");

        final Matcher matcher = CMD_OPTIONS_PATTERN.matcher("");
        while (matcher.find()) {
            argList.add(matcher.group());
        }
        final String[] args = argList.toArray(Z_STRING);

        final String confPath = SshdSettings.getDropbearDirectory(this).getPath();
        final String homePath = getFilesDir().getPath();

        String  shellCmd = Prefs.DEFAULT_SHELL;


        final String env =  "";


        final int pid = start_sshd(getApplicationInfo().nativeLibraryDir,
                args, confPath, homePath, shellCmd, env,
                true,
                true);
            Log.d(TAG + "|startSshd", "start_sshd=" + pid);

        if (pid == -1) {
            // utter failure to start
            synchronized (lock) {
                sshdPid = 0;
            }
        } else {
            synchronized (lock) {
                sshdPid = pid;
            }

            // Start a watchdog thread which will restart sshd should it die.
            EXECUTOR_SERVICE.execute(() -> {
                Log.d(TAG + "|startSshd", "waitpid=" + pid);

                synchronized (lock) {
                    final long now = System.nanoTime();
                    if (sshdStartTime == 0) {
                        // This is a 'first' start
                        sshdDuration = 0;
                    } else {
                        // It's a restart; remember how long since the last start
                        sshdDuration = now - sshdStartTime;
                    }
                    sshdStartTime = now;
                }

                // Pause until the dropbear process changes state
                waitpid(pid);

                final boolean failed;
                final boolean restart;
                synchronized (lock) {
                    failed = (sshdPid == pid);
                    if (failed) {
                        sshdPid = 0;
                        restart =
                                // 'first' start failed
                                sshdDuration == 0
                                        // or the 'previous' attempt ran for more than the minimum
                                        || sshdDuration >= MIN_DURATION_MS
                                        // or the 'current' attempt ran for more than the minimum
                                        || (System.currentTimeMillis() - sshdStartTime)
                                        >= MIN_DURATION_MS;
                        // i.e. do not restart if we failed twice in less than the minimum time.

                    } else {
                        // The process was stopped by request
                        restart = false;
                    }
                }

//                if (restart) {
//                    startSshd();
//                } else if (failed) {
//                    // not restarting and failed
//                    updateUI();
//                }
            });
        }

        updateUI();
    }


    private void updateUI() {
        final Intent intent = new Intent(SERVICE_UI_REQUEST);
        LocalBroadcastManager.getInstance(this).sendBroadcast(intent);
    }

    private void stopSshd() {
        synchronized (lock) {
            final int pid = sshdPid;
            sshdPid = 0;
            if (pid > 0) {
                    Log.d(TAG + "|stopSshd", "killing pid=" + pid);
                kill(pid);
            }
        }
        updateUI();
    }


    private native int start_sshd(@NonNull String lib,
                                  @NonNull String[] dropbearArgs,
                                  @NonNull String confPath,
                                  @NonNull String homePath,
                                  @NonNull String shell,
                                  @NonNull String env,
                                  boolean enablePublickeyAuth,
                                  boolean enableSingleUsePasswords);
    private native int waitpid(int pid);
    private native void kill(int pid);

}
