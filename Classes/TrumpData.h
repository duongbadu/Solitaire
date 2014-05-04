#include "cocos2d.h"

class TrumpData : public cocos2d::Ref {
public:
    TrumpData(int suit, int value, bool isReverse);

    int getSuit();

    int getValue();

    int getFieldX();

    void setFieldX(int x);

    int getFieldY();

    void setFieldY(int y);

    bool isReverse();

    void setReverse(bool isReverse);

private:
    int _suit;

    int _fieldX;

    int _fieldY;

    int _value;

    bool _isReverse;

};
