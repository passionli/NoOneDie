#include "GameFailureScene.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "IconvString.h"
#include "MainMenu.h"

USING_NS_CC;

CCScene* GameFailureScene::scene()
{
    CCScene *scene = CCScene::create();
    GameFailureScene *layer = GameFailureScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameFailureScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(255,0,0,255)) )
    {
        return false;
    }

	this->setKeypadEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite *train=CCSprite::create("train.png");
	train->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-train->getContentSize().height/2-40));
	this->addChild(train);

	CCSprite *line=CCSprite::create("line.png");
	line->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-train->getContentSize().height-40-50));
	this->addChild(line);

	char *buf=new char[128];
	memset(buf,0,strlen(buf));
	sprintf(buf,"%d s",MainMenu::score);
	CCLabelTTF *scoreLabel=CCLabelTTF::create(buf,"STXingkai",30);
	scoreLabel->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(scoreLabel);
	delete buf;

	CCMenuItemImage *pShareItem = CCMenuItemImage::create(
                                        "share.png",
                                        "share_selected.png",
                                        this,
                                        menu_selector(GameFailureScene::menuShareCallback));
	pShareItem->setPosition(ccp(origin.x + visibleSize.width/2-pShareItem->getContentSize().width/2,origin.y+ pShareItem->getContentSize().height+20));

	CCMenuItemImage *pRetryItem = CCMenuItemImage::create(
                                        "retry.png",
                                        "retry_selected.png",
                                        this,
                                        menu_selector(GameFailureScene::menuRetryCallback));
	pRetryItem->setPosition(ccp(origin.x + visibleSize.width/2+pShareItem->getContentSize().width/2,origin.y+ pShareItem->getContentSize().height+20));

	CCSprite *line2=CCSprite::create("line.png");
	line2->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+ pShareItem->getContentSize().height+20+50+line2->getContentSize().height));
	this->addChild(line2);

	CCMenu* pMenu = CCMenu::create(pShareItem,pRetryItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}


void GameFailureScene::menuShareCallback(CCObject* pSender)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo( methodInfo,"com/imeiren/game/NoOneDie", "shareScore", "(I)V") ;

    if (isHave)
    {
		methodInfo.env->CallStaticVoidMethod( methodInfo .classID, methodInfo.methodID,3);
    }
	#endif
}

void GameFailureScene::menuRetryCallback(CCObject* pSender)
{
}

void GameFailureScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,MainMenu::scene(), false));
}
