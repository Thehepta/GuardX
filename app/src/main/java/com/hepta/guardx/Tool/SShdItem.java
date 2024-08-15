package com.hepta.guardx.Tool;

import android.util.Log;

import com.hepta.guardx.Tool.ItemBean;

public class SShdItem extends ItemBean {


    public SShdItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle() {
        Log.e("rzx","SShdItem");
    }
}
