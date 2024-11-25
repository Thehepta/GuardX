package com.hepta.guardx;

import android.app.Application;

public class GuardXApp extends Application {
    private static GuardXApp instance;

    @Override
    public void onCreate() {
        super.onCreate();
        instance = this;

    }
    public static  GuardXApp getInstance(){
        return instance;
    }

}
