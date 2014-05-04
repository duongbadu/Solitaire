#include "cocos2d.h"

class TitleViewModel;

class TitleScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    CREATE_FUNC(TitleScene);

private:
    TitleViewModel* _viewModel;
    
    cocos2d::Node* _touching;

    void startGame(int rule);
};
