package com.example.ffmodtest.ffmod

import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.blankj.utilcode.util.PathUtils
import com.blankj.utilcode.util.ThreadUtils
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
            Thread {
                stop()
                playVoice(path, 0)
            }.start()
        }

        binding.btnPitchHalf.setOnClickListener {
            Thread {
                stop()
                playVoice(path, 1)
            }.start()
        }
        binding.btnPitchDouble.setOnClickListener {
            Thread {
                stop()
                playVoice(path, 2)
            }.start()
        }
        binding.btnEcho.setOnClickListener {
            Thread{
                stop()
                playVoice(path, 3)
            }.start()
        }
        binding.btnMixer.setOnClickListener {
            Thread{
                stop()
                playVoice(path, 4)
            }.start()
        }
        binding.btnSpeed.setOnClickListener {
            Thread{
                stop()
                playVoice(path, 5)
            }.start()
        }
        binding.btnStop.setOnClickListener {
            stop()
        }
    }

    override fun onResume() {
        super.onResume()
        FMOD.init(this)
    }

    override fun onDestroy() {
        super.onDestroy()
        stop()
        FMOD.close()
    }

    external fun playVoice(voicePath: String, mode: Int)

    external fun stop()

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}