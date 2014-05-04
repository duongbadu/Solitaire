#include "cocos2d.h"

class Trump;

class BlankCard;

class SolitaireKlondikeViewModel : public cocos2d::Ref {
public:
    /**
    * 場札の列数
    */
    static const int COUNT_FIELD_MAX_ROWS = 7;

    /**
    * 捨てるとこの列数
    */
    static const int COUNT_DROP_MAX_ROWS = 4;

    /**
    * 山札の列数
    */
    static const int COUNT_STOCK_MAX_ROWS = 3;

    /**
    * 山札(めくったやつ)が入っているXの添字
    */
    static const int INDEX_STOCK_OPEN_X = 11;

    /**
    * 山札(裏向きのやつ)が入っているXの添字
    */
    static const int INDEX_STOCK_CLOSE_X = 12;

    /**
    * 山札(めくったやつを隠すとこ)が入っているXの添字
    */
    static const int INDEX_STOCK_HIDDEN_X = 13;

    /**
    * コンストラクタ
    */
    SolitaireKlondikeViewModel();

    /**
    * 場札を全て返す
    */
    cocos2d::Vector<Trump*>* getFieldCards();

    /**
    * 指定列の場札を返す
    */
    cocos2d::Vector<Trump*>* getFieldRow(int row);

    /**
    * 指定カードがその列で一番手前にあるかどうか
    */
    bool isLast(int x, int y);

    /**
    * 指定列のブランク枠を返す
    */
    BlankCard* getFieldBlank(int x);

    /**
    * 場札のブランク枠を全て返す
    */
    cocos2d::Vector<BlankCard*>* getFieldBlanks();

    /**
    * 組札を全て返す
    */
    cocos2d::Vector<Trump*>* getDropCards();

    /**
    * 指定列の組札を返す
    */
    cocos2d::Vector<Trump*>* getDropRow(int x);

    /**
    * 指定列の組札のブランク枠を返す
    */
    BlankCard* getDropBlank(int x);

    /**
    * 組札のブランク枠を全て返す
    */
    cocos2d::Vector<BlankCard*>* getDropBlanks();

    /**
    * ドラッグ可能な山札を返す
    */
    Trump* getDraggableStockRow();

    /**
    * 山札(裏向きのやつ)を全て返す
    */
    cocos2d::Vector<Trump*>* getCloseStockCards();

    /**
    * 山札のブランク枠を返す
    */
    BlankCard* getStockBlank();

    /**
    * 座標を書き換え、書き換えたオブジェクトを返す
    */
    Trump* moveCard(Trump* card, int toX);

    /**
    * 何枚ルールかを返す
    */
    int getDropCount();

    /*
    * 山札から何枚ずつめくるか(1枚ルールor3枚ルール)
    * Titleシーンで設定する
    */
    static int _dropCount;

    /**
    * back(奥)、front(手前)で重なる2枚のカードが
    * クロンダイクルールで重ねられるかを判定
    */
    bool isKlondikeSequence(Trump* back, Trump* front);

    /**
    * back(奥)、front(手前)で重なる2枚のカードが
    * クロンダイクルールで捨てられるかを判定
    */
    bool isKlondikeDrop(Trump* back, Trump* front);

    void saveData();

private:
    /**
    * データの初期化
    */
    void init();

    static const int COUNT_DATA_X = 16; // cardsを格納する配列数

    static const int INDEX_DROP_X = 7; // 組札が入っているXの添字

    cocos2d::Vector<Trump*>* _cards[SolitaireKlondikeViewModel::COUNT_DATA_X];

    BlankCard* _fieldBlank[SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS];

    BlankCard* _dropBlank[SolitaireKlondikeViewModel::COUNT_DROP_MAX_ROWS];

    BlankCard* _stockBlank;

};
