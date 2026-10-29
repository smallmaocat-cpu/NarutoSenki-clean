LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
            ../../Classes/ActionButton.cpp \
            ../../Classes/ActionManager.cpp \
            hellocpp/AppDelegate.cpp \
            ../../Classes/BGLayer.cpp \
            ../../Classes/Characters.cpp \
            ../../Classes/CreditsLayer.cpp \
            ../../Classes/Effect.cpp \
            ../../Classes/Element.cpp \
            ../../Classes/GameLayer.cpp \
            ../../Classes/GameOver.cpp \
            ../../Classes/GameScene.cpp \
            ../../Classes/GearLayer.cpp \
            ../../Classes/HPBar.cpp \
            ../../Classes/HudLayer.cpp \
            ../../Classes/JoyStick.cpp \
            ../../Classes/LoadLayer.cpp \
            ../../Classes/NetworkLayer.cpp \
            ../../Classes/PauseLayer.cpp \
            ../../Classes/RankingLayer.cpp \
            ../../Classes/SelectLayer.cpp \
            ../../Classes/SkillLayer.cpp \
            ../../Classes/StartMenu.cpp \
            ../../Classes/MyUtils/CCScrewLayer.cpp \
            ../../Classes/MyUtils/CCShake.cpp \
            ../../Classes/MyUtils/CCStrokeLabel.cpp \
            ../../Classes/MyUtils/KTools.cpp \
            ../../Classes/MyUtils/MD5ChecksumDefines.cpp \
            ../../Classes/MyUtils/sqlite3.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/MyUtils

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
