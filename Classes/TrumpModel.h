#include "cocos2d.h"

class TrumpData;

class TrumpModel {
private:
    int getRandom(int count);

public:
    static const int COUNT_SUIT = 13; // スートあたりのカード数

    static const int COUNT_ALL_CARDS = 52; // 全カードの枚数

    cocos2d::Vector<TrumpData*>* dealFull();
};