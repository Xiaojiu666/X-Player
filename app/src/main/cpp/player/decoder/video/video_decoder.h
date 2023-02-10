//
// Created by 41798 on 2023/2/10.
//

#ifndef X_PLAYER_VIDEO_DECODER_H
#define X_PLAYER_VIDEO_DECODER_H

#include "../base_decoder.h"

extern "C" {
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
};


class VideoDecoder : public BaseDecoder{

public:
    VideoDecoder(const char *filePath);

    ~VideoDecoder();

    virtual AVMediaType GetMediaType();

    virtual const char *const LogTAG();

};


#endif //X_PLAYER_VIDEO_DECODER_H
