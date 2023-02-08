package com.gx.player

object PlayerNativeInterface {

    // Used to load the 'player' library on application startup.
    init {
        System.loadLibrary("player")
    }

    /**
     * A native method that is implemented by the 'player' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun ffmpegVersion(): String



}