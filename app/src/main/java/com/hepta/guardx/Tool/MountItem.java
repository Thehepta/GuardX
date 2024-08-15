package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.DropbearUtil;

public class MountItem extends ItemBean {


    public MountItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        DropbearUtil.mountTest();
    }}
