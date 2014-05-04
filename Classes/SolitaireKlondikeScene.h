#include "cocos2d.h"

class BlankCard;

class SolitaireKlondikeViewModel;

class Trump;

class SolitaireKlondikeScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SolitaireKlondikeScene);

private:
    SolitaireKlondikeViewModel* _viewModel;

    bool _isTouchCard = false;

    Trump* _touchingCard;

    cocos2d::Point _touchStartPos;

    cocos2d::Point _touchPos;

    /**
    * ただのタップなのかドラッグされたのかの判定に使用
    * カードをタッチ後にfalse、一定量ドラッグされたらtrueにする
    */
    bool _isMovingCard = false;

    void onSingleTapOpenCard();

    void onSingleTapClosedStockCard();

    void onSingleTapBlankStockCard();

    void onCompleteDragTween();

    void flipFieldCard();

    void endTween();

    cocos2d::Vector<Trump*>* _draggedTrumps;

    cocos2d::Vector<Trump*>* getDraggingGroup();

    void moveCard(Trump* card, int toX);

    void hideOpenStockCard();

    void hideCard(Trump* card);

};
