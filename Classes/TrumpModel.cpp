#include "TrumpModel.h"
#include "TrumpData.h"

USING_NS_CC;

Vector<TrumpData*>* TrumpModel::dealFull() {

    auto sequenceCards = new Vector<TrumpData*>();
    auto shuffleCards = new Vector<TrumpData*>();

    for (int i = 0; i < COUNT_SUIT; i++) {
        // 1から13まで順番に生成する
        sequenceCards->pushBack(new TrumpData(0, i + 1, true));
        sequenceCards->pushBack(new TrumpData(1, i + 1, true));
        sequenceCards->pushBack(new TrumpData(2, i + 1, true));
        sequenceCards->pushBack(new TrumpData(3, i + 1, true));
    }

    for (int i = COUNT_ALL_CARDS; i > 1; i--) {
        // 1回目 : 0〜51 の間
        // 2回目 : 0〜50 の間
        // ...
        // 51回目 : 0〜1 の間
        int index = this->getRandom(i - 1);

        shuffleCards->pushBack(sequenceCards->at(index));
        sequenceCards->erase(index);
    }

    // 52回目 : 0
    shuffleCards->pushBack(sequenceCards->at(0));

    return shuffleCards;
}

int TrumpModel::getRandom(int count) {

    srand((unsigned int) time(NULL)); //seed

    // 0〜countで渡された値 の間でランダム値を生成する
    return rand() % count;
}