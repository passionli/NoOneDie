#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayerColor
{
public:
	static int score;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void keyBackClicked();//¼àÌýAndroid ·µ»Ø¼ü
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuNormalCallback(CCObject* pSender);
	void menuCrazyCallback(CCObject* pSender);
	void menuRateCallback(CCObject* pSender);
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __HELLOWORLD_SCENE_H__
