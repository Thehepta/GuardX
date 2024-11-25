package com.hepta.guardx.Tool.base;

import android.content.Context;

public class ItemCardBean {

    String index;
    String msg;
    boolean status;
    public ItemCardBean(String msg) {
        this.msg = msg;
    }
    public String getIndex() {
        return index;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getMsg() {
        return msg;
    }


    public void ItemHandle(Context context){

    }
}
