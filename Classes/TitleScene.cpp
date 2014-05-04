#include "TitleScene.h"
#include "extensions/cocos-ext.h"
#include "Trump.h"
#include "TrumpData.h"
#include "TitleViewModel.h"
#include "SolitaireKlondikeScene.h"
#include "SolitaireKlondikeViewModel.h"
//#include "NendModule.h"
//#include "NendIconModule.h"

USING_NS_CC;

using namespace extension;

Scene* TitleScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    _viewModel = new TitleViewModel();
    
    _viewModel->_title->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 250));
    this->addChild(_viewModel->_title, 1);

    _viewModel->_label1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 70));
    _viewModel->_label1->setColor(Color3B::WHITE);
    _viewModel->_label1->setAnchorPoint(Point(0.5, 0.5));

    _viewModel->_play1->setPosition(_viewModel->_label1->getPosition() + Point(0, -10));
    _viewModel->_play1->setContentSize(Size(400, _viewModel->_label1->getContentSize().height + 90));

    _viewModel->_play1card1->setPosition(_viewModel->_play1->getPosition() + Point(-100, 0));

    this->addChild(_viewModel->_play1, 1);
    this->addChild(_viewModel->_label1, 2);
    this->addChild(_viewModel->_play1card1, 3);

    _viewModel->_label3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 130));
    _viewModel->_label3->setColor(Color3B::WHITE);
    _viewModel->_label3->setAnchorPoint(Point(0.5, 0.5));

    _viewModel->_play3->setPosition(_viewModel->_label3->getPosition() + Point(0, -10));
    _viewModel->_play3->setContentSize(Size(400, _viewModel->_label3->getContentSize().height + 90));

    _viewModel->_play3card1->setPosition(_viewModel->_play3->getPosition() + Point(-130, 0));
    _viewModel->_play3card2->setPosition(_viewModel->_play3->getPosition() + Point(-100, 0));
    _viewModel->_play3card3->setPosition(_viewModel->_play3->getPosition() + Point(-70, 0));

    this->addChild(_viewModel->_play3, 1);
    this->addChild(_viewModel->_label3, 2);
    this->addChild(_viewModel->_play3card1, 5);
    this->addChild(_viewModel->_play3card2, 4);
    this->addChild(_viewModel->_play3card3, 3);
/*
    SpriteBatchNode* spBatch = SpriteBatchNode::create("Back.png");
    SpriteFrame* spFrame = SpriteFrame::create("Back.png", Rect(0, 0, 128, 128));
    spFrame->getTexture()->setAliasTexParameters();

    int x = 0;
    while (x <= visibleSize.width) {
        int y = 0;
        while (y <= visibleSize.height) {
            Sprite* back = Sprite::createWithSpriteFrame(spFrame);
            back->setPosition(Point(x, y));
            spBatch->addChild(back);

            y += 128;
        }
        x += 128;
    }

    this->addChild(spBatch, 0);
*/

    /*
    // Nend広告
    char apiKey[] = "2cf8ac6a0e0a103324422286335cc29c48a110d7";
    char spotID[] = "140708";
    NendModule::createNADViewBottom(apiKey, spotID);

    char iconApiKey[] = "ddec5c41b857c8a804b1ee46c493c32e8c044be5";
    char iconSpotID[] = "143186";
    NendIconModule::createNADIconLoader(iconApiKey, iconSpotID);
    NendIconModule::createNADIconViewTop();
    NendIconModule::load();
    */

    // タッチイベント系
    // イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create();
    
    // イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    
    // タッチメソッド設定
    listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
    
    // 優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    return true;
}

bool TitleScene::onTouchBegan(Touch* touch, Event* event) {

    if (_viewModel->_play1->getBoundingBox().containsPoint(touch->getLocation())) {
        _touching = _viewModel->_play1;
        return true;
    }
    if (_viewModel->_play3->getBoundingBox().containsPoint(touch->getLocation())) {
        _touching = _viewModel->_play3;
        return true;
    }
    
    return false;
}

void TitleScene::onTouchEnded(Touch* touch, Event* event) {
    
    if (_viewModel->_play1->getBoundingBox().containsPoint(touch->getLocation())) {
        if (_touching == _viewModel->_play1) {
            startGame(1);
        }
    }
    if (_viewModel->_play3->getBoundingBox().containsPoint(touch->getLocation())) {
        if (_touching == _viewModel->_play3) {
            startGame(3);
        }
    }
}

void TitleScene::startGame(int rule) {

    // 何枚ルールかを設定する
    SolitaireKlondikeViewModel::_dropCount = rule;

    // タッチイベントを全て無効化
    this->getEventDispatcher()->removeAllEventListeners();
    
    // シーン切り替え
    Scene* gameScene = SolitaireKlondikeScene::createScene();
    // FadeIn&Outで切り替え
    TransitionFade* fade = TransitionFade::create(0.5, gameScene);
    
    if (fade) {
        Director::getInstance()->replaceScene(fade);
    }
}

