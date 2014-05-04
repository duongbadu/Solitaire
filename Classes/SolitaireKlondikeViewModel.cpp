#include "SolitaireKlondikeViewModel.h"
#include "BlankCard.h"
#include "Trump.h"
#include "TrumpData.h"
#include "TrumpModel.h"

USING_NS_CC;

/*
*
* 持っているデータについて
*
* 組札:捨てていくところ(4列)    山札(めくったやつ)    山札(裏向き)    隠し
* x:7〜10 y:0〜12               x:11 y:0〜2           x:12 y:0〜      x:13 y:0〜
*
* 場札(7列)
* x:0〜6 y:0〜12
*
*
* ※隠し
* 山札をめくった時、すでにめくった山札があった場合にそれを隠しておくための列
*
*/
SolitaireKlondikeViewModel::SolitaireKlondikeViewModel() {

    // TODO セーブデータから読む
    init();
}

void SolitaireKlondikeViewModel::init() {

    // シャッフルした全部のカードを受け取る
    TrumpModel* model = new TrumpModel();
    Vector<TrumpData*>* trumpData = model->dealFull();

    // 場札データを作る (x:0〜6)
    int index = 0;
    for (int x = 0; x < COUNT_FIELD_MAX_ROWS; x++) {

        _cards[x] = new Vector<Trump*>();
        _fieldBlank[x] = new BlankCard(true, x, 0);

        int y = 0;
        while (y <= x) {
            trumpData->at(index)->setFieldX(x);
            trumpData->at(index)->setFieldY(y);

            Trump* card = new Trump(trumpData->at(index));
            _cards[x]->pushBack(card);

            y++;
            index++;
        }
    }

    // 組札データを作る (x:7〜10)
    for (int x = INDEX_DROP_X; x < INDEX_DROP_X + COUNT_DROP_MAX_ROWS; x++) {
        _cards[x] = new Vector<Trump*>();
    }
    for (int i = 0; i < COUNT_DROP_MAX_ROWS; i++) {
        _dropBlank[i] = new BlankCard(false, INDEX_DROP_X + i, 0);
    }

    // 山札(めくったやつ)データを作る (x:11)
    _cards[INDEX_STOCK_OPEN_X] = new Vector<Trump*>();

    // 山札(裏向き)データを作る(x:12)
    _cards[INDEX_STOCK_CLOSE_X] = new Vector<Trump*>();

    int y = 0;
    while (index < TrumpModel::COUNT_ALL_CARDS) {

        TrumpData* data = trumpData->at(index);
        data->setFieldX(INDEX_STOCK_CLOSE_X);
        data->setFieldY(y);

        Trump* card = new Trump(data);

        _cards[INDEX_STOCK_CLOSE_X]->pushBack(card);

        index++;
        y++;
    }
    _stockBlank = new BlankCard(false, INDEX_STOCK_CLOSE_X, 0);

    // 山札データ(めくったやつを隠すとこ)を作る(x:13)
    _cards[INDEX_STOCK_HIDDEN_X] = new Vector<Trump*>();
}

Vector<Trump*>* SolitaireKlondikeViewModel::getFieldCards() {

    Vector<Trump*>* cards = new Vector<Trump*>();
    for (int x = 0; x < COUNT_FIELD_MAX_ROWS; x++) {
        for (Trump* trump : *_cards[x]) {
            cards->pushBack(trump);
        }
    }
    return cards;
}

Vector<Trump*>* SolitaireKlondikeViewModel::getFieldRow(int x) {
    return _cards[x];
}

bool SolitaireKlondikeViewModel::isLast(int x, int y) {

    Vector<Trump*>* row = _cards[x];

    return (row->size() == 0) ? true : ((row->size() - 1) == y);
}

BlankCard* SolitaireKlondikeViewModel::getFieldBlank(int x) {
    return _fieldBlank[x];
}

Vector<BlankCard*>* SolitaireKlondikeViewModel::getFieldBlanks() {

    Vector<BlankCard*>* blanks = new Vector<BlankCard*>();
    for (int x = 0; x < COUNT_FIELD_MAX_ROWS; x++) {
        blanks->pushBack(_fieldBlank[x]);
    }
    return blanks;
}

Vector<Trump*>* SolitaireKlondikeViewModel::getDropCards() {

    Vector<Trump*>* cards = new Vector<Trump*>();
    for (int x = COUNT_FIELD_MAX_ROWS; x < INDEX_STOCK_OPEN_X; x++) {
        for (Trump* trump : *_cards[x]) {
            cards->pushBack(trump);
        }
    }
    return cards;
}

Vector<Trump*>* SolitaireKlondikeViewModel::getDropRow(int x) {
    return _cards[x];
}

BlankCard* SolitaireKlondikeViewModel::getDropBlank(int x) {
    return _dropBlank[x];
}

Vector<BlankCard*>* SolitaireKlondikeViewModel::getDropBlanks() {

    Vector<BlankCard*>* blanks = new Vector<BlankCard*>();
    for (int x = 0; x < COUNT_DROP_MAX_ROWS; x++) {
        blanks->pushBack(_dropBlank[x]);
    }
    return blanks;
}

Trump* SolitaireKlondikeViewModel::getDraggableStockRow() {

    if (_cards[INDEX_STOCK_OPEN_X]->size() > 0) {
        return _cards[INDEX_STOCK_OPEN_X]->back();
    }
    return nullptr;
}

Vector<Trump*>* SolitaireKlondikeViewModel::getCloseStockCards() {
    return _cards[INDEX_STOCK_CLOSE_X];
}

BlankCard* SolitaireKlondikeViewModel::getStockBlank() {
    return _stockBlank;
}

Trump* SolitaireKlondikeViewModel::moveCard(Trump* card, int toX) {

    int fromX = card->getData()->getFieldX();
    int fromY = card->getData()->getFieldY();

    Trump* moveCard = _cards[fromX]->at(fromY);

    // 移動先に追加
    _cards[toX]->pushBack(moveCard);
    moveCard->getData()->setFieldX(toX);
    moveCard->getData()->setFieldY(_cards[toX]->size() - 1);

    // 移動元から削除
    _cards[fromX]->erase(fromY);

    // 削除したY値より大きいY値をマイナス1する
    for (Trump* card : *_cards[fromX]) {
        if (card->getData()->getFieldY() > fromY) {
            card->getData()->setFieldY(card->getData()->getFieldY() - 1);
        }
    }


    // TODO 移動履歴スタックを積む


    return moveCard;
}

int SolitaireKlondikeViewModel::getDropCount() {
    return _dropCount;
}

// back(奥)、front(手前)で重なる2枚のカードが
// クロンダイクルールで重ねられるかを判定
bool SolitaireKlondikeViewModel::isKlondikeSequence(Trump* back, Trump* front) {

    // Suitの判定
    // クラブ(0)かスペード(3)
    if (back->getData()->getSuit() == 0 || back->getData()->getSuit() == 3) {

        if (front->getData()->getSuit() == 0 || front->getData()->getSuit() == 3) {
            return false;
        }
    } else {

        // ダイア(1)かハート(2)
        if (front->getData()->getSuit() == 1 || front->getData()->getSuit() == 2) {
            return false;
        }
    }

    // 数字の判定
    return ((back->getData()->getValue() - 1) == front->getData()->getValue());
}

// back(奥)、front(手前)で重なる2枚のカードが
// クロンダイクルールで捨てられるかを判定
bool SolitaireKlondikeViewModel::isKlondikeDrop(Trump* back, Trump* front) {

    // Suitの判定
    if (front->getData()->getSuit() != back->getData()->getSuit()) {
        return false;
    }

    // 数字の判定
    return ((back->getData()->getValue() + 1) == front->getData()->getValue());
}

void SolitaireKlondikeViewModel::saveData() {


    ValueMap vmap;
    vmap["hoge"] = Value(1);
}

// static
int SolitaireKlondikeViewModel::_dropCount;
