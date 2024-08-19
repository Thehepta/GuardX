package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.DropbearUtil;
import com.hepta.guardx.NativeUtil;

import java.util.ArrayList;
import java.util.List;

public class ClassCheckItem extends ItemBean {


    public ClassCheckItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        List<String> findClasses = new ArrayList<>();
        findClasses.add("de.robv.android.xposed.XposedBridge");
        findClasses.add("com.hepta.guardx.Tool");
        List<String> foundClasses = NativeUtil.getFilterClass(findClasses);
        Log.e("rzx",foundClasses.toString());
    }
}
