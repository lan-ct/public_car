#include <stdio.h>
#include <unistd.h>

#include "iot_gpio_ex.h"
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "state.h"
#include "motor_control.h"
#include "screen.h"
#define DELYA_MS    1000
#define NORMAL_SPEED 10
#define NORMAL_SPEED_TURN 30
#define DELYA_LOOP_MS  100
#define DELYA_LOOP_MS_TURN 10
void moveInit(void);
void moveForward(int times,int speed);
void moveBackward(int times,int speed);

void moveForward_wheel(int cycles,int speed,char restart);

void leftStopTurn(char left);
void rightStopTurn(char left);