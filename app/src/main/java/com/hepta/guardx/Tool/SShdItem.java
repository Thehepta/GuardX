package com.hepta.guardx.Tool;


import android.content.Context;
import android.content.Intent;

import com.hepta.guardx.Tool.Sshd.SshdActivity;
import com.hepta.guardx.Tool.base.ItemCardBean;

public class SShdItem extends ItemCardBean {


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
