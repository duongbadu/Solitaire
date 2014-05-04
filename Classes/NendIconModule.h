//
//  NendIconModule.h
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __NendIconModule__
#define __NendIconModule__

#include "cocos2d.h"

#define NendIconNotificationFinishLoad      "NEND_ICON_NOTIFICATION_FINISH_LOAD"
#define NendIconNotificationReceiveAd       "NEND_ICON_NOTIFICATION_RECEIVE_AD"
#define NendIconNotificationFailToReceiveAd "NEND_ICON_NOTIFICATION_FAIL_TO_RECEIVE_AD"
#define NendIconNotificationClickAd         "NEND_ICON_NOTIFICATION_CLICK_AD"

using namespace cocos2d;

class NendIconModule
{
private:
    NendIconModule();
    //シングルトン用クラス保持
    static NendIconModule* m_mySingleton;
public:
    //クラス取得
    static NendIconModule* sharedNendIconModule();
    //NADIconLoader生成
    static void createNADIconLoader(char* apiKey, char* spotID);
    //NADIconView生成、位置指定
    static void createNADIconView(cocos2d::Point pos);
    //NADIconView生成、画面下部
    static void createNADIconViewBottom();
    //NADIconView生成、画面上部
    static void createNADIconViewTop();
    //NADIconView非表示
    static void hideNADIconView();
    //NADIconView表示
    static void showNADIconView();
    //広告のload
    static void load();
    //広告のload一時停止
    static void pause();
    //広告のload再開
    static void resume();
    //解放
    static void release();
};

#endif
