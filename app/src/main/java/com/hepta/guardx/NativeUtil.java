package com.hepta.guardx;

import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import dalvik.system.BaseDexClassLoader;

public class NativeUtil {

    static {
        System.loadLibrary("davilkRuntime");
    }

    public static native ClassLoader[] getBaseDexClassLoaderList();
    public static native ClassLoader[] getClassLoaderList();
    public static native List<String> getClassFind(List<String> classNames);


    public static List<String> matchClass(List<String> classNames) {
        List<String> foundClasses = new ArrayList<>();

        ClassLoader[] classLoaders = getClassLoaderList();
        for (ClassLoader classLoader : classLoaders) {
                for(String clsName :classNames){
                    try {
                        Class<?> clazz = classLoader.loadClass(clsName);
                        foundClasses.add(clazz.getName());
                    } catch (ClassNotFoundException ignored) {
                    }

                }
        }

        return foundClasses;
    }
}
