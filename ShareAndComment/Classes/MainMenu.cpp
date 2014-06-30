#include "MainMenu.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//add logo
	CCSprite *logo=CCSprite::create("logo.png");
	logo->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-logo->getContentSize().height/2-30));
	this->addChild(logo);
	//add football
	CCSprite *football=CCSprite::create("football.png");
	football->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-logo->getContentSize().height-35));
	this->addChild(football);

	CCMenuItemImage *pNormalItem = CCMenuItemImage::create(
                                        "lianxi.png",
                                        "lianxi_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuNormalCallback));
	CCMenuItemImage *pCrazyItem = CCMenuItemImage::create(
                                        "yeyu.png",
                                        "yeyu_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuCrazyCallback));
	CCMenuItemImage *pProfessionalItem = CCMenuItemImage::create(
                                        "zhiye.png",
                                        "zhiye_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuCrazyCallback));
	CCMenuItemImage *pWorldCupItem = CCMenuItemImage::create(
                                        "shijie.png",
                                        "shijie_selected.png",
                                        this,
                                        menu_selector(MainMenu::menuCrazyCallback));
	//每个按钮相距
	int btnApart=35;
	//按钮偏离屏幕y轴中心距离
	int offset=-80;
	pNormalItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+ visibleSize.height/2+pNormalItem->getContentSize().height/2+btnApart+pCrazyItem->getContentSize().height+btnApart/2+offset));
	pCrazyItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+ visibleSize.height/2+pCrazyItem->getContentSize().height/2+btnApart/2+offset));
	pProfessionalItem->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-btnApart/2-pProfessionalItem->getContentSize().height/2+offset));
	pWorldCupItem->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-btnApart/2-pProfessionalItem->getContentSize().height-btnApart-pWorldCupItem->getContentSize().height/2+offset));

	CCMenuItemImage *pRateItem = CCMenuItemImage::create(
                                        "rate.png",
                                        "rate.png",
                                        this,
                                        menu_selector(MainMenu::menuRateCallback));
	pRateItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+20+pRateItem->getContentSize().height/2));

	CCMenu* pMenu = CCMenu::create(pNormalItem,pCrazyItem,pProfessionalItem,pWorldCupItem,pRateItem,NULL);
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
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,GameFailureScene::scene(), false));
}

void MainMenu::keyBackClicked()
{
	CCDirector::sharedDirector()->end();	
}
