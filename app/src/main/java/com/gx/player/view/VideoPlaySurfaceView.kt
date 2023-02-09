package com.gx.player.view

import android.content.Context
import android.text.TextUtils
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView


class VideoPlaySurfaceView : SurfaceView, SurfaceHolder.Callback {

    private var filePath = ""

    constructor(context: Context) : this(context, null, 0)
    constructor(context: Context, attrs: AttributeSet?) : this(context, attrs, 0)
    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) :
            super(context, attrs, defStyleAttr) {
    }


    override fun surfaceCreated(holder: SurfaceHolder) {
        val surface = holder.surface
        if (surface == null || !surface.isValid) {
//            Log.d(TAG,"surface is exception")
            return
        }
        if (TextUtils.isEmpty(filePath)) {
//            Log.d(TAG,"filePath is exception")
            return
        }
//        val ffmpegPlayer = FFmpegPlayer(surface,filePath)
//        VideoControlManager.initPlayer(ffmpegPlayer)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {

    }

    fun setFile(filePath: String) {
        this.filePath = filePath
        holder.addCallback(this)
    }

    fun start() {
    }

    fun stop() {
    }
}