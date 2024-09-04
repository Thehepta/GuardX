package com.hepta.guardx.Tool;


import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.chad.library.adapter4.BaseQuickAdapter;
import com.hepta.guardx.databinding.ActivityToolsBinding;
import java.util.ArrayList;

public class ToolsActivity extends AppCompatActivity {

    ArrayList<ItemBean> itemBeans = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityToolsBinding binding = ActivityToolsBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        binding.rvList.setLayoutManager(new LinearLayoutManager(this));
        RecyclerViewAdapter adapter = new RecyclerViewAdapter(itemBeans);
        binding.rvList.setAdapter(adapter);
        adapter.setOnItemClickListener(new BaseQuickAdapter.OnItemClickListener<ItemBean>() {
            @Override
            public void onClick(@NonNull BaseQuickAdapter<ItemBean, ?> baseQuickAdapter, @NonNull View view, int i) {
                baseQuickAdapter.getItem(i).ItemHandle(getApplicationContext());
            }
        });

        itemBeans.add(new SShdItem("sshd"));
        itemBeans.add(new MountItem("mount"));
        itemBeans.add(new ClassCheckItem("className check"));
        itemBeans.add(new SoInfoCheckItem("soInfo check"));
        itemBeans.add(new ClassLoaderListItem("ClassLoader check"));
    }

    /**
     * A native method that is implemented by the 'guardx' native library,
     * which is packaged with this application.
     */
}