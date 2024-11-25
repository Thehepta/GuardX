package com.hepta.guardx.Tool.deviceInfo;

import android.content.Context;

import com.hepta.guardx.GuardXApp;
import com.hepta.guardx.Tool.base.ItemInfoBean;

import java.lang.reflect.InvocationTargetException;

public class OAID extends ItemInfoBean {


    @Override
    public String getMsg() {
        return getOaid(GuardXApp.getInstance().getApplicationContext());
    }

    @Override
    public String getTitle() {
        return "OAID";
    }

    //不同版本可能不一样，写的这个是小米的
    String getOaid(Context context){
        Class<?> cls = null;
        try {
            cls = Class.forName("com.android.id.impl.IdProviderImpl");
            String oaid = null;
            oaid = (String) cls.getMethod("getOAID", Context.class).invoke(cls.newInstance(), context);
            return oaid;
        } catch (IllegalAccessException | InvocationTargetException | NoSuchMethodException |
                 InstantiationException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
