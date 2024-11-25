package com.hepta.guardx.Tool.base;

import android.content.Context;

public class ItemInfoBean {

    String index;
    String msg;
    String title;
    boolean status;

    public ItemInfoBean(){
        title="";
        msg="";
        index="";
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

    public String getTitle() {
        return title;
    }

    public void ItemHandle(Context context){

    }
}
