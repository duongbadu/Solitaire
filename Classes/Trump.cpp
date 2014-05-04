#include "Trump.h"
#include "TrumpData.h"

USING_NS_CC;

// Copyright
//
// あひる小屋 様
// http://momomohouse.jugem.jp/
// http://momomohouse.jugem.jp/?page=1&cid=2

// テクスチャのファイル名
const char* NAME_TEXTURE_CLUB = "Trump/Club.png";
const char* NAME_TEXTURE_DIAMOND = "Trump/Diamond.png";
const char* NAME_TEXTURE_HEART = "Trump/Heart.png";
const char* NAME_TEXTURE_SPADE = "Trump/Spade.png";

// カードサイズ
const float SIZE_SPRITE_X = 2.8f; // 元の絵の何倍でゲーム上に表示するか
const float SIZE_SPRITE_Y = 2.8f;

// tween
//const float TWEEN_CARD_MOVE_SPEED = 0.1f; // ドラッグした時のtweenスピード
const float TWEEN_CARD_FLIP_SPEED = 0.3f; // めくる時のtweenスピード

Trump::Trump(TrumpData* trump) {

    _data = trump;
    refresh();
}

TrumpData* Trump::getData() {
    return _data;
}

void Trump::refresh() {

    Sprite::init();

    // テクスチャ名
    std::string textureName;
    switch (_data->getSuit()) {
        case 0:
            textureName = NAME_TEXTURE_CLUB;
            break;
        case 1:
            textureName = NAME_TEXTURE_DIAMOND;
            break;
        case 2:
            textureName = NAME_TEXTURE_HEART;
            break;
        default:
            textureName = NAME_TEXTURE_SPADE;
            break;
    }

    // テクスチャからSpriteを切り出す
    // トランプのテクスチャは1行に7枚入っている
    int x;
    int y;

    if (_data->isReverse()) {
        x = 6;
        y = 1;
    } else {
        x = (_data->getValue() - 1) % 7;
        y = (_data->getValue() > 7) ? 1 : 0;
    }

    Rect rect = Rect(float(x * SIZE_TEXTURE_X), float(y * SIZE_TEXTURE_Y), float(SIZE_TEXTURE_X), float(SIZE_TEXTURE_Y));

    SpriteFrame* spFrame = SpriteFrame::create(textureName, rect);
    spFrame->getTexture()->setAliasTexParameters();

    Sprite::initWithSpriteFrame(spFrame);
    Sprite::setScale(SIZE_SPRITE_X, SIZE_SPRITE_Y);
}

void Trump::tweenOnDeal(float delayTime, float duration, Point distPos, const std::function<void ()> &func) {

    DelayTime* delay = DelayTime::create(delayTime);
    MoveTo* move = MoveTo::create(duration, distPos);
    EaseSineOut* ease = EaseSineOut::create(move);

    Sequence* seq;
    if (func == nullptr) {
        seq = Sequence::create(delay, ease, nullptr);
    } else {
        CallFunc* callBack = CallFunc::create(func);
        seq = Sequence::create(delay, ease, callBack, nullptr);
    }
    Sprite::runAction(seq);
}

void Trump::flip(const std::function<void ()> &func) {

    // 半分までめくる
    OrbitCamera* cam1 = OrbitCamera::create(TWEEN_CARD_FLIP_SPEED / 2.0f, 1, 0, 0.0f, 90.0f, 0, 0);
    Hide* hide = Hide::create();

    // sprite再設定
    CallFunc* refreshFunc = CallFunc::create(CC_CALLBACK_0(Trump::refresh, this));

    // 半分めくったあと
    Show* show = Show::create();
    OrbitCamera* cam2 = OrbitCamera::create(TWEEN_CARD_FLIP_SPEED / 2.0f, 1, 0, 270.0f, 90.0f, 0, 0);

    CallFunc* callBack = CallFunc::create(func);
    Sequence* seq = Sequence::create(cam1, hide, refreshFunc, show, cam2, callBack, nullptr);
    Sprite::runAction(seq);
}

void Trump::setLocalZOrder(int localZOrder) {

    Sprite::setLocalZOrder(localZOrder);
    log("Trump Suit: %d, Value: %d, Zorder: %d", _data->getSuit(), _data->getValue(), localZOrder);
}