package com.hepta.guardx.Tool;



import android.content.Context;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.hepta.guardx.Tool.base.ItemBean;
import com.hepta.guardx.Tool.utils.MRDID;

import java.lang.reflect.InvocationTargetException;

public class DeviceInfoItem extends ItemBean {


    public DeviceInfoItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){

        Log.e("DeviceInfoItem",getMediaDrm());
        Log.e("DeviceInfoItem","RXPOSED_ACTIVITY:"+System.getenv("RXPOSED_ACTIVITY"));
    }


     //不同版本可能不一样，写的这个是小米的
    String getOaid(Context context){
        Class<?> cls = null;
        try {
            cls = Class.forName("com.android.id.impl.IdProviderImpl");
            String oaid = null;
            oaid = (String) cls.getMethod("getOAID", Context.class).invoke(cls.newInstance(), context);
            Log.i("OaidItem", "oaid is: " + oaid);
            return oaid;
        } catch (IllegalAccessException | InvocationTargetException | NoSuchMethodException |
                 InstantiationException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
    String getMediaDrm() {

        return MRDID.getDrmId();
    }

//    String ip_list(Context context) {
//
//    }
}
