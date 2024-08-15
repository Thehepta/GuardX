package com.hepta.guardx.Tool;


import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.hepta.guardx.SshdActivity;
import com.hepta.guardx.Tool.ItemBean;

public class SShdItem extends ItemBean {


    public SShdItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        Intent intent = new Intent(context, SshdActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
    }
}
