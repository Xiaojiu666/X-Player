//
// Created by 41798 on 2023/2/10.
//

#ifndef X_PLAYER_BASE_DECODER_H
#define X_PLAYER_BASE_DECODER_H

#include <jni.h>
#include <thread>
#include "../../utils/logger.h"
#include "../decode_state.h"
#include "../../utils/callback/callback.h"
#include "../../jsoncpp/value.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
#include <ctime>
};


class BaseDecoder {
private:
    const char * m_path = NULL;


    //-------------定义解码相关------------------------------
    // 解码信息上下文
    AVFormatContext *m_format_ctx = NULL;

    // 解码器
    AVCodec *m_codec = NULL;

    // 解码器上下文
    AVCodecContext *m_codec_ctx = NULL;

    // 待解码包 解封装后保存压缩数据包
    AVPacket *m_packet = NULL;

    // 最终解码数据 解码后保存音视频帧
    AVFrame *m_frame = NULL;

    // 数据流索引(音？视频)
    int m_stream_index = -1;



    //-----------------私有方法------------------------------------
    /**
     * 初始化
     * @param env jvm环境
     * @param path 本地文件路径
     */
    void Init(JNIEnv *env, jstring path);

    /**
     * 初始化FFMpeg相关的参数
     * @param env jvm环境
     */
    void InitFFMpegDecoder();

    /**
     * 分配解码过程中需要的缓存
     */
    void AllocFrameBuffer();

    /**
     * 新建解码线程
     */
    void CreateDecodeThread();

    /**
     * 循环解码
     */
    void LoopDecode(JNIEnv *env);

    /**
     * 获取当前帧时间戳
     */
    void ObtainTimeStamp();

    /**
     * 解码完成
     * @param env jvm环境
     */
    void DoneDecode();

    /**
     * 静态解码方法，用于解码线程回调
     * @param that 当前解码器
     */
    static void Decode(const std::shared_ptr<BaseDecoder>& that);

    /**
     * 时间同步
     */
    void SyncRender();

    //解码状态
    void CallbackState(DecodeState status);

public:
   BaseDecoder(const char *filePath);

    ~BaseDecoder();


    Callback *m_callback = NULL;

    Json::Value base_parameter;

    /**
     * 音视频索引类型
     */
    virtual AVMediaType GetMediaType() = 0;

    /**
     * Log前缀
     */
    virtual const char *const LogTAG() = 0;

};


#endif //X_PLAYER_BASE_DECODER_H
