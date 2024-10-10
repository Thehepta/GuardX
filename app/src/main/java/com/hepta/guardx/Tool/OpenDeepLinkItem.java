package com.hepta.guardx.Tool;


import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

import com.hepta.guardx.SshdActivity;
import com.hepta.guardx.Tool.base.ItemBean;

public class OpenDeepLinkItem extends ItemBean {

    // 通过activity日志启动一个activity
//2024-10-09 16:05:43.371  1687-2816  ActivityTaskManager     pid-1687                             I  START u0 {act=android.intent.action.VIEW dat=kwai://merchant/detail/content?fid=4259269500&cc=share_qqms&followRefer=151&shareMethod=TOKEN&kpn=KUAISHOU&subBiz=VIDEO_GOODS_DETAIL_SHARE&carrierType=24&shareId=18099538039095&lastSharePageCode=BUYER_HOME_PAGE&sharePageCode=MERCHANT_ITEMSELF_DETAIL_CONTENT&fromSceneShelf=0&fromSecondSceneShelf=0&itemId=22145545419521&shareMode=APP&paramSellerId=3997758521&originShareId=18099538039095&layoutType=4&shareObjectId=22145545419521&id=22145545419521&shareUrlOpened=0&carrierId=${carrierId}&timestamp=1728460620446&alreadyDealt=true&blockUgStidReport=true flg=0x40000 cmp=com.smile.gifmaker/com.kuaishou.merchant.transaction.detail.contentdetail.MerchantContentDetailActivity (has extras)} from uid 10208 from pid 24077 callingPackage com.smile.gifmaker 根据这个信息，使用代码启动这个activity
    public OpenDeepLinkItem(String msg) {
        super(msg);
    }

    @Override
    public void ItemHandle(Context context){
        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setComponent(new ComponentName("com.smile.gifmaker", "com.kuaishou.merchant.transaction.detail.contentdetail.MerchantContentDetailActivity"));

// 设置数据 URI
//        intent.setData(Uri.parse("kwai://merchant/detail/content?fid=4259269500&cc=share_qqms&followRefer=151&shareMethod=TOKEN&kpn=KUAISHOU&subBiz=VIDEO_GOODS_DETAIL_SHARE&carrierType=24&shareId=18099538039095&lastSharePageCode=BUYER_HOME_PAGE&sharePageCode=MERCHANT_ITEMSELF_DETAIL_CONTENT&fromSceneShelf=0&fromSecondSceneShelf=0&itemId=22145545419521&shareMode=APP&paramSellerId=3997758521&originShareId=18099538039095&layoutType=4&shareObjectId=22145545419521&id=22145545419521&shareUrlOpened=0&carrierId=${carrierId}&timestamp=1728460620446&alreadyDealt=true&blockUgStidReport=true"));
        intent.setData(Uri.parse("kwai://merchant/detail/content?cc=share_qqms&followRefer=151&shareMethod=TOKEN&kpn=KUAISHOU&subBiz=VIDEO_GOODS_DETAIL_SHARE&carrierType=24&shareId=18099538039095&lastSharePageCode=BUYER_HOME_PAGE&sharePageCode=MERCHANT_ITEMSELF_DETAIL_CONTENT&fromSceneShelf=0&fromSecondSceneShelf=0&itemId=21425328564210&shareMode=APP&paramSellerId=3997758521&originShareId=18099538039095&layoutType=4&shareObjectId=21425328564210&id=21425328564210&shareUrlOpened=0&carrierId=${carrierId}&timestamp=1728460620446&alreadyDealt=true&blockUgStidReport=true"));

// 添加FLAG_ACTIVITY_NEW_TASK标志
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

// 启动 Activity
        context.startActivity(intent);
    }
}
