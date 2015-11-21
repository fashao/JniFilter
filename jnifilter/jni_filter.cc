#include "jni_filter.h"
#include "utils/log.h"

#define MODULE_TAG "JniFilter"

void JniFilter::initialize(JNIEnv* env) {
  LOGD("JniFilter, built %s %s\n", __TIME__, __DATE__);

  jni_env_ = env;
  LOGD("env: %p\n", env);

  orig_jni_functions_table_ = jni_env_->functions;
  memcpy(&jni_functions_filter_, orig_jni_functions_table_, sizeof(jni_functions_filter_));
}