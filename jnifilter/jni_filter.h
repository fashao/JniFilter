#ifndef JNI_FILTER_H_
#define JNI_FILTER_H_

class JniFilter final {
private:
  JniFilter():
    jni_env_(nullptr),
    orig_jni_functions_table_(nullptr) {
  }

  JniFilter(JniFilter const&) = delete;
  JniFilter(JniFilter&&) = delete;
  JniFilter& operator=(JniFilter const&) = delete;
  JniFilter& operator=(JniFilter&&) = delete;

public:
  static JniFilter& GetInstance() {
    static JniFilter instance;
    return instance;
  }

  void initialize(JNIEnv* env);

  void enable() const {
    jni_env_->functions = &jni_functions_filter_;
  }

  void disable() const {
    jni_env_->functions = orig_jni_functions_table_;
  }

  bool is_enable() const {
    return jni_env_->functions == &jni_functions_filter_;
  }

  const JNINativeInterface* get_orig_table() const {
    return orig_jni_functions_table_;
  }

  JNINativeInterface& get_filter() {
    return jni_functions_filter_;
  }

private:
  // the env object.
  JNIEnv* jni_env_;
  // the original jni functions table
  const JNINativeInterface* orig_jni_functions_table_;
  // filters
  JNINativeInterface jni_functions_filter_;
};

#define _JNI_FILTER_HOOK_ENTRY(_func, _replace) \
  JniFilter::GetInstance().get_filter()._func = _replace

#define _JNI_FILTER_CALL_ORIG(_func) \
  JniFilter::GetInstance().get_orig_table()->_func

#endif // JNI_FILTER_H_