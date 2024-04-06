

#include"move.h"
void moveInit(void){
   /*IoTGpioInit(IOT_IO_NAME_GPIO_5);
    // 设置GPIO9的管脚复用关系为GPIO Set the pin reuse relationship of GPIO9 to GPIO
    IoSetFunc(IOT_IO_NAME_GPIO_5, IOT_IO_FUNC_GPIO_5_GPIO);
    // GPIO方向设置为输出 GPIO direction set to output
    IoTGpioSetDir(IOT_IO_NAME_GPIO_5, IOT_GPIO_DIR_OUT);

    IoTGpioInit(IOT_IO_NAME_GPIO_6);
    // 设置GPIO9的管脚复用关系为GPIO Set the pin reuse relationship of GPIO9 to GPIO
    IoSetFunc(IOT_IO_NAME_GPIO_6, IOT_IO_FUNC_GPIO_6_GPIO);
    // GPIO方向设置为输出 GPIO direction set to output
    IoTGpioSetDir(IOT_IO_NAME_GPIO_6, IOT_GPIO_DIR_OUT);

    // LED3的GPIO初始化 GPIO initialization of LED3
    IoTGpioInit(IOT_IO_NAME_GPIO_9);
    // 设置GPIO9的管脚复用关系为GPIO Set the pin reuse relationship of GPIO9 to GPIO
    IoSetFunc(IOT_IO_NAME_GPIO_9, IOT_IO_FUNC_GPIO_9_GPIO);
    // GPIO方向设置为输出 GPIO direction set to output
    IoTGpioSetDir(IOT_IO_NAME_GPIO_9, IOT_GPIO_DIR_OUT);

    // LED3的GPIO初始化 GPIO initialization of LED3
    IoTGpioInit(IOT_IO_NAME_GPIO_10);
    // 设置GPIO9的管脚复用关系为GPIO Set the pin reuse relationship of GPIO9 to GPIO
    IoSetFunc(IOT_IO_NAME_GPIO_10, IOT_IO_FUNC_GPIO_10_GPIO);
    // GPIO方向设置为输出 GPIO direction set to output
    IoTGpioSetDir(IOT_IO_NAME_GPIO_10, IOT_GPIO_DIR_OUT);*/
   IoTWatchDogDisable(); 
   GA12N20Init();
     
}
void leftForwardON(){
    
}
void moveForward(int times){
    /*IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_10, IOT_GPIO_VALUE1);
    TaskMsleep(times);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_10, IOT_GPIO_VALUE0);*/
    int pwm=45;
    printf("here");
    car_forward(pwm,pwm); 
    TaskMsleep(times);
    car_stop();
}
void moveBackward(int times){
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE1);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_9, IOT_GPIO_VALUE1);
    TaskMsleep(times);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_9, IOT_GPIO_VALUE0);
}
void leftStopTurn(float angle){
    float last=get_yaw_conv();
    float dst=angle+last;
    float now=last;
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    if(angle<0){
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_9, IOT_GPIO_VALUE1);
    while(now>dst){
       TaskMsleep(10);
       now=get_yaw_conv();
    } 
    
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_9, IOT_GPIO_VALUE0);
    }
    else if(angle>0){
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_10, IOT_GPIO_VALUE1);
    while(now<dst){
       TaskMsleep(10);
       now=get_yaw_conv();
    } 
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_10, IOT_GPIO_VALUE0);
    }
}
void rightStopTurn(float angle){
    float last=get_yaw_conv();
    float dst=angle+last;
    float now=last;
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_9, IOT_GPIO_VALUE0);
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_10, IOT_GPIO_VALUE0);
    if(angle<0){
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE1);
    while(now>dst){
       TaskMsleep(10);
       now=get_yaw_conv();
    } 
    
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_5, IOT_GPIO_VALUE0);
    }
    else if(angle>0){
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE1);
    while(now<dst){
       TaskMsleep(10);
       now=get_yaw_conv();
    } 
    IoTGpioSetOutputVal(IOT_IO_NAME_GPIO_6, IOT_GPIO_VALUE0);
    }
}

//6左后 5左前
//10右前 9右后 