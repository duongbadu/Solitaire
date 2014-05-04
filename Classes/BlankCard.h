#include "cocos2d.h"

class BlankCard : public cocos2d::Sprite {
private:
    bool _isField; // 場札かどうか

    int _x;

    int _y;

public:
    BlankCard(bool isField, int x, int y);

    bool isField();

    int getX();

    int getY();

};