#define MINIAUDIO_IMPLEMENTATION
#include "music_engine.hpp"

#include <thread>
#include <vector>

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){
    AudioData* pAudioData = (AudioData*)pDevice->pUserData;
    if(pAudioData == NULL) return;

    ma_uint64 framesRead = 0;
    ma_data_source_read_pcm_frames(&pAudioData->decoder, pOutput, frameCount, &framesRead);

    if(framesRead < frameCount){
        pAudioData->isFinished = true;
    }

    (void)pInput;
}

Harmony::Harmony(){
    _decoder_config = ma_decoder_config_init(ma_format_f32, 2, 44100);
    current_song = 0;

    _device_config = ma_device_config_init(ma_device_type_playback);
    _device_config.playback.format = ma_format_f32;
    _device_config.playback.channels = 2;
    _device_config.sampleRate = 44100;
    _device_config.dataCallback = data_callback;
    _device_config.pUserData = &audio_data;
}

void Harmony::play_music(std::unordered_multimap<argument_type, std::string> argument_map){
    std::string url = argument_map.find(MUSIC)->second;

    if(ma_decoder_init_file(url.c_str(), &_decoder_config, &audio_data.decoder) != MA_SUCCESS){
        throw std::runtime_error("Unable to decode file");
    }

    if(ma_device_init(NULL, &_device_config, &device) != MA_SUCCESS){
        ma_decoder_uninit(&audio_data.decoder);
        throw std::runtime_error("Unable to initiate device");
    }

    if(ma_device_start(&device) != MA_SUCCESS){
        throw std::runtime_error("Unable to start device");
    }

    while(!audio_data.isFinished){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ma_device_uninit(&device);
    ma_decoder_uninit(&audio_data.decoder);
}

void Harmony::play_directory(std::unordered_multimap<argument_type, std::string> argument_map){
    auto range = argument_map.equal_range(MUSIC);
    bool deviceStarted = false;

    for(auto i = range.first; i != range.second; ++i){
        audio_data.isFinished = false;

        if(ma_decoder_init_file(i->second.c_str(), &_decoder_config, &audio_data.decoder) != MA_SUCCESS){
            throw std::runtime_error("Unable to decode file");
        }

        if(deviceStarted == false){
            if(ma_device_init(NULL, &_device_config, &device) != MA_SUCCESS){
                ma_decoder_uninit(&audio_data.decoder);
                throw std::runtime_error("Unable to initiate device");
            }
            deviceStarted = true;
        }

        if(ma_device_start(&device) != MA_SUCCESS){
            throw std::runtime_error("Unable to start device");
        }

        std::cout << "Playing " << i->second <<"\n";

        while(!audio_data.isFinished){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        ma_device_stop(&device);
        ma_decoder_uninit(&audio_data.decoder);
    }
}