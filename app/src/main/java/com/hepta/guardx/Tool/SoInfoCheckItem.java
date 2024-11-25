package com.hepta.guardx.Tool;

import android.content.Context;

import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

import java.util.List;

public class SoInfoCheckItem extends ItemCardBean {
    public  SoInfoCheckItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){

        List<String> foundClasses = NativeUtil.getSoinfoList();
    }
}
