package com.hepta.guardx.Tool.deviceInfo;


import android.media.MediaDrm;
import android.os.Build;
import android.util.Base64;
import android.util.Log;

import com.hepta.guardx.Tool.base.ItemInfoBean;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.security.MessageDigest;
import java.util.UUID;

public class MRDID extends ItemInfoBean {


    @Override
    public String getTitle() {
        return "MRDID";
    }


    @Override
    public String getMsg() {
        return getDrmId();
    }

    public static String getMediaDrmId() {
        if (Build.VERSION.SDK_INT < 23 || Build.VERSION.SDK_INT > 29) {
            return "";
        }
        StringBuilder sb = new StringBuilder();
        try {
            Class<?> cls = Class.forName("java.util.UUID");
            Class<?> cls2 = Class.forName("android.media.MediaDrm");
            Constructor<?> constructor = cls.getConstructor(Long.TYPE, Long.TYPE);
            Constructor<?> constructor2 = cls2.getConstructor(cls);
            Method method = cls2.getMethod("getPropertyByteArray", String.class);
            Object newInstance = constructor2.newInstance(constructor.newInstance(-1301668207276963122L, -6645017420763422227L));
            sb.append(Base64.encodeToString((byte[]) method.invoke(newInstance, "deviceUniqueId"), 2)).append("__").append("_");
            cls2.getMethod("close", new Class[0]).invoke(newInstance, new Object[0]);
        } catch (Throwable th) {
//            th.printStackTrace();
        }
        String result = sb.toString();
        Log.i("new_MediaDrmId:", result);
        return result;

    }

    public static String getMediaDrmId_old() {
        if (Build.VERSION.SDK_INT < 23) {
            return "";
        }
        StringBuilder sb = new StringBuilder();
        try {
            Class<?> cls = Class.forName("java.util.UUID");
            Class<?> cls2 = Class.forName("android.media.MediaDrm");
            Constructor<?> constructor = cls.getConstructor(Long.TYPE, Long.TYPE);
            Constructor<?> constructor2 = cls2.getConstructor(cls);
            Method method = cls2.getMethod("getPropertyByteArray", String.class);
            Object newInstance = constructor2.newInstance(constructor.newInstance(-1301668207276963122L, -6645017420763422227L));
            sb.append(Base64.encodeToString((byte[]) method.invoke(newInstance, "deviceUniqueId"), 2));
            sb.append("__");
            sb.append("_");
            cls2.getMethod("close", new Class[0]).invoke(newInstance, new Object[0]);
        } catch (Throwable th) {
//            th.printStackTrace();
        }

        String result = sb.toString();
        Log.i("old_MediaDrmId:", result);
        return result;
    }

    public static String getDrmId() {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.JELLY_BEAN_MR1) {
            //
            //final UUID COMMON_PSSH_UUID = new UUID(0x1077EFECC0B24D02L, 0xACE33C1E52E2FB4BL);
            //final UUID CLEARKEY_UUID = new UUID(0xE2719D58A985B3C9L, 0x781AB030AF78D30EL);
            //final UUID WIDEVINE_UUID = new UUID(0xEDEF8BA979D64ACEL, 0xA3C827DCD51D21EDL);
            //final UUID PLAYREADY_UUID = new UUID(0x9A04F07998404286L, 0xAB92E65BE0885F95L);


            //这个好象是和华为有关，在pdd里找到的,使用这个发生了崩溃
//            UUID uuid = new UUID(4422091961135677928L, -5169044695670406100L);

            //
//            UUID uuid = new UUID(0xEDEF8BA979D64ACEL, 0xA3C827DCD51D21EDL);

//            UUID uuid = new UUID(-1301668207276963122L, -6645017420763422227L);
//            UUID uuid2 = new UUID(4422091961135677928L, -5169044695670406100L);
//
//            UUID[] uuidArr = new UUID[]{uuid, uuid2};
            UUID uuid = new UUID(-1301668207276963122L, -6645017420763422227L);
            Log.i("td_isSupported:", MediaDrm.isCryptoSchemeSupported(uuid)+"");
//            if (MediaDrm.isCryptoSchemeSupported(uuid)) {//查询设备是否支持给定方案
            try {
                MediaDrm drm = new MediaDrm(uuid);
                MessageDigest md5 = MessageDigest.getInstance("MD5");
                byte[] bytes = drm.getPropertyByteArray("deviceUniqueId");  //fefd768a6b015a14767061ed7a48e094ccd04048b382260198e2df7f948ef7fd
                String vendor = drm.getPropertyString("vendor");
                String version = drm.getPropertyString("version");
                String description = drm.getPropertyString("description");
                String result = g(bytes);
                Log.i("td_MediaDrmId:", result);
                return result+":"+vendor+":"+version+":"+description;

            } catch (Throwable e) {
                e.printStackTrace();
            }
        }
//        }
        return null;
    }


    public static int m(String str) {
        if (str != null) {
            return str.length();
        }
        return 0;
    }

    public static String g(byte[] bArr) {

        StringBuilder sb = new StringBuilder("");
        if (bArr == null || bArr.length <= 0) {
            return null;
        }
        for (byte b : bArr) {
            String hexString = Integer.toHexString(b & 255);
            if (m(hexString) < 2) {
                sb.append(0);
            }
            sb.append(hexString);
        }
        return sb.toString().toLowerCase();
    }

}
