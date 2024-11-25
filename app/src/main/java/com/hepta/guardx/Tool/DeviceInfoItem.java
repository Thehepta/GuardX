package com.hepta.guardx.Tool;



import android.content.Context;
import android.content.Intent;

import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.deviceInfo.DeviceInfoActivity;
import com.hepta.guardx.Tool.deviceInfo.MRDID;

import java.lang.reflect.InvocationTargetException;

public class DeviceInfoItem extends ItemCardBean {


    public DeviceInfoItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){

        Intent intent = new Intent(context, DeviceInfoActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent,null);

//        Log.e("DeviceInfoItem","Oaid:"+getOaid(context));
//        Log.e("DeviceInfoItem","DRMID:"+getMediaDrm());
//        Log.e("DeviceInfoItem","RXPOSED_ACTIVITY:"+System.getenv("RXPOSED_ACTIVITY"));
    }





}
