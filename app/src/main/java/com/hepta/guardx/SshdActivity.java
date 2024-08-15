package com.hepta.guardx;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ScrollView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;

import com.hepta.guardx.databinding.ActivitySshdBinding;

import java.util.List;

public class SshdActivity extends AppCompatActivity {



    // Used to load the 'guardx' library on application startup.
    static {
        System.loadLibrary("jni-dropbear");
    }

    private ServiceViewModel vm;
    private ActivitySshdBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivitySshdBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        vm = new ViewModelProvider(this).get(ServiceViewModel.class);
        vm.onLogUpdate().observe(this, output -> {
            // We always replace the WHOLE content. TODO: receive and append updates only
            binding.log.setText(String.join("\n", output));
            binding.logScroller.post(() -> binding.logScroller.fullScroll(ScrollView.FOCUS_DOWN));
        });


    }




    @Override
    public void onResume() {
        super.onResume();
        vm.startService(getApplicationContext());
        populateNetworkAddressList();
    }

    private void populateNetworkAddressList() {
        // limit 3... assuming a max of 1 mobile + 1 wifi + 1 eth
        final List<String> ipList = SshdSettings.getHostAddresses(3);
        if (ipList.isEmpty()) {
            // should never happen... flw
            binding.ip.setText(R.string.err_no_ip);
        } else {
            binding.ip.setText(String.join("\n", ipList));
            //noinspection ConstantConditions
            binding.port.setText(Prefs.getPort(getApplicationContext()));
        }
    }

    /**
     * A native method that is implemented by the 'guardx' native library,
     * which is packaged with this application.
     */
}