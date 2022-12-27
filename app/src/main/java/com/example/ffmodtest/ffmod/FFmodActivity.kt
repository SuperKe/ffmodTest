package com.example.ffmodtest.ffmod

import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.blankj.utilcode.util.PathUtils
import com.example.ffmodtest.databinding.ActivityFfmodBinding
import org.fmod.FMOD
import java.io.File

class FFmodActivity : AppCompatActivity() {
    private lateinit var binding: ActivityFfmodBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val path = PathUtils.getInternalAppFilesPath() + File.separator + "testffmod.mp3"
        binding = ActivityFfmodBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.btnNormal.setOnClickListener {
            changeVoice(path, 0)
        }

        binding.btnPitchHalf.setOnClickListener {
            changeVoice(path, 1)
        }
        binding.btnPitchDouble.setOnClickListener {
            changeVoice(path, 2)
        }
        binding.btnEcho.setOnClickListener {
            changeVoice(path, 3)
        }
        binding.btnMixer.setOnClickListener {
            changeVoice(path, 4)
        }
    }

    override fun onResume() {
        super.onResume()
        FMOD.init(this)
    }

    override fun onDestroy() {
        super.onDestroy()
        FMOD.close()
    }

    external fun changeVoice(voicePath: String, mode: Int)

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}