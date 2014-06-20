#include "NoOneDieJni.h"
#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

void NoOneDie::openUmengShareJni(){
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo( methodInfo,"com/imeiren/game/cocos2dSimpleGame", "openShareBoard", "()V") ;

    if (isHave)
    {
		methodInfo.env->CallStaticVoidMethod( methodInfo .classID, methodInfo.methodID );
    }
}