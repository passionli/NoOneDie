#ifndef __GAMEFAILURE_SCENE_H__
#define __GAMEFAILURE_SCENE_H__

#include "cocos2d.h"

class GameFailureScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();  
	virtual void keyBackClicked();//¼àÌýAndroid ·µ»Ø¼ü
    static cocos2d::CCScene* scene();
    
    void menuShareCallback(CCObject* pSender);
	void menuReturnCallback(CCObject* pSender);
	void menuRetryCallback(CCObject* pSender);
    CREATE_FUNC(GameFailureScene);
};

#endif // __HELLOWORLD_SCENE_H__
