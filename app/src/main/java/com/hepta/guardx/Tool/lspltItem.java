package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

import java.lang.reflect.Member;

public class lspltItem extends ItemCardBean {


    public lspltItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        Member nativeSpecializeAppProcess_method = Found_javaMethod("com.android.internal.os.Zygote","nativeSpecializeAppProcess");
        if(nativeSpecializeAppProcess_method == null){
            Log.e("rzx","nativeSpecializeAppProcess_method not found");
        }
        NativeUtil.lsplt(nativeSpecializeAppProcess_method);
    }


    public Member Found_javaMethod(String className, String Method){
        try {

            Class<?> cls_zygote = Class.forName(className);
            for(Member method: cls_zygote.getDeclaredMethods()){
                if(method.getName().contains(Method)){
                    return method;
                }
            }

        } catch (ClassNotFoundException e) {

        }
        return null;
    }

}
