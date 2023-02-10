//
// Created by 41798 on 2023/2/10.
//

#include "base_decoder.h"
#include "../player/Player.h"



using namespace std;

BaseDecoder::BaseDecoder(const char *filePath) {
    m_path = filePath;
    CreateDecodeThread();
}

BaseDecoder::~BaseDecoder() {

}

void BaseDecoder::CreateDecodeThread() {
    //智能指针 协助回收 线程
    //https://blog.csdn.net/weixin_45732589/article/details/115741770
    shared_ptr<BaseDecoder> that(this);
    //创建线程 用于解码
    thread thread(Decode,that);
    thread.detach();
}

void BaseDecoder::Decode(const shared_ptr<BaseDecoder>& that) {
    that->CallbackState(PREPARE);
    that->InitFFMpegDecoder();

}

void BaseDecoder::InitFFMpegDecoder() {

    unsigned int avutil_v = avutil_version();
    unsigned int avcodec_v = avcodec_version();

    //1，初始化上下文
    m_format_ctx = avformat_alloc_context();
    //2，打开文件
    if (avformat_open_input(&m_format_ctx, m_path, NULL, NULL) != 0) {
        LOGE(LogTAG(),"av_format_open_input fail" )
        DoneDecode();
        return;
    }
    //3，获取音视频流信息
    if (avformat_find_stream_info(m_format_ctx, NULL) < 0) {
        LOGE(LogTAG(),"av_format_find_stream_info fail" )
        DoneDecode();
        return;
    }

    //4，查找编解码器
    //4.1 获取视频流的索引
    int vIdx = -1;//存放视频流的索引
    int streams = m_format_ctx->nb_streams;
    LOGD(LogTAG(), "streams size %u", streams);
    for (int i = 0; i < streams; ++i) {
        if (m_format_ctx->streams[i]->codecpar->codec_type == GetMediaType()) {
            vIdx = i;
            break;
        }
    }
    LOGD(LogTAG(), "codec_type %d", vIdx);
    if (vIdx == -1) {
        LOGD(LogTAG(), "Fail to find stream index");
        DoneDecode();
        return;
    }
    m_stream_index = vIdx;

    //4.2 获取解码器参数
    AVStream *pStream = m_format_ctx->streams[vIdx];
    AVCodecParameters *codecPar = pStream->codecpar;

    //4.3 获取解码器
    m_codec = avcodec_find_decoder(codecPar->codec_id);

    //4.4 获取解码器上下文
    m_codec_ctx = avcodec_alloc_context3(m_codec);
    if (avcodec_parameters_to_context(m_codec_ctx, codecPar) != 0) {
        LOGD(LogTAG(), "Fail to obtain av codec context");
        DoneDecode();
        return;
    }
   // 5，打开解码器
    if (avcodec_open2(m_codec_ctx, m_codec, nullptr) < 0) {
        LOGD(LogTAG(), "Fail to open av codec");
        DoneDecode();
        return;
    }

    int  m_duration = (int) (m_format_ctx->duration / AV_TIME_BASE);
    int  m_bit_rate = (int) (m_format_ctx->bit_rate / 1000);

    base_parameter["duration"] = m_duration;
    base_parameter["bitRate"] = m_bit_rate;
    const char *base_para = base_parameter.toStyledString().c_str();
    LOGE(LogTAG(),"base_parameter = %s ",base_para)


}


void BaseDecoder::CallbackState(DecodeState status) {
    switch (status) {
        case PREPARE:
            LOGE("CallbackState","CallbackState PREPARE")
            break;
        case START:
            break;
        case DECODING:
            break;
        case PAUSE:
            break;
        case FINISH:
            break;
        case STOP:
            break;
    }
}

void BaseDecoder::DoneDecode() {

}

