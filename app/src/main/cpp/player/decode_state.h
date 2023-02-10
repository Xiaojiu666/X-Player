//
// Created by edz on 2021/4/9.
//

#ifndef VIDEOPLAYER_DECODE_STATE_H
#define VIDEOPLAYER_DECODE_STATE_H

/**
 *  解码状态定义
 */
enum DecodeState {
    STOP,
    PREPARE,
    START,
    DECODING,
    PAUSE,
    FINISH
};
#endif
