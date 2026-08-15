#define MINIAUDIO_IMPLEMENTATION
#include "music_engine.hpp"

#include <thread>

struct AudioData{
    ma_decoder decoder;
    bool isFinished = false;
};

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

void play_music(std::string music_url){
    AudioData audio_data;

    ma_result result = ma_decoder_init_file(music_url.c_str(), NULL, &audio_data.decoder);
    if(result != MA_SUCCESS){
        std::cout << "ERROR: Unable to initiate file\n";
        return;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = audio_data.decoder.outputFormat;
    config.playback.channels = audio_data.decoder.outputChannels;
    config.sampleRate = audio_data.decoder.outputSampleRate;
    config.dataCallback = data_callback;
    config.pUserData = &audio_data;

    ma_device device;
    if(ma_device_init(NULL, &config, &device) != MA_SUCCESS){
        std::cout << "ERROR: Failed to open playback device\n";
        ma_decoder_uninit(&audio_data.decoder);
        return;
    }

    if(ma_device_start(&device) != MA_SUCCESS){
        std::cout << "ERROR: Failed to start playback device\n";
        ma_device_uninit(&device);
        ma_decoder_uninit(&audio_data.decoder);
        return;
    }

    while(!audio_data.isFinished){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ma_device_uninit(&device);
    ma_decoder_uninit(&audio_data.decoder);
}