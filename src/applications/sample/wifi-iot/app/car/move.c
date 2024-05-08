#include"move.h"
#include <stdio.h>
#include <math.h>

// PID控制器结构体
typedef struct {
    float kp, ki, kd;  // PID参数
    float error, integral, derivative;  // 内部状态
} PIDController;
PIDController yawPID_forward;
PIDController yawPID_back;
// 初始化PID控制器
void initPID(PIDController *pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->error = 0.0f;
    pid->integral = 0.0f;
    pid->derivative = 0.0f;
}

// 更新PID控制器状态并计算控制输出
float updatePID(PIDController *pid, float target, float current, float dt) {
    float error = target - current;  // 当前偏差

    pid->integral += error * dt;  // 积分项更新
    pid->derivative = (error - pid->error) / dt;  // 微分项计算

    float output = pid->kp * error + pid->ki * pid->integral + pid->kd * pid->derivative;  // PID输出

    pid->error = error;  // 保存当前偏差供下次计算

    return output;
}

float direct_conv=0.0f;
short left_wheel=0,right_wheel=0;
void moveInit(void){
   IoTWatchDogDisable(); 
   GA12N20Init();
}
void moveForward(int times,int speed){
   int left_speed=speed,right_speed=speed;
   //float now=get_yaw_conv();
   //float dt = DELYA_LOOP_MS;
   
   /*while(times>0){
      getBalanceSpeed(&left_speed,&right_speed,speed);
      car_forward(left_speed,right_speed);
      //now=get_yaw_conv();
      //bt=now-direct_conv;
      while(1){
         now=get_yaw_conv();
         if(now-direct_conv-bt)
         TaskMsleep(DELYA_LOOP_MS);
         times-=DELYA_LOOP_MS;
      }
      TaskMsleep(DELYA_LOOP_MS);
      times-=DELYA_LOOP_MS;
   }
    // 假设已知的PID参数
    float kp = 0.1f;
    float ki = 0.005f;
    float kd = 0.002f;

    // 初始化PID控制器
    
    initPID(&yawPID, kp, ki, kd);

    // 假设每秒更新一次
    direct_conv=get_yaw_conv(); */
   initPID(&yawPID_forward,0.1,0,0.01);
   direct_conv= get_yaw_conv();
    // 示例循环，模拟持续获取偏航角并调整电机转速差
    while(times>0){
      get_wheel_cnt(&left_wheel,&right_wheel);
      getBalanceSpeed_forward(&left_speed,&right_speed,speed);
      car_forward(left_speed,right_speed);
      TaskMsleep(DELYA_LOOP_MS);
      times-=DELYA_LOOP_MS;
   } 

   car_stop();
}
/*void moveForward_wheel(int cycles,int speed){
   int left_speed=speed,right_speed=speed;
   int last=left_wheel;
   initPID(&yawPID_forward,0.1,0,0.01);
   direct_conv= get_yaw_conv();
    while(left_wheel-last<cycles){
      get_wheel_cnt(&left_wheel,&right_wheel);
      getBalanceSpeed_forward(&left_speed,&right_speed,speed);
      car_forward(left_speed,right_speed);
      TaskMsleep(DELYA_LOOP_MS);
   }  
   car_stop();
}*/
void moveForward_wheel(int cycles,int speed,char restart){
   int left_speed=speed,right_speed=speed;
   short last=get_wheel_cnt_left();
   short now=last;
   if(restart){
      initPID(&yawPID_forward,0.1,0,0.01);
      direct_conv= get_yaw_conv();
   }
   printf("before:%d\n",now);
   while(now-last<cycles){
      //get_wheel_cnt(&left_wheel,&right_wheel);
      now=get_wheel_cnt_left();
      getBalanceSpeed_forward(&left_speed,&right_speed,speed);
      car_forward(left_speed,right_speed);
      TaskMsleep(DELYA_LOOP_MS);
      printf("wheel:%d\n",now);
   }  
   printf("later:%d\n",now);
   car_stop();
}
void getBalanceSpeed_forward(int*left_speed,int*right_speed,int speed){
  /* float conv=get_yaw_conv();
   //char s[30];
   float k=0.5f;
   float direct=conv-direct_conv;
   *left_speed=speed;
   *right_speed=speed;
   //snprintf(s,sizeof(s),"conv:%.2f",conv);
   //screenShow(s);
   
   if(direct<0){
      *right_speed=speed-(int)(direct*k);
   }
   else if(direct>0){
      *left_speed=speed+(int)(direct*k);
   }*/
 // 假设从传感器获取到当前偏航角（这里使用固定值代替实际传感器数据）
   float currentYawAngle = get_yaw_conv();  // 当前偏航角（单位：度）

   // 直行目标偏航角
   float targetYawAngle = direct_conv;
   float dt = (float)DELYA_LOOP_MS/1000;
   // 计算偏航角偏差并更新PID控制器
   float yawError = targetYawAngle-currentYawAngle;
   float controlOutput = updatePID(&yawPID_forward, targetYawAngle, currentYawAngle, dt);

   // 将PID输出转换为电机转速差（这里仅做概念演示，实际转换需考虑电机特性和硬件限制）
   float motorSpeedDifference = controlOutput*10;  // 举例：控制输出乘以一个系数
   *left_speed=speed;
   *right_speed=speed;
   motorSpeedDifference=motorSpeedDifference>0?motorSpeedDifference:-motorSpeedDifference;
   if(yawError>0){
      *right_speed=speed+motorSpeedDifference;
   }
   else if(yawError<0){
      *left_speed=speed+motorSpeedDifference;
   }      
   printf("left:%d right:%d yawError:%f dif:%f angle:%.2f\n",*left_speed,*right_speed,yawError,motorSpeedDifference,currentYawAngle);
        //printf("Current yaw angle: %.2f degrees, Motor speed difference: %.2f\n", currentYawAngle, motorSpeedDifference);

        // 延迟一秒，模拟下一次循环
        // 实际应用中应使用合适的定时器或任务调度机制
       // sleep(1);
   /*    
   short left=0,right=0;
   float k=0.8f;
   float s_l_now=0.0f,s_r_now=00.0f;
   get_wheel_cnt(&left,&right);
   s_l_now=(float)(left-left_wheel)/DELYA_LOOP_MS;
   s_r_now=(float)(right-right_wheel)/DELYA_LOOP_MS;
   if(s_l_now>s_r_now){
      *left_speed=speed+(s_l_now-s_r_now)*k;
      *right_speed=speed;
   }
   else if(s_l_now<s_r_now){
      *right_speed=speed+(s_r_now-s_l_now)*k;
      *left_speed=speed;
   }
*/

}
void getBalanceSpeed_back(int*left_speed,int*right_speed,int speed){
  /* float conv=get_yaw_conv();
   //char s[30];
   float k=0.5f;
   float direct=conv-direct_conv;
   *left_speed=speed;
   *right_speed=speed;
   //snprintf(s,sizeof(s),"conv:%.2f",conv);
   //screenShow(s);
   
   if(direct<0){
      *right_speed=speed-(int)(direct*k);
   }
   else if(direct>0){
      *left_speed=speed+(int)(direct*k);
   }*/
 // 假设从传感器获取到当前偏航角（这里使用固定值代替实际传感器数据）
   float currentYawAngle = get_yaw_conv();  // 当前偏航角（单位：度）

   // 直行目标偏航角
   float targetYawAngle = direct_conv;
   float dt = (float)DELYA_LOOP_MS/1000;
   // 计算偏航角偏差并更新PID控制器
   float yawError =  targetYawAngle-currentYawAngle;
   float controlOutput = updatePID(&yawPID_back, targetYawAngle, currentYawAngle, dt);

   // 将PID输出转换为电机转速差（这里仅做概念演示，实际转换需考虑电机特性和硬件限制）
   float motorSpeedDifference = controlOutput * 10;  // 举例：控制输出乘以一个系数
   motorSpeedDifference=motorSpeedDifference>0?motorSpeedDifference:-motorSpeedDifference;
   *left_speed=speed;
   *right_speed=speed;
   if(yawError>0){
      *left_speed=speed+motorSpeedDifference;
   }
   else if(yawError<0){
       *right_speed=speed+motorSpeedDifference;
   }      
   printf("left:%d right:%d yawError:%f dif:%f angle:%.2f\n",*left_speed,*right_speed,yawError,motorSpeedDifference,currentYawAngle);
        //printf("Current yaw angle: %.2f degrees, Motor speed difference: %.2f\n", currentYawAngle, motorSpeedDifference);

        // 延迟一秒，模拟下一次循环
        // 实际应用中应使用合适的定时器或任务调度机制
       // sleep(1);
   /*    
   short left=0,right=0;
   float k=0.8f;
   float s_l_now=0.0f,s_r_now=00.0f;
   get_wheel_cnt(&left,&right);
   s_l_now=(float)(left-left_wheel)/DELYA_LOOP_MS;
   s_r_now=(float)(right-right_wheel)/DELYA_LOOP_MS;
   if(s_l_now>s_r_now){
      *left_speed=speed+(s_l_now-s_r_now)*k;
      *right_speed=speed;
   }
   else if(s_l_now<s_r_now){
      *right_speed=speed+(s_r_now-s_l_now)*k;
      *left_speed=speed;
   }
*/

}
void moveBackward(int times,int speed){
  int left_speed=speed,right_speed=speed;
   //float now=get_yaw_conv();
   //float dt = DELYA_LOOP_MS;
   
   /*while(times>0){
      getBalanceSpeed(&left_speed,&right_speed,speed);
      car_forward(left_speed,right_speed);
      //now=get_yaw_conv();
      //bt=now-direct_conv;
      while(1){
         now=get_yaw_conv();
         if(now-direct_conv-bt)
         TaskMsleep(DELYA_LOOP_MS);
         times-=DELYA_LOOP_MS;
      }
      TaskMsleep(DELYA_LOOP_MS);
      times-=DELYA_LOOP_MS;
   }
    // 假设已知的PID参数
    float kp = 0.1f;
    float ki = 0.005f;
    float kd = 0.002f;

    // 初始化PID控制器
    
    initPID(&yawPID, kp, ki, kd);

    // 假设每秒更新一次
    direct_conv=get_yaw_conv(); */
    initPID(&yawPID_back,0.1,0.01,0.01);
    direct_conv= get_yaw_conv();
    // 示例循环，模拟持续获取偏航角并调整电机转速差
    while(times>0){
      get_wheel_cnt(&left_wheel,&right_wheel);
      getBalanceSpeed_back(&left_speed,&right_speed,speed);
      car_backward(left_speed,right_speed);
      TaskMsleep(DELYA_LOOP_MS);
      times-=DELYA_LOOP_MS;
   } 

   car_stop();
}
void leftStopTurn(char left){
      
    /*float last=get_yaw_conv();
    float dst=angle+last;
    float now=last;
    car_stop();
    if(angle<0){
    car_backward(0,NORMAL_SPEED_TURN);
    while(now>dst){
       TaskMsleep(DELYA_LOOP_MS);
       now=get_yaw_conv();
    } 
    }
    else if(angle>0){
    car_forward(0,NORMAL_SPEED_TURN);
    while(now<dst){
       TaskMsleep(DELYA_LOOP_MS);
       now=get_yaw_conv();
    } 
    }*/
    short go=770;//800
    short wheel_begin=get_wheel_cnt_right();
    short wheel_dst=0;
    if(left>0){
        wheel_dst=wheel_begin+go;
        car_forward(0,NORMAL_SPEED_TURN);
        while(wheel_dst>get_wheel_cnt_right()){
         TaskMsleep(DELYA_LOOP_MS_TURN);
        }
    }
    else{
        wheel_dst=wheel_begin-go;
        car_backward(0,NORMAL_SPEED_TURN);
        while(wheel_dst<get_wheel_cnt_right()){
         TaskMsleep(DELYA_LOOP_MS_TURN);
        }
    }
    car_stop();
}
void rightStopTurn(char left){
    /*float last=get_yaw_conv();
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
    }*/
    short go=770;//800
    short wheel_begin=get_wheel_cnt_left();
    short wheel_dst=0;
    //printf("now:%d\n",wheel_begin);
    printf("begin:%d\n",get_wheel_cnt_left());
    if(left>0){
        wheel_dst=wheel_begin-go;
        //setStop(car_stop,wheel_dst);
        car_backward(NORMAL_SPEED_TURN,0);
        while(wheel_dst<get_wheel_cnt_left()){
         TaskMsleep(DELYA_LOOP_MS_TURN);
        }////////
    }
    else{
        wheel_dst=wheel_begin+go;
        //setStop(car_stop,wheel_dst);
        car_forward(NORMAL_SPEED_TURN,0); 
        while(wheel_dst>get_wheel_cnt_left()){
         TaskMsleep(DELYA_LOOP_MS_TURN);
         printf("now:%d\n",get_wheel_cnt_left());
        }////////
    }
    car_stop();
    printf("later:%d\n",get_wheel_cnt_left());
}

//6左后 5左前
//10右前 9右后 