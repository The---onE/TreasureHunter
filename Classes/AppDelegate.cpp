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
        glview = GLViewImpl::createWithRect("TreasureHunter", Rect(0, 0, 640, 960)); //����WINDOWS����
        director->setOpenGLView(glview);
	}

    director->getOpenGLView()->setDesignResolutionSize(WIDTH, HEIGHT, ResolutionPolicy::SHOW_ALL); //��Ļ����
    director->setDisplayStats(false); //����ʾFPS
	director->setAnimationInterval(1.0 / 60); //����FPS

	//Ԥ����������Ч
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

	//����cocos studio�������ļ�
    FileUtils::getInstance()->addSearchPath("res");

	//����Start����
    auto scene = StartScene::create();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	//���������ֿ�������ͣ��������
	if (UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

	//���������ֿ������ָ���������
	if (UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
