#include "jni_filter.h"

#define MODULE_TAG "JniFilterTest"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, MODULE_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, MODULE_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, MODULE_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, MODULE_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, MODULE_TAG, __VA_ARGS__)

jint hook_RegisterNatives(JNIEnv* env,
                          jclass clazz,
                          const JNINativeMethod* methods,
                          jint numMethods) {
  for (size_t i = 0; i < numMethods; ++i) {
    LOGD("register native function: %s %s %p", methods[i].name, methods[i].signature, methods[i].fnPtr);
    // TODO: Replace methods[i].fnPtr to hook native.
  }
  return _JNI_FILTER_CALL_ORIG(RegisterNatives)(env, clazz, methods, numMethods);
}

jclass hook_FindClass(JNIEnv* env,
                      const char* name) {

  LOGD("findClass: %s\n", name);
  return _JNI_FILTER_CALL_ORIG(FindClass)(env, name);
}

extern "C"
jint JNI_OnLoad(JavaVM* vm,
                void* reserved) {
  JNIEnv* env = nullptr;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4) != JNI_OK) {
    return JNI_ERR ;
  }

  LOGD("JniFilterTest, built %s %s\n", __TIME__, __DATE__);

  JniFilter::GetInstance().initialize(env);

  _JNI_FILTER_HOOK_ENTRY(RegisterNatives, hook_RegisterNatives);
  _JNI_FILTER_HOOK_ENTRY(FindClass, hook_FindClass);

  JniFilter::GetInstance().enable();

  return JNI_VERSION_1_4;
}

