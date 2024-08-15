package com.hepta.guardx;

import androidx.annotation.NonNull;

public class DropbearUtil {

    static {
        System.loadLibrary("customSshd");
    }


    static native int start_sshd(@NonNull String lib,
                                 @NonNull String[] dropbearArgs,
                                 @NonNull String confPath,
                                 @NonNull String homePath,
                                 @NonNull String shell,
                                 @NonNull String env,
                                 boolean enablePublickeyAuth,
                                 boolean enableSingleUsePasswords);
    static native int waitpid(int pid);
    static native void kill(int pid);

    public static native void mountTest();
}
