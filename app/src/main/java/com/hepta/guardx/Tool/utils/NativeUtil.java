package com.hepta.guardx.Tool.utils;

import java.lang.reflect.Member;
import java.util.ArrayList;
import java.util.List;

public class NativeUtil {

    static {
        System.loadLibrary("GuardX");
    }

    public static native ClassLoader[] getClassLoaderList();
    public static native List<String> getFilterClass(List<String> classNames);
    public static native List<String> getSoinfoList();
    public static native boolean lsplt(Member nativeSpecializeAppProcess_method);


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
