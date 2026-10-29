#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdarg.h>

#define  LOG_TAG    "NarutoDiag"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

static void filelog(const char* fmt, ...) {
    char buf[2048];
    va_list ap; va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    LOGD("%s", buf);
    FILE* f = fopen("/sdcard/Download/naruto_native.txt", "a");
    if (f) { fprintf(f, "%s\n", buf); fflush(f); fclose(f); }
}

extern "C"
{
    jint JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        filelog("=== JNI_OnLoad ===");
        JniHelper::setJavaVM(vm);
        filelog("JniHelper::setJavaVM ok");
        return JNI_VERSION_1_4;
    }

    void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
    {
        filelog("=== nativeInit w=%d h=%d ===", w, h);
        if (!CCDirector::sharedDirector()->getOpenGLView())
        {
            filelog("creating CCEGLView...");
            CCApplication::sharedApplication()->run();
            filelog("run() returned");
        }
        else
        {
            filelog("reinit path");
            ccDrawInit();
            ccGLInvalidateStateCache();
            CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
            CCTextureCache::reloadAllTextures();
            CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
            CCDirector::sharedDirector()->setGLDefaultValues();
        }
    }
}
