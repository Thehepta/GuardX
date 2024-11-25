package com.hepta.guardx.Tool;


import android.os.Bundle;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.chad.library.adapter4.BaseQuickAdapter;
import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.base.RecyclerViewCardAdapter;
import com.hepta.guardx.databinding.ActivityToolsBinding;
import java.util.ArrayList;

public class ToolsActivity extends AppCompatActivity {

    ArrayList<ItemCardBean> itemBeans = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityToolsBinding binding = ActivityToolsBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        binding.rvList.setLayoutManager(new LinearLayoutManager(this));
        RecyclerViewCardAdapter adapter = new RecyclerViewCardAdapter(itemBeans);
        binding.rvList.setAdapter(adapter);
        adapter.setOnItemClickListener(new BaseQuickAdapter.OnItemClickListener<ItemCardBean>() {
            @Override
            public void onClick(@NonNull BaseQuickAdapter<ItemCardBean, ?> baseQuickAdapter, @NonNull View view, int i) {
                baseQuickAdapter.getItem(i).ItemHandle(getApplicationContext());
            }
        });

        itemBeans.add(new SShdItem("sshd"));
        itemBeans.add(new MountItem("mount"));
        itemBeans.add(new ClassCheckItem("className check"));
        itemBeans.add(new SoInfoCheckItem("soInfo check"));
        itemBeans.add(new ClassLoaderListItem("ClassLoader check"));
        itemBeans.add(new RunningAppItem("RunningApp check"));
        itemBeans.add(new DeviceInfoItem("DeviceInfoItem check"));
        itemBeans.add(new OpenDeepLinkItem("openDeepLink"));
        itemBeans.add(new lspltItem("lspltCheckItem"));
        itemBeans.add(new httpsProxyItem("httpsProxyItem"));

    }

    /**
     * A native method that is implemented by the 'guardx' native library,
     * which is packaged with this application.
     */
}