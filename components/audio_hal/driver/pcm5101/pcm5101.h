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

#ifndef _PCM5101_H
#define _PCM5101_H

#include "audio_hal.h"
#include "esp_types.h"
#include "esxxx_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    PCM5101_MIC_GAIN_MIN = -1,
    PCM5101_MIC_GAIN_0DB,
    PCM5101_MIC_GAIN_6DB,
    PCM5101_MIC_GAIN_12DB,
    PCM5101_MIC_GAIN_18DB,
    PCM5101_MIC_GAIN_24DB,
    PCM5101_MIC_GAIN_30DB,
    PCM5101_MIC_GAIN_36DB,
    PCM5101_MIC_GAIN_42DB,
    PCM5101_MIC_GAIN_MAX
} pcm5101_mic_gain_t;

/*
 * @brief Initialize PCM5101 codec chip
 *
 * @param codec_cfg  configuration of PCM5101
 *
 * @return
 *      - ESP_OK
 *      - ESP_FAIL
 */
esp_err_t pcm5101_codec_init(audio_hal_codec_config_t *codec_cfg);

/**
 * @brief Deinitialize PCM5101 codec chip
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t pcm5101_codec_deinit(void);

/**
 * @brief Configure PCM5101 DAC mute or not. Basically you can use this function to mute the output or unmute
 *
 * @param enable enable(1) or disable(0)
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t pcm5101_set_voice_mute(bool enable);

/**
 * @brief Set voice volume
 *
 * @param volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t pcm5101_codec_set_voice_volume(int volume);

/**
 * @brief Get voice volume
 *
 * @param[out] *volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t pcm5101_codec_get_voice_volume(int *volume);


esp_err_t pcm5101_codec_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state);
esp_err_t pcm5101_codec_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface);

/*
* enable pa power
*/
esp_err_t pcm5101_pa_power(bool enable);

#ifdef __cplusplus
}
#endif

#endif
