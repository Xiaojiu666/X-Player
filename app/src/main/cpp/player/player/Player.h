//
// Created by 41798 on 2023/2/9.
//

#ifndef X_PLAYER_PLAYER_H
#define X_PLAYER_PLAYER_H


#include <jni.h>
#include <android/log.h>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

class Player {
private:

public:

    Player(JNIEnv *jniEnv, jobject obj, jstring path, jobject surface);

    ~Player();

    void play();

    void pause();


    // 经过转换的路径
    const char *m_path;

};


#endif //X_PLAYER_PLAYER_H
