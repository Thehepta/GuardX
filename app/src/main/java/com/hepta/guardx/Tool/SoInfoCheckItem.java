package com.hepta.guardx.Tool;

import android.content.Context;

import com.hepta.guardx.Tool.base.ItemBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

import java.util.List;

public class SoInfoCheckItem extends ItemBean {
    public  SoInfoCheckItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){

        List<String> foundClasses = NativeUtil.getSoinfoList();
    }
}
