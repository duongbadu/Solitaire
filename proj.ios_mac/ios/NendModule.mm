//
//  NendModule.mm
//
//  Created by F@N Communications, Inc.
//
//

#include "NendModule.h"
#include "AppController.h"
#import "RootViewController.h"
#import "CCEAGLView.h"
#import "NADView.h"

@interface NadViewDelegate : NSObject<NADViewDelegate>
{
}
@end

@implementation NadViewDelegate

//NADViewDelegateの設定

-(void)nadViewDidFinishLoad:(NADView *)adView{
    //初回ロード終了後の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendNotificationFinishLoad, NULL);
}

-(void)nadViewDidReceiveAd:(NADView *)adView{
    //ロード終了後処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendNotificationReceiveAd, NULL);
}

-(void)nadViewDidFailToReceiveAd:(NADView *)adView{
    //ロード失敗の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendNotificationFailToReceiveAd, NULL);
}

-(void)nadViewDidClickAd:(NADView *)adView{
    //広告クリック時の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendNotificationClickAd, NULL);
}

@end


//シングルトンの設定
NendModule* NendModule::m_mySingleton = NULL;
NADView* nadView = nil;
NSString* nendIDString = nil;
NSString* spotIDString = nil;

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

void NendModule::createNADView(char* apiKey, char* spotID)
{
    if(nadView){
        // すでにNADViewを生成済み
        return;
    }
    
    NendModule::sharedNendModule();
    
    //NADViewの生成
    nadView = [[NADView alloc] initWithFrame:CGRectMake(0, 0, NAD_ADVIEW_SIZE_320x50.width, NAD_ADVIEW_SIZE_320x50.height)];
    
    //NADViewDelegateクラスを生成
    nadView.delegate = (id<NADViewDelegate>)[[NadViewDelegate alloc] init];
    
    AppController* app = [UIApplication sharedApplication].delegate;
    RootViewController* viewController = app.viewController;
    [viewController.view addSubview:nadView];
    
    nendIDString = [NSString stringWithCString:apiKey encoding:NSUTF8StringEncoding];
    spotIDString = [NSString stringWithCString:spotID encoding:NSUTF8StringEncoding];
    
    [nadView setNendID:nendIDString spotID:spotIDString];
    
    
    //ログ出力の設定(必要に応じて設定)
    [nadView setIsOutputLog:YES];
    
}

void NendModule::createNADView(char* apiKey, char* spotID, cocos2d::Point pos)
{
    //広告View生成
    NendModule::createNADView(apiKey, spotID);
    
    //位置設定
    
    //cocos2d-x上の座標をiOSの座標に変換
    //cocos2d-xで管理するwindowサイズを取得
    cocos2d::Size size = Director::getInstance()->getWinSize();
    
    //座標を割合で取得
    cocos2d::Point pointRate;
    pointRate.x = (pos.x / size.width);
    pointRate.y = (pos.y / size.height);
    
    //iOSで管理するViewのサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //高さをiOS基準に変換する
    CGPoint newPosition;
    newPosition.x = mainViewRect.size.width * pointRate.x;
    newPosition.y = mainViewRect.size.height - (mainViewRect.size.height * pointRate.y);
    
    //座標の設定
    [nadView setFrame:CGRectMake(newPosition.x, newPosition.y, nadView.frame.size.width, nadView.frame.size.height)];

    
    NendModule::load();
    
}

void setPositionTop(){
    //NADViewを画面上部・中央に移動する
    
    //Windowサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //NADViewの位置を変更
    [nadView setFrame:CGRectMake((mainViewRect.size.width - nadView.frame.size.width) /2, 0, nadView.frame.size.width, nadView.frame.size.height)];
    
    
    return;
}

void setPositionButtom(){
    //NADViewを画面下部・中央に移動する
    
    //Windowサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    //NADViewの位置を変更
    [nadView setFrame:CGRectMake((mainViewRect.size.width - nadView.frame.size.width) /2, mainViewRect.size.height - nadView.frame.size.height, nadView.frame.size.width, nadView.frame.size.height)];
    
    
    return;
}

void NendModule::createNADViewTop(char *apiKey, char *spotID){
    //広告View生成
    NendModule::createNADView(apiKey, spotID);
    
    //位置設定
    setPositionTop();
    
    NendModule::load();
}

void NendModule::createNADViewBottom(char *apiKey, char *spotID){
    //広告View生成
    NendModule::createNADView(apiKey, spotID);
    
    //位置設定
    setPositionButtom();

    NendModule::load();
}

void NendModule::hideNADView()
{
    //NADView非表示
    [nadView setHidden:YES];
}

void NendModule::showNADView()
{
    //NADView表示
    [nadView setHidden:NO];
}

void NendModule::load(){
    //load
    [nadView load];
}

void NendModule::pause(){
    //pause
    [nadView pause];
}

void NendModule::resume(){
    //resume
    [nadView resume];
}

void NendModule::release(){
    NendModule::pause();
    [nadView.delegate release];
    nadView.delegate = nil;
    [nadView removeFromSuperview];
    [nadView release];
    nadView = nil;
}