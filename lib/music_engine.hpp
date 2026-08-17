#pragma once

#include "miniaudio.h"
#include "input_parser.hpp"

#include <iostream>
#include <unordered_map>

struct AudioData{

    ma_decoder decoder;

    std::string name;
    std::string autor;

    bool isFinished = false;
    bool isPaused = false;
};

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

class Harmony{
    private:
        ma_decoder_config _decoder_config;
        ma_device_config _device_config;
        AudioData audio_data;
        std::atomic<bool> isDecoderInitiated;
        ma_device device;
        std::atomic<bool> isDeviceInitiated;
        int current_song;
    public:
        Harmony();
        //~Harmony();
        void play_music(std::unordered_multimap<argument_type, std::string> argument_map);
        void play_directory(std::unordered_multimap<argument_type, std::string> argument_map);
};

void play_music(std::string music_url);