#include "SolitaireKlondikeScene.h"
#include "BlankCard.h"
#include "Trump.h"
#include "TrumpData.h"
#include "TrumpModel.h"
#include "SolitaireKlondikeViewModel.h"
//#include "NendModule.h"
//#include "NendIconModule.h"

USING_NS_CC;

// 場札の座標
const float POS_FIELD_START_X = 50;
const float POS_FIELD_OFFSET_X = 90;
const float POS_FIELD_START_Y = 570;
const float POS_FIELD_OFFSET_Y = -50;

// 捨てるとこの座標
const float POS_DROP_START_X = 50;
const float POS_DROP_OFFSET_X = 90;
const float POS_DROP_START_Y = 730;

// 山札の座標
const float POS_STOCK_START_Y = 730;
const float POS_STOCK_OFFSET_X = -30;

// tween
const float TWEEN_CARD_MOVE_SPEED = 0.1; // ドラッグした時のtweenスピード

// ドラッグ中のZ値(一番手前に表示したいので)
const int Z_DRAGGING = 999;

Scene* SolitaireKlondikeScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SolitaireKlondikeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SolitaireKlondikeScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage* closeItem;
    closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(SolitaireKlondikeScene::menuCloseCallback, this));

    closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
            origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    _isTouchCard = true;

    // ViewModelの生成
    _viewModel = new SolitaireKlondikeViewModel();

    // トランプ配置
    int index = 0;
    for (int x = 0; x < SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS; x++) {

        // 場札にブランク枠を表示する
        BlankCard* blank = _viewModel->getFieldBlank(x);
        blank->setPosition(Point((POS_FIELD_OFFSET_X * x) + POS_FIELD_START_X, POS_FIELD_START_Y));

        this->addChild(blank, -1);

        // 場札
        Vector<Trump*>* rows = _viewModel->getFieldRow(x);

        int y = 0;
        for (Trump* trump : *rows) {

            // 初期位置は画面外
            trump->setPosition(Point(visibleSize.width, -200));
            this->addChild(trump, y);

            // 配置tween
            Point distPos = Point((POS_FIELD_OFFSET_X * x) + POS_FIELD_START_X //
                    , (POS_FIELD_OFFSET_Y * y) + POS_FIELD_START_Y);

            if ((x == SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS - 1)
                    && (trump == rows->back())) {

                // 最後に配布するカードのみ、めくるtweenをするメソッドをcallbackで呼んでもらう
                trump->tweenOnDeal(index * 0.05, // delay
                        TWEEN_CARD_MOVE_SPEED // duration
                        , distPos, CC_CALLBACK_0(SolitaireKlondikeScene::flipFieldCard, this));

            } else {

                trump->tweenOnDeal(index * 0.05, // delay
                        TWEEN_CARD_MOVE_SPEED // duration
                        , distPos, nullptr);
            }

            y++;
            index++;
        }
    }

    // 捨てるとこの表示
    for (int x = 0; x < SolitaireKlondikeViewModel::COUNT_DROP_MAX_ROWS; x++) {

        // 場札にブランク枠を表示する
        BlankCard* blank = _viewModel->getDropBlank(x);
        blank->setPosition(Point((POS_DROP_OFFSET_X * x) + POS_DROP_START_X, POS_DROP_START_Y));

        this->addChild(blank, -1);
    }

    // 山札の表示
    // ブランク枠
    BlankCard* blank = _viewModel->getStockBlank();
    blank->setPosition(Point( //
            (POS_FIELD_START_X //
                    + (POS_FIELD_OFFSET_X * (SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS - 1))) //
            , POS_STOCK_START_Y));
    this->addChild(blank, -1);

    // 山札
    for (Trump* stock : *this->_viewModel->getCloseStockCards()) {

        stock->setPosition(Point( //
                (POS_FIELD_OFFSET_X * (SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS - 1)) + POS_FIELD_START_X //
                , POS_STOCK_START_Y));

        this->addChild(stock, stock->getData()->getFieldY());
    }

    // タッチイベント系
    // イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create();

    // イベントを飲み込むかどうか
    listener->setSwallowTouches(true);

    // タッチメソッド設定
    listener->onTouchBegan = CC_CALLBACK_2(SolitaireKlondikeScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SolitaireKlondikeScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SolitaireKlondikeScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SolitaireKlondikeScene::onTouchCancelled, this);

    // 優先度100でディスパッチャーに登録
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);

    // Nend広告
    /*
    char apiKey[] = "2cf8ac6a0e0a103324422286335cc29c48a110d7";
    char spotID[] = "140708";
    NendModule::createNADViewTop(apiKey, spotID);

    char iconApiKey[] = "ddec5c41b857c8a804b1ee46c493c32e8c044be5";
    char iconSpotID[] = "143186";
    NendIconModule::createNADIconLoader(iconApiKey, iconSpotID);
    NendIconModule::createNADIconView(ccp(200, 170));
    NendIconModule::createNADIconView(ccp(350, 170));
    NendIconModule::createNADIconView(ccp(500, 170));
    NendIconModule::load();
    */

    return true;
}

bool SolitaireKlondikeScene::onTouchBegan(Touch* touch, Event* event) {

    if (_isTouchCard) {
        return false;
    }

    _isTouchCard = false;
    _isMovingCard = false;
    _touchingCard = nullptr;

    Point location = touch->getLocation();
    Trump* dragCandidate = nullptr;
    int lastZOrder = -1;

    // 場札のどれかをタッチしたか
    for (Trump* trump: *_viewModel->getFieldCards()) {

        // 裏向きはドラッグNG
        if (trump->getData()->isReverse()) {
            continue;
        }
        // tween中はおさわり禁止
        if (trump->getNumberOfRunningActions() > 0) {
            continue;
        }

        if (trump->getBoundingBox().containsPoint(location)) {
            // Z値がより大きいものをドラッグ対象とする(一番手前をドラッグできるようにするため)
            if (trump->getLocalZOrder() > lastZOrder) {
                dragCandidate = trump;
                lastZOrder = trump->getLocalZOrder();
            }
        }
    }

    // 場札はタッチしなかった
    if (dragCandidate == nullptr) {
        // 山札(めくったやつ)をタッチしたか調査
        Trump* stock = _viewModel->getDraggableStockRow();
        if (stock != nullptr) {
            // tween中はおさわり禁止
            if (stock->getNumberOfRunningActions() == 0) {
                if (stock->getBoundingBox().containsPoint(location)) {
                    dragCandidate = stock;
                }
            }
        }
    }

    // 山札(めくったやつ)はタッチしなかった
    if (dragCandidate == nullptr) {
        // 山札(裏向きのやつ)をタッチしたか調査
        for (Trump* trump: *_viewModel->getCloseStockCards()) {
            // tween中はおさわり禁止
            if (trump->getNumberOfRunningActions() == 0) {
                if (trump->getBoundingBox().containsPoint(location)) {
                    dragCandidate = trump;
                    break;
                }
            }
        }
    }

    // ドラッグ対象のカードがあった
    if (dragCandidate != nullptr) {
        _isTouchCard = true;
        _touchingCard = dragCandidate;
        _touchStartPos = dragCandidate->getPosition();
        _touchPos = Point(
                (dragCandidate->getPosition().x + (dragCandidate->getScaleX() / 2)) - location.x //xの中心点
                , (dragCandidate->getPosition().y + (dragCandidate->getScaleY() / 2)) - location.y //yの中心点
        );

        int index = 0;
        for (Trump* dragging : *this->getDraggingGroup()) {

            // Z軸書き換え
            dragging->setLocalZOrder(Z_DRAGGING + index);

            index++;
        }
        return true;
    }

    // 山札のブランク枠をタップしたか
    if (_viewModel->getStockBlank()->getBoundingBox().containsPoint(location)) {
        _isTouchCard = true;
        return true;
    }

    return false;
}

void SolitaireKlondikeScene::onTouchMoved(Touch* touch, Event* event) {

    if (!_isTouchCard || _touchingCard == nullptr) {
        return;
    }

    _isMovingCard = true;

    // ドラッグ中のトランプより下(Y軸で)をまとめてドラッグする
    int index = 0;
    for (Trump* trump : *this->getDraggingGroup()) {
        Point dragOffset = Point(0, index * POS_FIELD_OFFSET_Y);
        trump->setPosition(touch->getLocation() + _touchPos + dragOffset);
        index++;
    }
}

void SolitaireKlondikeScene::onTouchEnded(Touch* touch, Event* event) {

    if (!_isTouchCard) {
        return;
    }

    Vector<Trump*>* dragTrumps = this->getDraggingGroup();

    // ドラッグ完了tween後にさわるTrumpたち (callbackできないので)
    _draggedTrumps = new Vector<Trump*>();

    // タッチしているカードが無い ＝ 山札のブランク枠をタッチした
    if (!_isMovingCard) {
        if (_touchingCard == nullptr) {
            onSingleTapBlankStockCard();
            _isTouchCard = false;
            return;
        }
    }

    // 場札のどの列でタッチが完了されたか
    //int draggingX = (int) floor((touch->getLocation().x - POS_FIELD_START_X) / POS_FIELD_OFFSET_X);

    // 場札の上に重ねられるか
    for (Trump* trump: *_viewModel->getFieldCards()) {
        // ドラッグ中トランプの場合
        if (dragTrumps->contains(trump)) {
            continue;
        }
        // 判定対象となる列以外は除外 (2枚同時にヒットした場合など)
        /*
        if (trump->getData()->getFieldX() != draggingX) {
            continue;
        }
        */

        // ドラッグ中のカードの下にカードが存在していない場合(当たり判定)
        if (!_touchingCard->getBoundingBox().intersectsRect(trump->getBoundingBox())) {
            continue;
        }
        // 一番手前のカードかどうかの判定
        if (!_viewModel->isLast(trump->getData()->getFieldX(), trump->getData()->getFieldY())) {
            continue;
        }
        // クロンダイクルールで重ねられるか
        if (!_viewModel->isKlondikeSequence(trump, dragTrumps->at(0))) {
            continue;
        }

        // 移動
        if (dragTrumps->size() > 0) {
            for (Trump* dragging : *dragTrumps) {
                moveCard(dragging, trump->getData()->getFieldX());
            }
            // ドラッグできたらここでおしまい
            return;
        }
    }

    // フィールドにあるブランクの上に重ねられるか
    for (BlankCard* blank: *_viewModel->getFieldBlanks()) {

        // ドラッグ中のカードの下にブランクが存在していない場合(当たり判定)
        if (!_touchingCard->getBoundingBox().intersectsRect(blank->getBoundingBox())) {
            continue;
        }
        // その列にカードがある場合
        if (_viewModel->getFieldRow(blank->getX())->size() != 0) {
            continue;
        }
        // Kではない場合
        if (dragTrumps->at(0)->getData()->getValue() != 13) {
            continue;
        }

        // 移動
        if (dragTrumps->size() > 0) {
            for (Trump* dragging : *dragTrumps) {
                moveCard(dragging, blank->getX());
            }
            // ドラッグできたらここでおしまい
            return;
        }
    }

    // 組札(捨てるとこ)にあるブランクの上に重ねられるか
    for (BlankCard* blank: *_viewModel->getDropBlanks()) {

        // ドラッグ中のカードの下にブランクが存在していない場合(当たり判定)
        if (!_touchingCard->getBoundingBox().intersectsRect(blank->getBoundingBox())) {
            continue;
        }
        // その列にカードがある場合
        if (_viewModel->getDropRow(blank->getX())->size() != 0) {
            continue;
        }
        // 2枚以上ドラッグしている場合
        if (dragTrumps->size() > 1) {
            continue;
        }
        // Aではない場合
        if (dragTrumps->at(0)->getData()->getValue() != 1) {
            continue;
        }

        // 移動
        if (dragTrumps->size() > 0) {
            for (Trump* dragging : *dragTrumps) {
                moveCard(dragging //
                        , dragging->getData()->getSuit() + SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS);
            }
            // ドラッグできたらここでおしまい
            return;
        }
    }

    // 組札の上に重ねられるか
    for (Trump* trump: *_viewModel->getDropCards()) {
        // ドラッグ中トランプの場合
        if (dragTrumps->contains(trump)) {
            continue;
        }
        // 判定対象となる列以外は除外 (2枚同時にヒットした場合など)
        /*
        if (trump->getData()->getFieldX() != draggingX) {
            continue;
        }
        */

        // ドラッグ中のカードの下にカードが存在していない場合(当たり判定)
        if (!_touchingCard->getBoundingBox().intersectsRect(trump->getBoundingBox())) {
            continue;
        }
        // 2枚以上ドラッグしている場合
        if (dragTrumps->size() > 1) {
            continue;
        }
        // クロンダイクルールで捨てられるか
        if (!_viewModel->isKlondikeDrop(trump, dragTrumps->at(0))) {
            continue;
        }

        // 移動
        if (dragTrumps->size() > 0) {
            for (Trump* dragging : *dragTrumps) {
                moveCard(dragging //
                        , dragging->getData()->getSuit() + SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS);
            }
            // ドラッグできたらここでおしまい
            return;
        }
    }

    // ドラッグではないシングルタップの場合
    if (!_isMovingCard) {
        _touchingCard->setLocalZOrder(_touchingCard->getData()->getFieldY());

        // タップ中カード
        int x = _touchingCard->getData()->getFieldX();

        if ((x < SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS)
                || (x == SolitaireKlondikeViewModel::INDEX_STOCK_OPEN_X)) {

            // 場札、またはめくった山札の場合
            // 一番手前のカードのみ有効
            if (_viewModel->isLast(x, _touchingCard->getData()->getFieldY())) {
                onSingleTapOpenCard();
                return;
            }

        } else if (x == SolitaireKlondikeViewModel::INDEX_STOCK_CLOSE_X) {

            // 山札(裏向きのやつ)の場合
            onSingleTapClosedStockCard();
            return;
        }
    }

    // ドラッグ判定NG
    if (dragTrumps->size() == 0) {
        _isTouchCard = false;
        _touchingCard->setLocalZOrder(_touchingCard->getData()->getFieldY());
        return;
    }
    int index = 0;
    for (Trump* dragging : *dragTrumps) {

        Point posOffset = Point(0, index * POS_FIELD_OFFSET_Y);
        // ドラッグ前の座標に戻す
        MoveTo* move = MoveTo::create(TWEEN_CARD_MOVE_SPEED, _touchStartPos + posOffset);
        EaseSineOut* ease = EaseSineOut::create(move);
        CallFunc* call1 = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::onCompleteDragTween, this));
        CallFunc* call2 = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::endTween, this));
        Sequence* seq = Sequence::create(ease, call1, call2, nullptr);
        dragging->runAction(seq);

        _draggedTrumps->pushBack(dragging);

        index++;
    }
}

// カードの移動
void SolitaireKlondikeScene::moveCard(Trump* card, int toX) {

    // viewmodelにあるデータの書き換え
    Trump* moveCard = _viewModel->moveCard(card, toX);

    // Z軸書き換え
    //moveCard->setLocalZOrder(moveCard->getData()->getFieldY());

    // 移動先の座標
    float snapPosX;
    float snapPosY;

    if (toX < SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS) {
        // 場札への移動
        snapPosX = (POS_FIELD_OFFSET_X * moveCard->getData()->getFieldX()) + POS_FIELD_START_X;
        snapPosY = (POS_FIELD_OFFSET_Y * moveCard->getData()->getFieldY()) + POS_FIELD_START_Y;
    } else if (toX < SolitaireKlondikeViewModel::INDEX_STOCK_OPEN_X) {
        // 組札への移動
        snapPosX = (POS_DROP_OFFSET_X //
                * (moveCard->getData()->getFieldX() - SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS)) //
                + POS_DROP_START_X;
        snapPosY = POS_DROP_START_Y;
    } else if (toX < SolitaireKlondikeViewModel::INDEX_STOCK_CLOSE_X) {
        // 山札(めくったやつ)への移動
        snapPosX = _viewModel->getFieldBlank(5)->getPosition().x //
                + (POS_STOCK_OFFSET_X * moveCard->getData()->getFieldY());
        snapPosY = POS_DROP_START_Y;
    }

    // tween
    MoveTo* move = MoveTo::create(TWEEN_CARD_MOVE_SPEED, Point(snapPosX, snapPosY));
    EaseSineOut* ease = EaseSineOut::create(move);
    CallFunc* call1 = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::onCompleteDragTween, this));
    CallFunc* call2 = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::flipFieldCard, this));
    CallFunc* call3 = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::endTween, this));
    Sequence* seq = Sequence::create(ease, call1, call2, call3, nullptr);
    moveCard->runAction(seq);

    _draggedTrumps->pushBack(moveCard);
}

void SolitaireKlondikeScene::onSingleTapOpenCard() {

    for (int i = 0; i < SolitaireKlondikeViewModel::COUNT_DROP_MAX_ROWS; i++) {

        // Suitが合わない時は除外
        if (_touchingCard->getData()->getSuit() != i) {
            continue;
        }
        int targetX = i + SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS;

        Vector<Trump*>* rows = _viewModel->getFieldRow(targetX);
        if (rows->size() == 0) {
            if (_touchingCard->getData()->getValue() != 1) {
                // まだ一枚も置いていない列に対しては1のカードのみ置ける
                continue;
            }
        } else {
            if (!_viewModel->isKlondikeDrop(rows->back(), _touchingCard)) {
                // 1枚以上置いてある列に対しては、+1の数字カードなら置ける
                continue;
            }
        }

        // Z値を一番手前に書き換え、このカードをドラッグしている扱いにする
        // (tween後にZ値を戻してもらいたいため)
        _touchingCard->setLocalZOrder(Z_DRAGGING);
        _draggedTrumps = new Vector<Trump*>();
        _draggedTrumps->pushBack(_touchingCard);

        // 移動
        moveCard(_touchingCard, targetX);
        return;
    }
    _isTouchCard = false;
}

void SolitaireKlondikeScene::onSingleTapClosedStockCard() {

    // 戻す
    hideOpenStockCard();

    // めくる
    // 何枚ルールかを取得して、その分ループする
    int zOrder = Z_DRAGGING;
    for (int i = 0; i < _viewModel->getDropCount(); i++) {

        // 山札が無い
        if (_viewModel->getCloseStockCards()->size() == 0) {
            break;
        }

        Trump* card = _viewModel->getCloseStockCards()->at(0);

        // 表向きにしてから
        card->getData()->setReverse(false);
        card->refresh();
        card->setLocalZOrder(zOrder);

        moveCard(card, SolitaireKlondikeViewModel::INDEX_STOCK_OPEN_X);

        zOrder++;
    }
}

void SolitaireKlondikeScene::onSingleTapBlankStockCard() {

    // 戻す
    hideOpenStockCard();

    // 隠しているカードを表示する
    Vector<Trump*>* row = _viewModel->getFieldRow(SolitaireKlondikeViewModel::INDEX_STOCK_HIDDEN_X);

    while (row->size() > 0) {

        Trump* moveCard = _viewModel->moveCard(row->at(0), SolitaireKlondikeViewModel::INDEX_STOCK_CLOSE_X);

        moveCard->stopAllActions();

        // 裏向きにしてから再表示
        moveCard->getData()->setReverse(true);
        moveCard->refresh();

        // Z order
        moveCard->setLocalZOrder(moveCard->getData()->getFieldY());

        moveCard->setPosition(Point( //
                (POS_FIELD_OFFSET_X * (SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS - 1)) + POS_FIELD_START_X //
                , POS_STOCK_START_Y));
    }
}

void SolitaireKlondikeScene::hideOpenStockCard() {

    // 戻す
    Vector<Trump*>* row = _viewModel->getFieldRow(SolitaireKlondikeViewModel::INDEX_STOCK_OPEN_X);

    while (row->size() > 0) {

        Trump* moveCard = _viewModel->moveCard(row->at(0), SolitaireKlondikeViewModel::INDEX_STOCK_HIDDEN_X);

        // 隠しとく
        DelayTime* delay = DelayTime::create(TWEEN_CARD_MOVE_SPEED);
        CallFunc* hideFunc = CallFunc::create(CC_CALLBACK_0(SolitaireKlondikeScene::hideCard, this, moveCard));
        Sequence* seq = Sequence::create(delay, hideFunc, nullptr);

        moveCard->runAction(seq);
    }
}

void SolitaireKlondikeScene::hideCard(Trump* card) {

    card->setPosition(Point(-200, -200));
}

void SolitaireKlondikeScene::onCompleteDragTween() {

    for (Trump* dragged : *_draggedTrumps) {

        // Z軸書き換え
        dragged->setLocalZOrder(dragged->getData()->getFieldY());
    }
}

void SolitaireKlondikeScene::flipFieldCard() {

    for (int x = 0; x < SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS; x++) {

        // 場札
        Vector<Trump*>* rows = _viewModel->getFieldRow(x);

        if (rows->size() == 0) {
            continue;
        }
        // 表向きならなんもしない
        if (!rows->back()->getData()->isReverse()) {
            continue;
        }

        // 表向きか、裏向きかのデータを逆に
        rows->back()->getData()->setReverse(!rows->back()->getData()->isReverse());

        // めくるtween
        rows->back()->flip(CC_CALLBACK_0(SolitaireKlondikeScene::endTween, this));
    }
}

void SolitaireKlondikeScene::endTween() {

    _isTouchCard = false;
}

void SolitaireKlondikeScene::onTouchCancelled(Touch* touch, Event* event) {
    //Point location = touch->getLocation();
    //CCLOG("onTouchCancelled x:%f, y:%f", location.x, location.y);
}

Vector<Trump*>* SolitaireKlondikeScene::getDraggingGroup() {

    Vector<Trump*>* trumps = new Vector<Trump*>();

    if (!_isTouchCard || _touchingCard == nullptr) {
        return trumps;
    }
    // ドラッグ中の列をまるごと取り出す
    int x = _touchingCard->getData()->getFieldX();

    if (x < SolitaireKlondikeViewModel::COUNT_FIELD_MAX_ROWS) {

        Vector<Trump*>* rows = _viewModel->getFieldRow(x);

        // ドラッグ中のトランプより下(Y軸で)を詰めて返す
        for (int y = 0; y < rows->size(); y++) {
            if (rows->at(y)->getData()->getFieldY() >= _touchingCard->getData()->getFieldY()) {
                trumps->pushBack(rows->at(y));
            }
        }

    } else if ((x >= SolitaireKlondikeViewModel::INDEX_STOCK_OPEN_X)
            && (x < SolitaireKlondikeViewModel::INDEX_STOCK_CLOSE_X)) {

        // 山札(めくったやつ)からのドラッグの場合
        trumps->pushBack(_touchingCard);
    }
    return trumps;
}

void SolitaireKlondikeScene::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
