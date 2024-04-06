

#include <stdio.h>
#include <unistd.h>
#include "hi_timer.h"

#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "screen.h"
#include "gyro.h"
#include "hi_time.h"
#include "iot_watchdog.h"
#include "pca9555.h"

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio_ex.h"
#include "iot_gpio.h"
#include "iot_errno.h"
#include "hi_errno.h"
#include "wheel_codec.h"

#define S3_CLICKED 3
#define S4_CLICKED 4
#define S5_CLICKED 5

extern int g_buttonState;

void OnFuncKeyPressed(char *arg);

void PressToRestore(void);

void GetFunKeyState(void);

// 电量检测模块Task
void CW2015Task(void);

void LSM6DSTask(void);
// 功能按键task
void FunKeyTask(void);

void TrafficLightInit(void);

void I2CBusInit(void);

void stateInit(void);

void I2CBusExampleEntry(void);

float getAngle(void);

int getKeyState(void);

int16_t get_wheel_cnt_left_state(void);

int16_t get_wheel_cnt_right_state(void);

void get_wheel_cnt_state(int16_t *left, int16_t *right);