//
// Created by 41798 on 2023/2/9.
//

#include <android/log.h>
#include "Player.h"
#include "../../utils/logger.h"


void Player::pause() {

}

Player::Player(JNIEnv *jniEnv, jobject obj, jstring path, jobject surface) {
    const char *m_path = jniEnv->GetStringUTFChars(path, NULL);
    LOGD("Player","Player path %s",m_path)
}

Player::~Player() {

}

void Player::play() {

}
