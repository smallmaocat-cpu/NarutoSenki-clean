#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameScene.h"
#include <android/log.h>
#include <stdio.h>
#include <stdarg.h>

USING_NS_CC;

static void flog(const char* fmt, ...) {
    char buf[2048];
    va_list ap; va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    __android_log_print(ANDROID_LOG_DEBUG,"NarutoDiag","%s",buf);
    FILE* f = fopen("/sdcard/Download/naruto_native.txt", "a");
    if (f) { fprintf(f, "%s\n", buf); fflush(f); fclose(f); }
}

AppDelegate::AppDelegate() {
    flog("=== AppDelegate ctor ===");
}

AppDelegate::~AppDelegate() {
    flog("=== AppDelegate dtor ===");
}

bool AppDelegate::applicationDidFinishLaunching() {
    flog("=== applicationDidFinishLaunching ===");
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0f / 60);
    flog("director configured, creating GameScene");
    CCScene* pScene = GameScene::create();
    flog("GameScene created, running");
    pDirector->runWithScene(pScene);
    flog("runWithScene done");
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
