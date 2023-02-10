# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

set(ffmpeg_lib_dir ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI})

set(ffmpeg_head_dir ${CMAKE_SOURCE_DIR}/ffmpeg)

# 2. 添加头文件目录
include_directories(${ffmpeg_head_dir}/include)

project("player")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 3. 添加ffmpeg相关的so库
add_library(avutil
        SHARED
        IMPORTED)
set_target_properties(avutil
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavutil.so)

add_library(swresample
        SHARED
        IMPORTED)
set_target_properties(swresample
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libswresample.so)

add_library(avcodec
        SHARED
        IMPORTED)
set_target_properties(avcodec
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavcodec.so)

add_library(avfilter
        SHARED
        IMPORTED)
set_target_properties(avfilter
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavfilter.so)

add_library(swscale
        SHARED
        IMPORTED)
set_target_properties(swscale
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libswscale.so)

add_library(avformat
        SHARED
        IMPORTED)
set_target_properties(avformat
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavformat.so)

add_library(avdevice
        SHARED
        IMPORTED)
set_target_properties(avdevice
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libavdevice.so)

add_library(h264
        SHARED
        IMPORTED)
set_target_properties(h264
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_dir}/libh264.so)

# 从系统库中查找依赖库
find_library( # Sets the name of the path variable.
        # 设置依赖库的名字，下面链接库的时候会用到
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.

        # 查找log依赖库
        # {sdk-path}/ndk-bundle/sysroot/usr/include/android/log.h
        log )

add_library( # Sets the name of the library.
        player

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp


        ${CMAKE_SOURCE_DIR}/utils/logger.h
        ${CMAKE_SOURCE_DIR}/utils/timer.c
        ${CMAKE_SOURCE_DIR}/utils/callback/callback.h
        ${CMAKE_SOURCE_DIR}/utils/callback/callback.cpp

        # 播放器
        ${CMAKE_SOURCE_DIR}/player/player/Player.cpp
        ${CMAKE_SOURCE_DIR}/player/player/Player.h
        ${CMAKE_SOURCE_DIR}/player/decoder/base_decoder.cpp
        ${CMAKE_SOURCE_DIR}/player/decoder/video/video_decoder.cpp
        ${CMAKE_SOURCE_DIR}/player/decoder/video/video_decoder.h
        ${CMAKE_SOURCE_DIR}/player/decoder/audio/audio_decoder.cpp
        ${CMAKE_SOURCE_DIR}/player/decoder/audio/audio_decoder.h

        #jsoncpp 引用 https://blog.csdn.net/lftaoyuan/article/details/107057766
        jsoncpp/json_tool.h
        jsoncpp/json_reader.cpp
        jsoncpp/json_valueiterator.inl
        jsoncpp/json_value.cpp
        jsoncpp/json_writer.cpp
        jsoncpp/assertions.h
        jsoncpp/allocator.h
        jsoncpp/config.h
        jsoncpp/json_features.h
        jsoncpp/forwards.h
        jsoncpp/json.h
        jsoncpp/reader.h
        jsoncpp/value.h
        jsoncpp/version.h
        jsoncpp/writer.h
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.



# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        player

        # 4. 连接 FFmpeg 相关的库
        avutil
        swresample
        avcodec
        avfilter
        swscale
        avformat
        avdevice
        h264
        -landroid
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})