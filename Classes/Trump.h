#include "cocos2d.h"

class TrumpData;

class Trump : public cocos2d::Sprite {
public:
    // サイズ定数
    static const int SIZE_TEXTURE_X = 30;
    static const int SIZE_TEXTURE_Y = 46;

    Trump(TrumpData* trump);

    TrumpData* getData();

    void refresh();

    /**
    * 配布するときのtween
    */
    void tweenOnDeal(float delayTime, float duration, cocos2d::Point distPos, const std::function<void ()> &func);

    /**
    * めくるtween
    */
    void flip(const std::function<void ()> &func);

    void setLocalZOrder(int localZOrder);

private:
    TrumpData* _data;
};