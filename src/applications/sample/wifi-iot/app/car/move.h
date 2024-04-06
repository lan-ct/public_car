#include <stdio.h>
#include <unistd.h>

#include "iot_gpio_ex.h"
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "state.h"
#include "motor_control.h"
#define LED_LOOP    10
#define DELYA_MS    1000

void moveInit(void);
void moveForward(int times);
void moveBackward(int times);
void LedExampleEntry(void);
//void turnLeft(float angle);
//void turnRight(float angle);
void leftStopTurn(float angle);
void rightStopTurn(float angle);