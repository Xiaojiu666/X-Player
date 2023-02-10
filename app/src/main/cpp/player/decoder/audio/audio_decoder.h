//
// Created by 41798 on 2023/2/10.
//

#ifndef X_PLAYER_AUDIO_DECODER_H
#define X_PLAYER_AUDIO_DECODER_H
#include "../base_decoder.h"

class AudioDecoder : public BaseDecoder {

private:

public:
    AudioDecoder(const char *filePath);

    ~AudioDecoder();

    AVMediaType GetMediaType() override;

    const char *const LogTAG() override;
};


#endif //X_PLAYER_AUDIO_DECODER_H
