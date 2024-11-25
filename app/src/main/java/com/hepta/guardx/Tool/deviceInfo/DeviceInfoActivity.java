package com.hepta.guardx.Tool.deviceInfo;


import android.os.Bundle;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.chad.library.adapter4.BaseQuickAdapter;
import com.hepta.guardx.Tool.ClassCheckItem;
import com.hepta.guardx.Tool.ClassLoaderListItem;
import com.hepta.guardx.Tool.DeviceInfoItem;
import com.hepta.guardx.Tool.MountItem;
import com.hepta.guardx.Tool.OpenDeepLinkItem;
import com.hepta.guardx.Tool.RunningAppItem;
import com.hepta.guardx.Tool.SShdItem;
import com.hepta.guardx.Tool.SoInfoCheckItem;
import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.base.ItemInfoBean;
import com.hepta.guardx.Tool.base.RecyclerViewInfoAdapter;
import com.hepta.guardx.databinding.ActivityToolsBinding;

import java.util.ArrayList;

public class DeviceInfoActivity extends AppCompatActivity {

    ArrayList<ItemInfoBean> itemBeans = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityToolsBinding binding = ActivityToolsBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        binding.rvList.setLayoutManager(new LinearLayoutManager(this));
        RecyclerViewInfoAdapter adapter = new RecyclerViewInfoAdapter(itemBeans);
        binding.rvList.setAdapter(adapter);
        adapter.setOnItemClickListener(new BaseQuickAdapter.OnItemClickListener<ItemInfoBean>() {
            @Override
            public void onClick(@NonNull BaseQuickAdapter<ItemInfoBean, ?> baseQuickAdapter, @NonNull View view, int i) {
                baseQuickAdapter.getItem(i).ItemHandle(getApplicationContext());
            }
        });

        itemBeans.add(new MRDID());
        itemBeans.add(new OAID());
    }

    /**
     * A native method that is implemented by the 'guardx' native library,
     * which is packaged with this application.
     */
}