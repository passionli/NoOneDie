#include "MainMenu.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "IconvString.h"
#include "GameFailureScene.h"
USING_NS_CC;

CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenu *layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }

	this->setKeypadEnabled(true);
	//初始化所有的变量
	MainMenu::score=0;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//add logo
	CCSprite *logo=CCSprite::create("logo.png");
	logo->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-logo->getContentSize().height/2-40));
	this->addChild(logo);
	//add football
	CCSprite *football=CCSprite::create("football.png");
	football->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-logo->getContentSize().height-40-50));
	this->addChild(football);

	CCMenuItemImage *pNormalItem = CCMenuItemImage::create(
                                        "btn.png",
                                        "btn_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuNormalCallback));
	pNormalItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+ visibleSize.height/2));

	CCMenuItemImage *pCrazyItem = CCMenuItemImage::create(
                                        "btn_crazy.png",
                                        "btn_crazy_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuCrazyCallback));
	pCrazyItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+ visibleSize.height/2-pNormalItem->getContentSize().height-50));

	CCMenuItemImage *pRateItem = CCMenuItemImage::create(
                                        "rate.png",
                                        "rate.png",
                                        this,
                                        menu_selector(MainMenu::menuRateCallback));
	pRateItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+20+pRateItem->getContentSize().height/2));

	CCMenu* pMenu = CCMenu::create(pNormalItem,pCrazyItem,pRateItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}


void MainMenu::menuRateCallback(CCObject* pSender)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo( methodInfo,"com/imeiren/game/NoOneDie", "rate", "()V") ;
		
		if (isHave)
		{
			methodInfo.env->CallStaticVoidMethod( methodInfo .classID, methodInfo.methodID);
		}
	#endif
}

void MainMenu::menuCrazyCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,GameFailureScene::scene(), false));
}

void MainMenu::menuNormalCallback(CCObject* pSender)
{
	//for test 
	MainMenu::score++;
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,GameFailureScene::scene(), false));
}

void MainMenu::keyBackClicked()
{
	CCDirector::sharedDirector()->end();	
}
