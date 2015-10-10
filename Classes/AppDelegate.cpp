#include "AppDelegate.h"
#include "Scene/StartScene.h"
#include "Data/BlockData.h"
#include "Data/PropData.h"

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("TreasureHunter", Rect(0, 0, 640, 960)); //´´½¨WINDOWS´°¿Ú
        director->setOpenGLView(glview);
	}

    director->getOpenGLView()->setDesignResolutionSize(WIDTH, HEIGHT, ResolutionPolicy::SHOW_ALL); //ÆÁÄ»ÊÊÅä
    director->setDisplayStats(false); //²»ÏÔÊ¾FPS
	director->setAnimationInterval(1.0 / 60); //ÉèÖÃFPS

	//Ô¤¼ÓÔØÒôÀÖÒôÐ§
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(BGM);
	audio->preloadEffect(KEY_EFFECT);
	audio->preloadEffect(GOLD_EFFECT);
	audio->preloadEffect(DIG_EFFECT);
	audio->preloadEffect(EXPLODE_EFFECT);
	audio->preloadEffect(WIN_EFFECT);
	audio->preloadEffect(LOSE_EFFECT);
	audio->preloadEffect(SCAN_EFFECT);
	audio->preloadEffect(DETECT_EFFECT);

	//¼ÓÔØcocos studioµ¼³öµÄÎÄ¼þ
    FileUtils::getInstance()->addSearchPath("res");

	//½øÈëStart³¡¾°
    auto scene = StartScene::create();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	//Èô±³¾°ÒôÀÖ¿ªÆô£¬ÔÝÍ£±³¾°ÒôÀÖ
	if (UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

	//Èô±³¾°ÒôÀÖ¿ªÆô£¬»Ö¸´±³¾°ÒôÀÖ
	if (UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
