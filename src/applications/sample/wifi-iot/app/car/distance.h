/*
 * Copyright (c) 2022 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

/*
    HCSR05 超声波模块的相关API接口
*/
#include <stdio.h>
#include <stdlib.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_watchdog.h"
#include "iot_gpio.h"
#include "hi_time.h"
#include "hi_io.h"
#include "iot_gpio_ex.h"

#define DELAY_US20    20
#define DELAY_MS10    10

void Hcsr04Init(void);

float GetDistance(void);

void Hcsr04SampleTask(void);

void distanceInit(void);