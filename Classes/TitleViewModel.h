#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class Trump;

class TitleViewModel : public cocos2d::Ref {
public:
    TitleViewModel();
    
    cocos2d::LabelBMFont* _title;
    
    cocos2d::LabelBMFont* _label1;
    
    cocos2d::extension::Scale9Sprite* _play1;
    
    Trump* _play1card1;
    
    cocos2d::LabelBMFont* _label3;
    
    cocos2d::extension::Scale9Sprite* _play3;
    
    Trump* _play3card1;
    
    Trump* _play3card2;
    
    Trump* _play3card3;
    
};
