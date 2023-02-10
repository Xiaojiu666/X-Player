//
// Created by 41798 on 2023/2/10.
//

#include "video_decoder.h"

VideoDecoder::VideoDecoder(const char *filePath) : BaseDecoder(filePath) {
}

VideoDecoder::~VideoDecoder() {

}

AVMediaType VideoDecoder::GetMediaType() {
    return AVMEDIA_TYPE_VIDEO;
}

const char *const VideoDecoder::LogTAG() {
    return "VideoDecoder";
}

