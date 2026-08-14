#define MINIAUDIO_IMPLEMENTATION
#include "music_engine.hpp"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if(pDecoder == NULL){
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, 0);

    (void)pInput;
}

void play_music(std::string music_url){
    ma_decoder decoder;
    ma_result result = ma_decoder_init_file(music_url.c_str(), NULL, &decoder);
    if(result != MA_SUCCESS){
        std::cout << "ERROR: Unable to initiate file\n";
        return;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = decoder.outputFormat;
    config.playback.channels = decoder.outputChannels;
    config.sampleRate = decoder.outputSampleRate;
    config.dataCallback = data_callback;
    config.pUserData = &decoder;

    ma_device device;
    if(ma_device_init(NULL, &config, &device) != MA_SUCCESS){
        std::cout << "ERROR: Failed to open playback device\n";
        ma_decoder_uninit(&decoder);
        return;
    }

    if(ma_device_start(&device) != MA_SUCCESS){
        std::cout << "ERROR: Failed to start playback device\n";
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return;
    }

    std::cout << "Press [ENTER] to exit...\n";
    getchar();

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}