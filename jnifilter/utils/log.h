#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

#include <android/log.h>

#ifdef DEBUG
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, MODULE_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, MODULE_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, MODULE_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, MODULE_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, MODULE_TAG, __VA_ARGS__)
#else
#define LOGV(...) while(false) {}
#define LOGD(...) while(false) {}
#define LOGI(...) while(false) {}
#define LOGW(...) while(false) {}
#define LOGE(...) while(false) {}
#endif // DEBUG

#endif // UTILS_LOG_H_