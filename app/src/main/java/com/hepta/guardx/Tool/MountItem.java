package com.hepta.guardx.Tool;

import android.content.Context;
import android.util.Log;

import com.hepta.guardx.DropbearUtil;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class MountItem extends ItemBean {


    public MountItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        DropbearUtil.mountTest();
    }

    public static String rootRun(String cmd)
    {
        Log.e("rootRun",cmd);
        StringBuilder Result  = new StringBuilder();
        try {
            // 申请获取root权限
            Process process = Runtime.getRuntime().exec("su"); //"/system/xbin/su"
            // 获取输出流
            OutputStream outputStream = process.getOutputStream();
            InputStream is = process.getInputStream();
            InputStream es = process.getErrorStream();
            DataOutputStream dataOutputStream = new DataOutputStream(outputStream);
            dataOutputStream.writeBytes(cmd);
            dataOutputStream.flush();
            dataOutputStream.close();
            outputStream.close();
            int code = process.waitFor();
            String is_line = null;
            String es_line = null;
//            Log.d(TAG, "Run:\"" + cmd +"\", "+"process.waitFor() = " + code);
            BufferedReader br;
            br = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
            while ((is_line = br.readLine()) != null) {
                Log.d("rootRun", "cmd > "+is_line);
                Result.append(is_line).append("\n");
            }

            br = new BufferedReader(new InputStreamReader(es, StandardCharsets.UTF_8));
            while ((es_line = br.readLine()) != null) {
                Log.e("rootRun", "errcmd > "+es_line);
                Result.append(es_line);
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return Result.toString();
    }

}
