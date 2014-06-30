#include "GameFailureScene.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "MainMenu.h"
#include "XmlParser.h"

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
	XMLParser *pXmlParser=XMLParser::parseWithFile("strings.xml");
	//获取当前级别，分别为：train,warmUp,career,worldCup
	const char *pLevel="train";
	CCLabelTTF *level=CCLabelTTF::create(pXmlParser->getString(pLevel)->getCString(),"STXingkai",50);
	level->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-level->getContentSize().height/2-40));
	this->addChild(level);

	CCSprite *line=CCSprite::create("line.png");
	line->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height-level->getContentSize().height-40-50));
	this->addChild(line);

	CCString *pValue=pXmlParser->getString("score");
	//本次得分
	int score=50;
	//最高分
	int best=40;
	if(score>best)
	{
		CCLabelTTF *label=CCLabelTTF::create(pXmlParser->getString("newHighScore")->getCString(),"STXingkai",50);
		label->setColor(ccc3(255,255,0));
		label->setPosition(ccp(origin.x+visibleSize.width/2,line->getPositionY()-60));
		this->addChild(label);
	}
	CCString *val=CCString::createWithFormat("%s : %d",pValue->getCString(),score);
	CCLabelTTF *scoreLabel=CCLabelTTF::create(val->getCString(),"STXingkai",45);
	scoreLabel->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+scoreLabel->getContentSize().height));
	this->addChild(scoreLabel);

	CCLabelTTF *bestLabel=CCLabelTTF::create(CCString::createWithFormat("%s : %d",pXmlParser->getString("best")->getCString(),best)->getCString(),"STXingkai",40);
	bestLabel->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-bestLabel->getContentSize().height));
	this->addChild(bestLabel);

	/*CCMenuItemImage *pShareItem = CCMenuItemImage::create(
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
	pRetryItem->setPosition(ccp(origin.x + visibleSize.width/2+pShareItem->getContentSize().width/2,origin.y+ pShareItem->getContentSize().height+20));*/
	CCLabelTTF *pShareLabel = CCLabelTTF::create(pXmlParser->getString("share")->getCString(),"STXingkai",40);
	CCMenuItemLabel *pShareItem =CCMenuItemLabel::create(pShareLabel,this,menu_selector(GameFailureScene::menuShareCallback));
	pShareItem->setPosition(ccp(origin.x + pShareItem->getContentSize().width/2+80,origin.y+ pShareItem->getContentSize().height+20));

	CCLabelTTF *pReturnLabel = CCLabelTTF::create(pXmlParser->getString("return")->getCString(),"STXingkai",40);
	CCMenuItemLabel *pReturnItem =CCMenuItemLabel::create(pReturnLabel,this,menu_selector(GameFailureScene::menuReturnCallback));
	pReturnItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+ pReturnItem->getContentSize().height+20));

	CCLabelTTF *pRetryLabel = CCLabelTTF::create(pXmlParser->getString("retry")->getCString(),"STXingkai",40);
	CCMenuItemLabel *pRetryItem =CCMenuItemLabel::create(pRetryLabel,this,menu_selector(GameFailureScene::menuRetryCallback));
	pRetryItem->setPosition(ccp(origin.x + visibleSize.width-pRetryLabel->getContentSize().width/2-80,origin.y+ pRetryLabel->getContentSize().height+20));

	CCSprite *line2=CCSprite::create("line.png");
	line2->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+ pShareItem->getContentSize().height+20+50+line2->getContentSize().height));
	this->addChild(line2);

	CCMenu* pMenu = CCMenu::create(pShareItem,pReturnItem,pRetryItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}


void GameFailureScene::menuShareCallback(CCObject* pSender)
{
	//截图
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* inTexture = CCRenderTexture::create((int)size.width, (int)size.height,kCCTexture2DPixelFormat_RGBA8888);
	CCScene *scene=CCDirector::sharedDirector()->getRunningScene();
    //inTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
    //inTexture->setPosition( ccp(size.width/2, size.height/2) );
    //inTexture->setAnchorPoint( ccp(0.5f,0.5f) );

    inTexture->begin();
    scene->visit();
    inTexture->end();
	//Android下默认保存的路径是Uri uri = Uri.parse("file:////data/data/"+ mActivity.getApplicationInfo().packageName + "/files/share.jpg");
	CCLog("%d",inTexture->saveToFile("share.jpg",kCCImageFormatJPEG));
	/*std::string fileName="share.jpg";
    //CCAssert(format == kCCImageFormatJPEG || format == kCCImageFormatPNG,"the image can only be saved as JPG or PNG format");

	CCImage *pImage =inTexture->newCCImage(true);
    if (pImage)
    {
        std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + fileName;//得到保存资源的位置
        pImage->saveToFile(fullpath.c_str(), true);
    }

    CC_SAFE_DELETE(pImage);*/

	//
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo( methodInfo,"com/imeiren/game/NoOneDie", "shareScore", "(I)V") ;

    if (isHave)
    {
		//本次得分
		int score=6;
		methodInfo.env->CallStaticVoidMethod( methodInfo .classID, methodInfo.methodID,score);
    }
	#endif
}

void GameFailureScene::menuRetryCallback(CCObject* pSender)
{
	//重新开始游戏
}

void GameFailureScene::menuReturnCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,MainMenu::scene(), false));
}

void GameFailureScene::keyBackClicked()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,MainMenu::scene(), false));
}
