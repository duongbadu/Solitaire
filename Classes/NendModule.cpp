// NendModule.cpp

#include "NendModule.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "net/nend/NendModule/NendModule"

//シングルトンの設定
NendModule* NendModule::m_mySingleton = NULL;

NendModule::NendModule()
{
}

NendModule* NendModule::sharedNendModule(){

    if (NULL == m_mySingleton) {
        //クラス未生成の場合は生成する
        m_mySingleton = new NendModule();
    }

    return m_mySingleton;
}

//IconViewの生成(位置指定)
void NendModule::createNADView(char* apiKey, char* spotID, CCPoint pos){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createAdView", "(Ljava/lang/String;Ljava/lang/String;FF)V")) {
	    //高さをandroid基準に変換する
	    CCSize size = CCDirector::sharedDirector()->getWinSize();
	    //座標を割合で取得
	    CCPoint pointRate;
	    pointRate.x = (pos.x / size.width);
	    pointRate.y = (pos.y / size.height);

	    //端末の画面サイズを取得
	    auto director = Director::getInstance();
	    auto pEGLView = director->getOpenGLView();

	    CCSize frameSize = pEGLView->getFrameSize();
	    CCPoint newPosition;
	    newPosition.x = frameSize.width * pointRate.x;
	    newPosition.y = frameSize.height - (frameSize.height * pointRate.y);

		jstring stringApiKey = t.env->NewStringUTF(apiKey);
		jstring stringSpotID = t.env->NewStringUTF(spotID);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringApiKey, stringSpotID, newPosition.x, newPosition.y);
		t.env->DeleteLocalRef(stringApiKey);
		t.env->DeleteLocalRef(stringSpotID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//Viewの生成(画面下部)
void NendModule::createNADViewBottom(char* apiKey, char* spotID){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createAdViewBottom", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringApiKey = t.env->NewStringUTF(apiKey);
		jstring stringSpotID = t.env->NewStringUTF(spotID);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringApiKey, stringSpotID);
		t.env->DeleteLocalRef(stringApiKey);
		t.env->DeleteLocalRef(stringSpotID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//Viewの生成(画面上部)
void NendModule::createNADViewTop(char* apiKey, char* spotID){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createAdViewTop", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringApiKey = t.env->NewStringUTF(apiKey);
		jstring stringSpotID = t.env->NewStringUTF(spotID);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringApiKey, stringSpotID);
		t.env->DeleteLocalRef(stringApiKey);
		t.env->DeleteLocalRef(stringSpotID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//Viewの非表示
void NendModule::hideNADView(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideAdView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//Viewの再表示
void NendModule::showNADView(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showAdView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NendModule::load(){
    
}

//広告の停止
void NendModule::pause(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "pauseAdView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//広告の再開
void NendModule::resume(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "resumeAdView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void NendModule::release(){

}

//callback処理
extern "C"
{
	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendModule_onReceiveAd(JNIEnv* env, jobject thiz) {
	    //ロード終了のオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendNotificationReceiveAd, NULL);
	}

	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendModule_onFailedToReceiveAd(JNIEnv* env, jobject thiz) {
	    //ロード失敗のオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendNotificationFailToReceiveAd, NULL);
	}

	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendModule_onDismissScreen(JNIEnv* env, jobject thiz) {
	}

	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendModule_onClick(JNIEnv* env, jobject thiz) {
	    //広告クリックのオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendNotificationClickAd, NULL);
	}
}
