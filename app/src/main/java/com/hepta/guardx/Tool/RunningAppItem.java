package com.hepta.guardx.Tool;

import android.app.ActivityManager;
import android.content.Context;
import android.os.Build;
import android.text.TextUtils;
import android.util.Log;

import com.hepta.guardx.Tool.base.ItemCardBean;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class RunningAppItem extends ItemCardBean {


    public RunningAppItem(String msg) {
        super(msg);
    }

    public  <E> Iterator<E> V(List<E> list) {
        Iterator<E> it;
        if (list == null) {
            if (Build.VERSION.SDK_INT >= 19) {
                it = (Iterator<E>) Collections.emptyList().iterator();
                return it;
            }
            return new ArrayList().iterator();
        }
        return list.iterator();
    }

    @Override
    public void ItemHandle(Context context){
        ActivityManager activityManager = (ActivityManager) context.getSystemService( Context.ACTIVITY_SERVICE);
        if (activityManager == null) {
            return ;
        }
        String processName = context.getPackageName();
        List<ActivityManager.RunningAppProcessInfo> list = null;
        try {
            list = activityManager.getRunningAppProcesses();
        } catch (Exception unused) {
        }
        if (list != null && !list.isEmpty()) {
            Iterator V = V(list);
            while (V.hasNext()) {
                ActivityManager.RunningAppProcessInfo runningAppProcessInfo = (ActivityManager.RunningAppProcessInfo) V.next();
                if (TextUtils.equals(runningAppProcessInfo.processName, processName) && runningAppProcessInfo.importance == 100) {
                    Log.e("Rzx","true");
                }
            }
        }
    }



}
