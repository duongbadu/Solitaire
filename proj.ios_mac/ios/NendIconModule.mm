//
//  NendIconModule.mm
//
//  Created by F@N Communications, Inc.
//
//

#include "NendIconModule.h"
#include "AppController.h"
#import "RootViewController.h"
#import "CCEAGLView.h"
#import "NADIconLoader.h"

#define ICON_DISPLAY_COUNT 4

@interface NadIconLoaderDelegate : NSObject<NADIconLoaderDelegate>
{
}
@end

@implementation NadIconLoaderDelegate

//NADViewDelegateの設定

-(void)nadIconLoaderDidFinishLoad:(NADIconLoader *)iconLoader{
    //初回ロード終了後の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationFinishLoad, NULL);
}

-(void)nadIconLoaderDidReceiveAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
    //ロード終了後処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationReceiveAd, NULL);
}

-(void)nadIconLoaderDidFailToReceiveAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
    //ロード失敗の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationFailToReceiveAd, NULL);
}

-(void)nadIconLoaderDidClickAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
    //広告クリック時の処理を記述
    CCNotificationCenter::getInstance()->postNotification(NendIconNotificationClickAd, NULL);
}

@end



//シングルトンの設定
NendIconModule* NendIconModule::m_mySingleton = NULL;
NADIconLoader* iconLoader = nil;
NSMutableArray* iconViewArray = nil;
NSString* nadIconApiKey;
NSString* nadIconSpotID;


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

//NADIconLoader生成
void NendIconModule::createNADIconLoader(char* apiKey, char* spotID){
    if (iconLoader) {
        return;
    }
    
    NendIconModule::sharedNendIconModule();

    iconLoader = [[NADIconLoader alloc] init];
    iconViewArray = [[NSMutableArray alloc] init];
    
    nadIconApiKey = [NSString stringWithCString:apiKey encoding:NSUTF8StringEncoding];
    nadIconSpotID = [NSString stringWithCString:spotID encoding:NSUTF8StringEncoding];
    
    //NADViewDelegateクラスを生成
    iconLoader.delegate = (id<NADIconLoaderDelegate>)[[NadIconLoaderDelegate alloc] init];
    
    iconLoader.isOutputLog = YES;
    
}

//NADIconView生成、API Key, NendIDを設定、位置設定
void NendIconModule::createNADIconView(cocos2d::Point pos){

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
    
    NADIconView* iconView = [[NADIconView alloc] initWithFrame:CGRectMake(newPosition.x, newPosition.y, NAD_ICONVIEW_SIZE_75x75.width, NAD_ICONVIEW_SIZE_75x75.height)];
    
    AppController* app = [UIApplication sharedApplication].delegate;
    RootViewController* viewController = app.viewController;
    [viewController.view addSubview:iconView];
    
    [iconLoader addIconView:iconView];
    [iconViewArray addObject:iconView];
}

void NendIconModule::createNADIconViewBottom(){

    //画面下部にアイコンを並べて表示する

    //Windowサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;


    AppController* app = [UIApplication sharedApplication].delegate;
    RootViewController* viewController = app.viewController;

    for (int i = (int)[iconViewArray count]; i < ICON_DISPLAY_COUNT; i++) {
        NADIconView* iconView = [[NADIconView alloc] init];
        //中央に並べる
        [iconView setFrame:CGRectMake(
                                       (mainViewRect.size.width /2) + ((NAD_ICONVIEW_SIZE_75x75.width * (i -(ICON_DISPLAY_COUNT /2) ))),
                                      mainViewRect.size.height - (NAD_ICONVIEW_SIZE_75x75.height ),
                                      iconView.frame.size.width,
                                      iconView.frame.size.height)];
        
        [viewController.view addSubview:iconView];

        [iconLoader addIconView:iconView];
        [iconViewArray addObject:iconView];

    }
    
}

void NendIconModule::createNADIconViewTop(){
    
    //画面上部にアイコンを並べて表示する
    
    //Windowサイズを取得
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *baseView = (CCEAGLView *) view->getEAGLView();
    CGRect mainViewRect = baseView.bounds;
    
    
    AppController* app = [UIApplication sharedApplication].delegate;
    RootViewController* viewController = app.viewController;

    for (int i = (int)[iconViewArray count]; i < ICON_DISPLAY_COUNT; i++) {
        NADIconView* iconView = [[NADIconView alloc] init];
        //中央に並べる
        [iconView setFrame:CGRectMake(
                                      (mainViewRect.size.width /2) + ((NAD_ICONVIEW_SIZE_75x75.width * (i -(ICON_DISPLAY_COUNT /2) ))),
                                      0,
                                      iconView.frame.size.width,
                                      iconView.frame.size.height)];
        
        [viewController.view addSubview:iconView];

        [iconLoader addIconView:iconView];
        [iconViewArray addObject:iconView];
        
    }
    
}

void NendIconModule::hideNADIconView()
{
    for (NADIconView* iconView in iconViewArray) {
        [iconView setHidden:YES];
    }
}

void NendIconModule::showNADIconView()
{
    for (NADIconView* iconView in iconViewArray) {
        [iconView setHidden:NO];
    }
}

void NendIconModule::load(){
    [iconLoader setNendID:nadIconApiKey spotID:nadIconSpotID];
    [iconLoader load];
}


void NendIconModule::pause(){
    [iconLoader pause];
}

void NendIconModule::resume(){
    [iconLoader resume];
}

void NendIconModule::release(){
    NendIconModule::pause();
    [iconLoader.delegate release];
    iconLoader.delegate = nil;
    [iconLoader release];
    iconLoader = nil;
    
    for (NADIconView* iconView in iconViewArray) {
        [iconView removeFromSuperview];
        [iconView release];
    }

    [iconViewArray removeAllObjects];
    [iconViewArray release];
    iconViewArray = nil;
}
