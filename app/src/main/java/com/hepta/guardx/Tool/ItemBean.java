package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

public class ItemBean {

    String index;
    String msg;
    boolean status;
    public ItemBean(String msg) {
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
