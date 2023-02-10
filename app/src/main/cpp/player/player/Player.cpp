//
// Created by 41798 on 2023/2/9.
//

#include <android/log.h>
#include "Player.h"
#include "../../utils/logger.h"
#include "../decoder/base_decoder.h"
#include "../decoder/video/video_decoder.h"
#include "../decoder/audio/audio_decoder.h"

Player::Player(JNIEnv *jniEnv, jobject obj, jstring path, jobject surface) {
    m_path = jniEnv->GetStringUTFChars(path, nullptr);
    LOGE("BaseDecoder","Player path %s",m_path)
    auto *videoDecoder = new VideoDecoder(m_path);
    auto *audioDecoder = new AudioDecoder(m_path);

}


void Player::play() {

}
void Player::pause() {

}

Player::~Player() {
    LOGE("Player","~Player()")
}
