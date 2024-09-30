package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.Tool.base.ItemBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

import java.lang.reflect.Field;

import dalvik.system.BaseDexClassLoader;
import dalvik.system.DexFile;
import dalvik.system.PathClassLoader;

public class ClassLoaderListItem extends ItemBean {
    public ClassLoaderListItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        PathClassLoader pathClassLoader = new PathClassLoader(".",ClassLoader.getSystemClassLoader());
        Log.e("Rzx",pathClassLoader.toString());

        ClassLoader[] classLoaders = NativeUtil.getClassLoaderList();
        Class<?> baseDexClassLoaderClass = null;
        try {
            baseDexClassLoaderClass = Class.forName("dalvik.system.BaseDexClassLoader");
            Class<?> Element = Class.forName("dalvik.system.DexPathList$Element");
            Field pathListField = baseDexClassLoaderClass.getDeclaredField("pathList");
            Class<?> dexPathListClass = Class.forName("dalvik.system.DexPathList");
            Field dexElementsField = dexPathListClass.getDeclaredField("dexElements");
            Field dexFile_filed = Element.getDeclaredField("dexFile");
            Field DexFile_mFileName = DexFile.class.getDeclaredField("mFileName");
            DexFile_mFileName.setAccessible(true);
            dexFile_filed.setAccessible(true);
            pathListField.setAccessible(true);
            dexElementsField.setAccessible(true);
            for (ClassLoader classLoader:classLoaders) {
                if (classLoader instanceof BaseDexClassLoader) {
                    Log.e("dexFile", "classLoader:"+classLoader.toString());
                    Object BaseDexClassLoad_PathList = pathListField.get(classLoader);
                    Object[] DexPathList_dexElements = (Object[]) dexElementsField.get(BaseDexClassLoad_PathList);
                    int i = 0;
                    if (DexPathList_dexElements != null) {
                        for (Object dexElement : DexPathList_dexElements) {
                            DexFile dexFile = (DexFile) dexFile_filed.get(dexElement);
                            try {
                                String fileName = (String) DexFile_mFileName.get(dexFile);
                                Log.e("dexFile", fileName);
                            }catch (NullPointerException exception){
                                Log.e("dexFile", "fileName is null");
                            }
                        }
                    }
                } else {
                    Log.e("dump", "class not instanceof BaseDexClassLoader");
                }
            }
        } catch (ClassNotFoundException | NoSuchFieldException | IllegalAccessException e) {
            throw new RuntimeException(e);
        }


    }
}
