#pragma once

#include "miniaudio.h"

#include <iostream>

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

void play_music(std::string music_url);