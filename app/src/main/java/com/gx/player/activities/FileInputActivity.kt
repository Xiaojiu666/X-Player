package com.gx.player.activities

import android.Manifest
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.provider.Settings
import android.text.TextUtils
import android.view.View
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import com.gx.player.databinding.ActivityFileInputBinding
import getPath

class FileInputActivity : AppCompatActivity() {

    private lateinit var binding: ActivityFileInputBinding
    private var filePath = ""

    var storagePermission = arrayOf(
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    )


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityFileInputBinding.inflate(layoutInflater)
        setContentView(binding.root)
        initListener()
    }


    private fun initListener() {
        binding.openLocalFile.setOnClickListener {

            result4StoragePermission.launch(storagePermission)
        }
        binding.openPlayer.setOnClickListener {
            val filePath = binding.edFilePath.text.toString();
            if (TextUtils.isEmpty(filePath)) {
                return@setOnClickListener
            }
            val intent = Intent(this, PlayerActivity::class.java)
            intent.putExtra("filePath", filePath)
            startActivity(intent)
        }
    }

    //请求文件管理器
    private val registerForActivityResult =
        registerForActivityResult(ActivityResultContracts.OpenDocument()) {
            if (it == null) {
                return@registerForActivityResult
            }
            filePath = getPath(this, it)!!
            binding.edFilePath.setText(filePath)
        }

    //请求运行时权限
    private val result4StoragePermission = registerForActivityResult(
        ActivityResultContracts.RequestMultiplePermissions()
    ) {
        if (it[Manifest.permission.READ_EXTERNAL_STORAGE]!! && it[Manifest.permission.WRITE_EXTERNAL_STORAGE]!!) {
            registerForActivityResult.launch(arrayOf("*/*"))
        } else {
            val intent = Intent()
            intent.action = Settings.ACTION_APPLICATION_DETAILS_SETTINGS
            intent.data = Uri.parse("package:$packageName")
            startActivity(intent)
        }
    }

}