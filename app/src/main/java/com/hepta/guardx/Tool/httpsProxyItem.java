package com.hepta.guardx.Tool;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import com.hepta.guardx.Tool.base.ItemCardBean;
import com.hepta.guardx.Tool.utils.NativeUtil;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import javax.net.ssl.HttpsURLConnection;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class httpsProxyItem extends ItemCardBean {


    public httpsProxyItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){

        Runnable runnable = new Runnable(){
            @Override
            public void run() {
                OkHttpClient mOkHttpClient = new OkHttpClient.Builder().build();
                final Request request = new Request.Builder()
                        .url("https://www.baidu.com")
                        .build();

                Response response = null;
                try {
                    response = mOkHttpClient.newCall(request).execute();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {
                    Log.d("https",response.body().string());
                    showToastInThread(context,"resquest suc");
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        };
        new Thread(runnable).start();
    }


    public void showToastInThread(Context context, final String message) {
        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(() -> Toast.makeText(context, message, Toast.LENGTH_SHORT).show());
    }

}