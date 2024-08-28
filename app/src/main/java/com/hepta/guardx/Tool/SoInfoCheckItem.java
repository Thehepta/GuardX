package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.NativeUtil;

import java.util.ArrayList;
import java.util.List;

import dalvik.system.PathClassLoader;

public class SoInfoCheckItem extends ItemBean {
    public  SoInfoCheckItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){


        List<String> findClasses = new ArrayList<>();
        findClasses.add("de.robv.android.xposed.XposedBridge");
        findClasses.add("com.hepta.guardx.Tool");
        List<String> foundClasses = NativeUtil.getSoinfoList();
        Log.e("rzx",foundClasses.toString());
    }
}
