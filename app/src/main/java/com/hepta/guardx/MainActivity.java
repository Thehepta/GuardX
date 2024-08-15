package com.hepta.guardx;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.hepta.guardx.Tool.ToolsActivity;
import com.hepta.guardx.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {



    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        Button btn = binding.sampleText;
        btn.setText("start sshd");
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), ToolsActivity.class);
                startActivity(intent,null);
            }
        });
    }

    /**
     * A native method that is implemented by the 'guardx' native library,
     * which is packaged with this application.
     */
}