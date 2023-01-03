#include <jni.h>
#include <string>
#include <unistd.h>
#include "fmod.hpp"
#include <pthread.h>

using namespace FMOD;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ffmodtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

Sound *sound = 0;//player
Channel *channel = 0;//音轨
DSP *dsp = 0;//重采样数字信号
System *sys = 0;//音效引擎系统
const char *path;//c的路径path
jstring voicePath;//java的路径
static JavaVM *jvm;//初始化jvm，用于生成环境env
//java虚拟机
static jobject m_clazz;//当前类(面向java)，做反射回调

static pthread_t pThread;//线程

void *runThread(void *arg) {
    //在这里播放音频
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmodtest_ffmod_FFmodActivity_playVoice(
        JNIEnv *env, jobject thiz,
        jstring voice_path, jint mode) {
    //java字符串转c的字符串
    voicePath = voice_path;
    //创建pThread线程
    pthread_create(&pThread, nullptr, runThread, nullptr);
    path = env->GetStringUTFChars(voicePath, NULL);
    //创建fmod引擎系统
    System_Create(&sys);
    //初始化系统
    sys->init(32, FMOD_INIT_NORMAL, 0);
    //初始化播放器
    sys->createSound(path, FMOD_DEFAULT, 0, &sound);
    sys->playSound(sound, 0, false, &channel);
    //可以创建pthread
    switch (mode) {
        case 0:
            //原声播放
            break;
        case 1:
            //音调降低一半
            sys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);//初始化音调dsp信号处理
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.5f);//降低一半的音调
            channel->addDSP(0, dsp);
            break;
        case 2:
            //音调提高2倍
            sys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);//初始化音调dsp信号处理
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0f);//降低一半的音调
            channel->addDSP(0, dsp);
            break;
        case 3:
            //回音
            sys->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);//创建数字信号处理器
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);//回声播放开始
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 40);//衰减程度
            channel->addDSP(0, dsp);
            break;
        case 4:
            //混音
            //低音轨-音轨1
            sys->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);//初始化音调dsp信号处理
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8f);//降低一半的音调
            channel->addDSP(0, dsp);
            //回声-音轨2
            sys->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);//创建数字信号处理器
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);//回声播放开始
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 40);//衰减程度
            channel->addDSP(1, dsp);
            //颤音-音轨3
            sys->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);//创建数字信号处理器
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 0.8f);//颤音的播放速度
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.4f);//波形倾斜
            channel->addDSP(2, dsp);
            break;
        case 5:
            //倍速
            float speed;
            channel->getFrequency(&speed);
            channel->setFrequency(speed * 1.5f);
            break;
    }

    bool isPlay = true;
    while (isPlay) {
        channel->isPlaying(&isPlay);
        sleep(500 * 1000);
    }
    sound->release();
    sys->close();
    sys->release();
    env->ReleaseStringUTFChars(voicePath, path);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmodtest_ffmod_FFmodActivity_stop(JNIEnv *env, jobject thiz) {
    if (sound != nullptr) {
        sound->release();
    }
    if (sys != nullptr) {
        sys->close();
        sys->release();
    }
    if (voicePath != nullptr && path != nullptr) {
        env->ReleaseStringUTFChars(voicePath, path);
    }
}