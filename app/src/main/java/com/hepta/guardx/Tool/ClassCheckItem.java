package com.hepta.guardx.Tool;

import android.content.Context;

import com.hepta.guardx.Tool.base.ItemBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

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
//        Log.e("rzx",foundClasses.toString());
    }
}
