package com.hepta.guardx.Tool.base;


import android.content.Context;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.chad.library.adapter4.BaseQuickAdapter;
import com.chad.library.adapter4.viewholder.QuickViewHolder;
import com.hepta.guardx.R;

import java.util.List;
import java.util.Objects;


public class RecyclerViewInfoAdapter extends BaseQuickAdapter<ItemInfoBean, QuickViewHolder> {

    public RecyclerViewInfoAdapter(@Nullable List<ItemInfoBean> data){
        super(Objects.requireNonNull(data));
    }
    @NonNull
    @Override
    protected QuickViewHolder onCreateViewHolder(@NonNull Context context, @NonNull ViewGroup viewGroup, int i) {
        return new QuickViewHolder(R.layout.item_info_view,viewGroup);
    }
    @Override
    protected void onBindViewHolder(@NonNull QuickViewHolder viewHolder, int i, @Nullable ItemInfoBean itemBean) {
        viewHolder.setText(R.id.text1, itemBean.getTitle());
        viewHolder.setText(R.id.text3, itemBean.getMsg());
    }

}

