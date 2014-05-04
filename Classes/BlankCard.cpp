#include "BlankCard.h"

USING_NS_CC;

// テクスチャのファイル名
const char* NAME_TEXTURE_BLANK = "Trump/Blank.png";

// サイズ定数
const int SIZE_TEXTURE_X = 30;
const int SIZE_TEXTURE_Y = 46;

// カードサイズ
const float SIZE_SPRITE_X = 2.75f; // 元の絵の何倍でゲーム上に表示するか
const float SIZE_SPRITE_Y = 2.75f;

BlankCard::BlankCard(bool isField, int x, int y) {

    Sprite::init();

    Rect rect = Rect(0, 0, float(SIZE_TEXTURE_X), float(SIZE_TEXTURE_Y));

    SpriteFrame* spFrame = SpriteFrame::create(NAME_TEXTURE_BLANK, rect);
    spFrame->getTexture()->setAliasTexParameters();

    Sprite::initWithSpriteFrame(spFrame);
    Sprite::setScale(SIZE_SPRITE_X, SIZE_SPRITE_Y);

    _isField = isField;
    _x = x;
    _y = y;
}

bool BlankCard::isField() {
    return _isField;
}

int BlankCard::getX() {
    return _x;
}

int BlankCard::getY() {
    return _y;
}

