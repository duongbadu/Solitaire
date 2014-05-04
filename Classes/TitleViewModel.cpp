#include "TitleViewModel.h"
#include "extensions/cocos-ext.h"
#include "Trump.h"
#include "TrumpData.h"

USING_NS_CC;

using namespace extension;

TitleViewModel::TitleViewModel() {

    _title = LabelBMFont::create("Solitaire Klondike", "Font/GD-DOTFONT-DQ-TTF_008.fnt");
    
    _label1 = LabelBMFont::create("     1mode", "Font/GD-DOTFONT-DQ-TTF_008.fnt");
    
    _play1 = Scale9Sprite::create("Trump/Blank.png");
    
    _play1card1 = new Trump(new TrumpData(0, 1, false));
    
    _label3 = LabelBMFont::create("     3mode", "Font/GD-DOTFONT-DQ-TTF_008.fnt");
    
    _play3 = Scale9Sprite::create("Trump/Blank.png");
    
    _play3card1 = new Trump(new TrumpData(1, 1, false));

    _play3card2 = new Trump(new TrumpData(1, 2, false));

    _play3card3 = new Trump(new TrumpData(1, 3, false));
}