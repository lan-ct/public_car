#include "screen.h"
#include "distance.h"
#include "servo.h"
#include "move.h"
#include "state.h"
#include "hwCloud.h"
void test(int qos,char*topic,char*payload){
    printf("test RCVMSG:QOS:%d TOPIC:%s PAYLOAD:%s\r\n", qos, topic, payload);
}
void init(void){
    screenInit(); 
    distanceInit();
    S92RInit();
    stateInit();
    moveInit();
    //initCloud(test);
}
void MainThread(void)
{
    char s[60]={0};
    float angle=0.0f;
    short left,right;
    TaskMsleep(100);
    moveForward(20000);
    //string s1;
   /* while(1){
        angle= getAngle();
        get_wheel_cnt_state(&left,&right);
        printf("left:%hd",left);
        printf("right:%hd",right);
        printf("%f",angle);
        printf("\n");
        TaskMsleep(DELAY_US20*10);
    };
   //moveForward(3*1000);
   // moveBackward(3*1000);
  TaskMsleep(2000);
   leftStopTurn(90);
   TaskMsleep(1000);
   leftStopTurn(-90);
   TaskMsleep(1000);
   rightStopTurn(90);
   TaskMsleep(1000);
   rightStopTurn(-90); 
   char topic[]="$oc/devices/65fd3cbc2ccc1a58387dc57b_0001/sys/messages/up";
   TaskMsleep(60000);
   sendMessage(0,topic,"hello");*/
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
    attr.stack_size = 1024; //堆栈大小为1024 stack size 1024
    attr.priority = osPriorityNormal;
    if(osThreadNew((osThreadFunc_t)MainThread, NULL, &attr) == NULL) {
        printf("[carMain] Failed to create Task!\n");
    }
    /* */
    //initCloud(test);
   // I2CBusExampleEntry();
}

SYS_RUN(Main);