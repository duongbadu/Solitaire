// NendIconModule.cpp

#include "NendIconModule.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "net/nend/NendModule/NendIconModule"

//シングルトンの設定
NendIconModule* NendIconModule::m_mySingleton = NULL;

NendIconModule::NendIconModule()
{
}

NendIconModule* NendIconModule::sharedNendIconModule(){

    if (NULL == m_mySingleton) {
        //クラス未生成の場合は生成する
        m_mySingleton = new NendIconModule();
    }

    return m_mySingleton;
}

//IconLoaderの生成
void NendIconModule::createNADIconLoader(char* apiKey, char* spotID){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createIconLoader", "(Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring stringApiKey = t.env->NewStringUTF(apiKey);
		jstring stringSpotID = t.env->NewStringUTF(spotID);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringApiKey, stringSpotID);
		t.env->DeleteLocalRef(stringApiKey);
		t.env->DeleteLocalRef(stringSpotID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//IconViewの生成(位置指定)
void NendIconModule::createNADIconView(cocos2d::Point pos){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createIconView", "(FF)V")) {
	    //高さをandroid基準に変換する
	    CCSize size = CCDirector::sharedDirector()->getWinSize();

	    //座標を割合で取得
	    cocos2d::Point pointRate;
	    pointRate.x = (pos.x / size.width);
	    pointRate.y = (pos.y / size.height);

	    //端末の画面サイズを取得
	    auto director = Director::getInstance();
	    auto pEGLView = director->getOpenGLView();

	    CCSize frameSize = pEGLView->getFrameSize();
	    cocos2d::Point newPosition;
	    newPosition.x = frameSize.width * pointRate.x;
	    newPosition.y = frameSize.height - (frameSize.height * pointRate.y);


		t.env->CallStaticVoidMethod(t.classID, t.methodID, newPosition.x, newPosition.y);
		t.env->DeleteLocalRef(t.classID);
	}
}

//IconViewの生成(画面下部)
void NendIconModule::createNADIconViewBottom(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createIconViewBottom", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//IconViewの生成(画面上部)
void NendIconModule::createNADIconViewTop(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createIconViewTop", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//IconViewの非表示
void NendIconModule::hideNADIconView(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideIconView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//IconViewの再表示
void NendIconModule::showNADIconView(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showIconView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//広告のロード
void NendIconModule::load(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadIconLoader", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//広告の停止
void NendIconModule::pause(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "pauseIconView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//広告の再開
void NendIconModule::resume(){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "resumeIconView", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

//解放
void NendIconModule::release(){

}

//callback処理
extern "C"
{
	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendIconModule_onReceiveIconAd(JNIEnv* env, jobject thiz) {
	    //初回ロード終了のオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationReceiveAd, NULL);
	}

	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendIconModule_onFailedIconAd(JNIEnv* env, jobject thiz) {
	    //ロード失敗のオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationFailToReceiveAd, NULL);
	}

	JNIEXPORT void JNICALL Java_net_nend_NendModule_NendIconModule_onClickIconAd(JNIEnv* env, jobject thiz) {
	    //広告クリックのオブザーバー通知
	    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationClickAd, NULL);
	}
}
