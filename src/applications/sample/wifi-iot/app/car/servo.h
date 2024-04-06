

#include <stdio.h>
#include <stdlib.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "hi_io.h"
#include "iot_gpio_ex.h"
#include "iot_watchdog.h"
#include "hi_time.h"

#define  COUNT   10
#define  FREQ_TIME    20000

void SetAngle(unsigned int duty);

void RegressMiddle(void);

void EngineTurnRight(void);

void EngineTurnLeft(void);

void S92RInit(void);

void Sg92RTask(void);

void Sg92rSampleEntry(void);