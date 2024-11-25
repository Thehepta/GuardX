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


public class RecyclerViewCardAdapter extends BaseQuickAdapter<ItemCardBean, QuickViewHolder> {

    public RecyclerViewCardAdapter(@Nullable List<ItemCardBean> data){
        super(Objects.requireNonNull(data));
    }
    @NonNull
    @Override
    protected QuickViewHolder onCreateViewHolder(@NonNull Context context, @NonNull ViewGroup viewGroup, int i) {
        return new QuickViewHolder(R.layout.item_card_view,viewGroup);
    }
    @Override
    protected void onBindViewHolder(@NonNull QuickViewHolder viewHolder, int i, @Nullable ItemCardBean itemBean) {
        viewHolder.setText(R.id.text1, itemBean.getMsg());
    }

}

