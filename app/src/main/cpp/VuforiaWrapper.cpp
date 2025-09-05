#include <jni.h>
#include <string>
#include <GLES3/gl31.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#include "GLESRenderer.h"

/// JVM pointer obtained in the JNI_OnLoad method below and consumed in the cross-platform code
void* javaVM;

// Struct to hold data that we need to store between calls
struct
{
    JavaVM* vm = nullptr;
    jobject activity = nullptr;
    AAssetManager* assetManager = nullptr;
    jmethodID presentErrorMethodID = nullptr;
    jmethodID initDoneMethodID = nullptr;

    GLESRenderer renderer;

    bool usingARCore{ false };
} gWrapperData;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_initRendering(JNIEnv *env, jclass clazz) {
    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (!gWrapperData.renderer.init(gWrapperData.assetManager))
    {
        __android_log_print(ANDROID_LOG_ERROR, "aaaaa", "Error initialising renderer");
    }
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_setTextures(JNIEnv *env, jclass clazz,
                                                                              jint astronaut_width,
                                                                              jint astronaut_height,
                                                                              jobject astronaut_bytes,
                                                                              jint lander_width,
                                                                              jint lander_height,
                                                                              jobject lander_bytes) {
    // TODO: implement setTextures()
}

JNIEXPORT jboolean JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_configureRendering(JNIEnv *env, jclass clazz,
                                                                                     jint width,
                                                                                     jint height,
                                                                                     jint orientation,
                                                                                     jint rotation) {
    // TODO: implement configureRendering()
    return true;
}

JNIEXPORT jboolean JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_renderFrame(JNIEnv *env, jclass clazz) {
    // TODO: implement renderFrame()
    return true;
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_deinitRendering(JNIEnv *env, jclass clazz) {
    // TODO: implement deinitRendering()
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_initAR(JNIEnv *env, jclass clazz,
                                                                         jobject activity,
                                                                         jobject asset_manager,
                                                                         jint target) {
    // TODO: implement initAR()
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_deinitAR(JNIEnv *env, jclass clazz) {
    // TODO: implement deinitAR()
}

JNIEXPORT jboolean JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_startAR(JNIEnv *env, jclass clazz) {
    // TODO: implement startAR()
    return true;
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_stopAR(JNIEnv *env, jclass clazz) {
    // TODO: implement stopAR()
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_cameraPerformAutoFocus(JNIEnv *env, jclass clazz) {
    // TODO: implement cameraPerformAutoFocus()
}

JNIEXPORT void JNICALL
Java_com_aaa_vuforiaimagetargetsample_VuforiaWrapperKt_cameraRestoreAutoFocus(JNIEnv *env, jclass clazz) {
    // TODO: implement cameraRestoreAutoFocus()
}

#ifdef __cplusplus
}
#endif
