package com.example.ffmodtest.ffmod

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.ffmodtest.databinding.ActivityFfmodBinding

class FFmodActivity : AppCompatActivity() {
    private lateinit var binding: ActivityFfmodBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityFfmodBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.btnPitchHalf.setOnClickListener {

        }
        binding.btnPitchDouble.setOnClickListener {

        }
        binding.btnEcho.setOnClickListener {

        }
        binding.btnMixer.setOnClickListener {

        }
    }

    external fun changeVoice(voicePath: String, mode: Int): String

    companion object {
        init {
            System.loadLibrary("native-lib")
        }

        @JvmStatic
        fun playComplete(playResult: String) {

        }
    }

}