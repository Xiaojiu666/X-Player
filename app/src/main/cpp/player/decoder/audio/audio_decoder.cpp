//
// Created by 41798 on 2023/2/10.
//

#include "audio_decoder.h"

AudioDecoder::AudioDecoder(const char *filePath) : BaseDecoder(filePath) {

}

AudioDecoder::~AudioDecoder() {

}

AVMediaType AudioDecoder::GetMediaType() {
    return AVMEDIA_TYPE_AUDIO;
}

const char *const AudioDecoder::LogTAG() {
    return "AudioDecoder";
}
