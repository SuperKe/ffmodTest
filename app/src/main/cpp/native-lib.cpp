#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ffmodtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmodtest_ffmod_FFmodActivity_changeVoice(
        JNIEnv *env, jobject thiz,
        jstring voice_path, jint mode) {
    //java字符串转c的字符串
    const char *path = env->GetStringUTFChars(voice_path, 0);

}