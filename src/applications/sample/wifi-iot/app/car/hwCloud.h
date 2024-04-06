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

#include <stdio.h>
#include <string.h>
#include "iot_config.h"
#include "iot_main.h"
#include "iot_profile.h"
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifi_connecter.h"
#include "iot_gpio_ex.h"
#include "iot_gpio.h"
#include "iot_watchdog.h"
#include "cjson_init.h"
#include "hi_stdlib.h"

void initCloud(FnMsgCallBack MsgRcvCallBack);
int sendMessage(int qos, char *topic, char *payload);