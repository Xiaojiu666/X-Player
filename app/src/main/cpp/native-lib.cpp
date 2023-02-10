#include <jni.h>
#include <string>
#include "player/player/Player.h"
#include "utils/logger.h"

using namespace std;
extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_gx_player_PlayerNativeInterface_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_gx_player_PlayerNativeInterface_ffmpegVersion(
        JNIEnv* env,
        jobject /* this */) {
    char versionInfo[4096];
    unsigned int avutil_v = avutil_version();
    unsigned int avcodec_v = avcodec_version();
    int a = avutil_v / (int) pow(2, 16);
    int b = (int) (avutil_v - a * pow(2, 16)) / (int) pow(2, 8);
    int c = avutil_v % (int) pow(2, 8);

    int d = avcodec_v / (int) pow(2, 16);
    int e = (int) (avcodec_v - a * pow(2, 16)) / (int) pow(2, 8);
    int f = avcodec_v % (int) pow(2, 8);

    LOGE("ATM","avUtils Version %d.%d.%d ",a,b,c)
    sprintf(versionInfo,"avUtils Version %d.%d.%d ",a,b,c);
    sprintf(versionInfo,"avCodec Version %d.%d.%d %s",d,e,f,versionInfo);

    return env->NewStringUTF(versionInfo);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_gx_player_PlayerNativeInterface_createPlayer(JNIEnv *env, jobject thiz, jobject surface,
                                                      jstring path) {
    Player *player = new Player(env, thiz, path, surface);
    return (jint) player;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_gx_player_PlayerNativeInterface_playStart(JNIEnv *env, jobject thiz, jint player) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_gx_player_PlayerNativeInterface_playPause(JNIEnv *env, jobject thiz, jint player) {

}
