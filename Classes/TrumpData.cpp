#include "TrumpData.h"

TrumpData::TrumpData(int suit, int value, bool isReverse) {
    _suit = suit;
    _value = value;
    _isReverse = isReverse;
}

int TrumpData::getSuit() {
    return _suit;
}

int TrumpData::getValue() {
    return _value;
}

int TrumpData::getFieldX() {
    return _fieldX;
}

void TrumpData::setFieldX(int x) {
    _fieldX = x;
}

int TrumpData::getFieldY() {
    return _fieldY;
}

void TrumpData::setFieldY(int y) {
    _fieldY = y;
}

bool TrumpData::isReverse() {
    return _isReverse;
}

void TrumpData::setReverse(bool isReverse) {
    _isReverse = isReverse;
}
