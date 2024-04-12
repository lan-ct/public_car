#include "screen.h"
#include "distance.h"
#include "servo.h"
#include "move.h"
#include "state.h"
#include "hwCloud.h"
#include "move_scan.h"
void test(int qos,char*topic,char*payload){
    printf("test RCVMSG:QOS:%d TOPIC:%s PAYLOAD:%s\r\n", qos, topic, payload);
}
void init(void){
    screenInit(); 
    S92RInit();
    stateInit();
    moveInit(); 
    distanceInit();
    // //initCloud(test);
}
void MainThread(void)
{
    char s[60]={0};
    float angle=0.0f;
    short left,right;
    TaskMsleep(1000);
    /*printf("1\n");
    printf("%f\n",GetDistance());
    printf("2\n");
    while(1)
   { 
    printf("%f\n",getAngle());
    TaskMsleep(500);
    }
    printf("3\n");*/
    struct scan_message message=step_scan();
  /* TaskMsleep(3000);
   
   angle= getAngle();
   sprintf(s,"angle:%.2f",angle);
  // screenShowRow1(s);

   // 
  
   
   
   angle= getAngle(); 
   sprintf(s,"angle:%.2f",angle);
   screenShowRow2(s);

   leftStopTurn(90);
   //TaskMsleep(2000);

   angle= getAngle(); 
   sprintf(s,"angle:%.2f",angle);
   screenShowRow3(s);*/
    ////////moveBackward(5000,NORMAL_SPEED);
   //;
    // //string s1;
   
    //leftStopTurn((char)(1));
    /*angle= getAngle();
        sprintf(s,"angleo:%.2f",angle);
        screenShowRow1(s);
        get_wheel_cnt_state(&left,&right);
        //printf("left:%hd",left);
       sprintf(s,"right:%hd",right);
       screenShowRow2(s);
        moveForward(5000,NORMAL_SPEED);
        angle= getAngle();
        sprintf(s,"angleo:%.2f",angle);
        screenShowRow3(s);
        get_wheel_cnt_state(&left,&right);
        //printf("left:%hd",left);
       sprintf(s,"right:%hd",right);
       screenShowRow4(s);
    TaskMsleep(1000);
    leftStopTurn((char)(0));
   while(1){
        angle= getAngle();
        sprintf(s,"angleo:%.2f",angle);
        screenShowRow3(s);
        get_wheel_cnt_state(&left,&right);
        //printf("left:%hd",left);
       sprintf(s,"right:%hd",right);
       screenShowRow4(s);
        //printf("%f",angle);
       // //// printf("\n");
        TaskMsleep(DELAY_US20);
     };*/
   /*//moveForward(3*1000);
   // moveBackward(3*1000);
  TaskMsleep(2000);
   leftStopTurn(90);
   TaskMsleep(1000);
   leftStopTurn(-90);
   TaskMsleep(1000);
   rightStopTurn(90);
   TaskMsleep(1000);
   rightStopTurn(-90); */

   
   //char topic[]="$oc/devices/65fd3cbc2ccc1a58387dc57b_0001/sys/messages/up";
   //TaskMsleep(60000);
   //sendMessage(0,topic,"hello");
} 
void moveThread(void){
     float angle=0.0f;
     while(1){
        angle= getAngle();

    };
}
static void Main(void)
{
    init();
    osThreadAttr_t attr;
    attr.name = "carMain";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 5*1024; //堆栈大小为1024 stack size 1024
    attr.priority = osPriorityNormal;
    if(osThreadNew((osThreadFunc_t)MainThread, NULL, &attr) == NULL) {
        printf("[carMain] Failed to create Task!\n");
    }
    /* */
    //initCloud(test);
   // I2CBusExampleEntry();
}

SYS_RUN(Main);