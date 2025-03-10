/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2019 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <string.h>
#include "board.h"
#include "esp_log.h"
#include "pcm5101.h"
#include "audio_volume.h"

static codec_dac_volume_config_t *dac_vol_handle;

#define PCM5101_DAC_VOL_CFG_DEFAULT() {                      \
    .max_dac_volume = 32,                                   \
    .min_dac_volume = -95.5,                                \
    .board_pa_gain = BOARD_PA_GAIN,                         \
    .volume_accuracy = 0.5,                                 \
    .dac_vol_symbol = 1,                                    \
    .zero_volume_reg = 0xBF,                                \
    .reg_value = 0,                                         \
    .user_volume = 0,                                       \
    .offset_conv_volume = NULL,                             \
}

/*
 * operate function of codec
 */
audio_hal_func_t AUDIO_CODEC_PCM5101_DEFAULT_HANDLE = {
    .audio_codec_initialize = pcm5101_codec_init,
    .audio_codec_deinitialize = pcm5101_codec_deinit,
    .audio_codec_ctrl = pcm5101_codec_ctrl_state,
    .audio_codec_config_iface = pcm5101_codec_config_i2s,
    .audio_codec_set_mute = pcm5101_set_voice_mute,
    .audio_codec_set_volume = pcm5101_codec_set_voice_volume,
    .audio_codec_get_volume = pcm5101_codec_get_voice_volume,
    .audio_codec_enable_pa = pcm5101_pa_power,
    .audio_hal_lock = NULL,
    .handle = NULL,
};

static char *TAG = "PCM5101";



esp_err_t pcm5101_codec_init(audio_hal_codec_config_t *codec_cfg)
{
    codec_dac_volume_config_t vol_cfg = PCM5101_DAC_VOL_CFG_DEFAULT();
    dac_vol_handle = audio_codec_volume_init(&vol_cfg);
    return ESP_OK;
}

esp_err_t pcm5101_codec_deinit()
{
    audio_codec_volume_deinit(dac_vol_handle);
    return ESP_OK;
}

/*
* set pcm5101 dac mute or not
* if mute = 0, dac un-mute
* if mute = 1, dac mute
*/
static void pcm5101_mute(int mute)
{
    pcm5101_codec_set_voice_volume(0);
}
/**
 * @brief Set voice volume
 *
 * @note Register values. 0x00: -95.5 dB, 0x5B: -50 dB, 0xBF: 0 dB, 0xFF: 32 dB
 * @note Accuracy of gain is 0.5 dB
 *
 * @param volume: voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t pcm5101_codec_set_voice_volume(int volume)
{
    esp_err_t res = ESP_OK;
    uint8_t reg = 0;
    reg = audio_codec_get_dac_reg_value(dac_vol_handle, volume);

    dac_vol_handle->user_volume = volume;
    ESP_LOGD(TAG, "Set volume:%.2d reg_value:0x%.2x dB:%.1f", dac_vol_handle->user_volume, reg,
            audio_codec_cal_dac_volume(dac_vol_handle));
    return res;
}

esp_err_t pcm5101_codec_get_voice_volume(int *volume)
{
    esp_err_t res = ESP_OK;
    *volume = dac_vol_handle->user_volume;
    ESP_LOGD(TAG, "Get volume:%.2d ", *volume);
    return res;
}

esp_err_t pcm5101_set_voice_mute(bool enable)
{
    ESP_LOGD(TAG, "PCM5101 SetVoiceMute volume:%d", enable);
    pcm5101_mute(enable);
    return ESP_OK;
}

esp_err_t pcm5101_codec_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state)
{
    esp_err_t ret = ESP_OK;
    return ret;
}

esp_err_t pcm5101_codec_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface)
{
    int ret = ESP_OK;
    return ret;
}
/*
* enable pa power
*/
esp_err_t pcm5101_pa_power(bool enable)
{
    esp_err_t ret = ESP_OK;
    return ret;
}