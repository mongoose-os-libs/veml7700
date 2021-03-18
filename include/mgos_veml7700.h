/*
 * Copyright (c) 2021 Deomid "rojer" Ryabkov
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <mgos_i2c.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MGOS_VEML7700_CFG_SD (1 << 0)

#define MGOS_VEML7700_CFG_ALS_PERS_1 (0 << 4)
#define MGOS_VEML7700_CFG_ALS_PERS_2 (1 << 4)
#define MGOS_VEML7700_CFG_ALS_PERS_4 (2 << 4)
#define MGOS_VEML7700_CFG_ALS_PERS_8 (3 << 4)

#define MGOS_VEML7700_CFG_ALS_IT_25 (0xc << 6)
#define MGOS_VEML7700_CFG_ALS_IT_50 (8 << 6)
#define MGOS_VEML7700_CFG_ALS_IT_100 (0 << 6)
#define MGOS_VEML7700_CFG_ALS_IT_200 (1 << 6)
#define MGOS_VEML7700_CFG_ALS_IT_400 (2 << 6)
#define MGOS_VEML7700_CFG_ALS_IT_800 (3 << 6)

#define MGOS_VEML7700_CFG_ALS_GAIN_1_8 (2 << 11)
#define MGOS_VEML7700_CFG_ALS_GAIN_1_4 (3 << 11)
#define MGOS_VEML7700_CFG_ALS_GAIN_1 (0 << 11)
#define MGOS_VEML7700_CFG_ALS_GAIN_2 (1 << 11)

#define MGOS_VEML7700_PSM_0 (0)
#define MGOS_VEML7700_PSM_500 (1 | (0 << 1))
#define MGOS_VEML7700_PSM_1000 (1 | (1 << 1))
#define MGOS_VEML7700_PSM_2000 (1 | (2 << 1))
#define MGOS_VEML7700_PSM_4000 (1 | (3 << 1))
#define MGOS_VEML7700_PSM_NO_CHANGE (0xffff)

bool mgos_veml7700_detect(struct mgos_i2c *bus);

struct mgos_veml7700;

struct mgos_veml7700 *mgos_veml7700_create(struct mgos_i2c *bus);

bool mgos_veml7700_set_cfg(struct mgos_veml7700 *ctx, uint16_t cfg,
                           uint16_t psm);

int mgos_veml7700_get_meas_interval_ms(struct mgos_veml7700 *ctx);

float mgos_veml7700_read_lux(struct mgos_veml7700 *ctx, bool adjust);

#ifndef MGOS_VEML7700_ADJUST_UP_THRESH
#define MGOS_VEML7700_ADJUST_UP_THRESH 2000
#endif
#ifndef MGOS_VEML7700_ADJUST_DOWN_THRESH
#define MGOS_VEML7700_ADJUST_DOWN_THRESH 30000
#endif

bool mgos_veml7700_adjust(struct mgos_veml7700 *ctx);

void mgos_veml7700_free(struct mgos_veml7700 *ctx);

#ifdef __cplusplus
}
#endif
