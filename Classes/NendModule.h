//
//  NendModule.h
//
//  Created by F@N Communications, Inc.
//
//

#ifndef __NendModule__
#define __NendModule__

#include "cocos2d.h"

#define NendNotificationFinishLoad      "NEND_NOTIFICATION_FINISH_LOAD"
#define NendNotificationReceiveAd       "NEND_NOTIFICATION_RECEIVE_AD"
#define NendNotificationFailToReceiveAd "NEND_NOTIFICATION_FAIL_TO_RECEIVE_AD"
#define NendNotificationClickAd         "NEND_NOTIFICATION_CLICK_AD"

using namespace cocos2d;

class NendModule
{
private:
    NendModule();
    //シングルトン用クラス保持
    static NendModule* m_mySingleton;
    //NADView生成、API Key, NendIDを設定
    static void createNADView(char* apiKey, char* spotID);
    //内部動作用　広告のload
    static void load();
public:
    //クラス取得
    static NendModule* sharedNendModule();
    //NADView生成、API Key, NendIDを設定、位置設定
    static void createNADView(char* apiKey, char* spotID, cocos2d::Point pos);
    //NADView生成、画面下部、API Key, NendIDを設定
    static void createNADViewBottom(char* apiKey, char* spotID);
    //NADView生成、画面上部、API Key, NendIDを設定
    static void createNADViewTop(char* apiKey, char* spotID);
    //NADView非表示
    static void hideNADView();
    //NADView表示
    static void showNADView();
    //広告のload一時停止
    static void pause();
    //広告のload再開
    static void resume();
    //解放
    static void release();

};

#endif
