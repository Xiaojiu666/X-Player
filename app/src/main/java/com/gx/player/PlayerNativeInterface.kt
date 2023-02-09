package com.gx.player

import android.view.Surface

object PlayerNativeInterface {

    // Used to load the 'Player' library on application startup.
    init {
        System.loadLibrary("player")
    }

    /**
     * A native method that is implemented by the 'Player' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun ffmpegVersion(): String

    external fun createPlayer(surface: Surface,path: String) : Int

    external fun playStart(player: Int)

    external fun playPause(player: Int)
}