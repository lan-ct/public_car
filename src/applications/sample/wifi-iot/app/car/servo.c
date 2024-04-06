
#include "servo.h"

void SetAngle(unsigned int duty)
{
    unsigned int time = FREQ_TIME;

    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_2, IOT_GPIO_VALUE1);
    hi_udelay(duty);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_2, IOT_GPIO_VALUE0);
    hi_udelay(time - duty);
}

/* The steering gear is centered
 * 1、依据角度与脉冲的关系，设置高电平时间为1500微秒
 * 2、不断地发送信号，控制舵机居中
*/
void RegressMiddle(void)
{
    //unsigned int angle = 1500;
     unsigned int angle =1425;
    for (int i = 0; i < COUNT; i++) {
        SetAngle(angle);
    }
}

/* Turn 90 degrees to the right of the steering gear
 * 1、依据角度与脉冲的关系，设置高电平时间为500微秒
 * 2、不断地发送信号，控制舵机向右旋转90度
*/
/*  Steering gear turn right */
void EngineTurnRight(void)
{
    unsigned int angle = 450;
    for (int i = 0; i < COUNT; i++) {
        SetAngle(angle);
    }
}

/* Turn 90 degrees to the left of the steering gear
 * 1、依据角度与脉冲的关系，设置高电平时间为2500微秒
 * 2、不断地发送信号，控制舵机向左旋转90度
*/
/* Steering gear turn left */
void EngineTurnLeft(void)
{
    unsigned int angle = 2400;
    for (int i = 0; i < COUNT; i++) {
        SetAngle(angle);
    }
}

void S92RInit(void)
{
    IoTWatchDogDisable();
    IoTGpioInit(IOT_IO_NAME_GPIO_2);
    IoSetFunc(IOT_IO_NAME_GPIO_2, IOT_IO_FUNC_GPIO_2_GPIO);
    IoTGpioSetDir(IOT_IO_NAME_GPIO_2, IOT_GPIO_DIR_OUT);
    
}

void Sg92RTask(void)
{
        unsigned int time = 200;
        RegressMiddle();
        TaskMsleep(time);

        /*
         * 舵机左转90度
         * Steering gear turns 90 degrees to the left
         */
        EngineTurnLeft();
        TaskMsleep(time);

        /* 舵机归中 Steering gear centering */
        RegressMiddle();
        TaskMsleep(time);

        /*
         * 舵机右转90度
         * Steering gear turns right 90 degrees
         */
        EngineTurnRight();
        TaskMsleep(time);

        /* 舵机归中 Steering gear centering */
        RegressMiddle();
        TaskMsleep(time);
}

void Sg92rSampleEntry(void)
{
    
}