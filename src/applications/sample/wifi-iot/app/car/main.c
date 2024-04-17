#include "screen.h"
#include "distance.h"
#include "servo.h"
#include "move.h"
#include "state.h"
#include "hwCloud.h"
#include "move_scan.h"
#include "commander.h"
void test(int qos,char*topic,char*payload){
    printf("test RCVMSG:QOS:%d TOPIC:%s PAYLOAD:%s\r\n", qos, topic, payload);
}
void init(void){
    screenInit(); 
    S92RInit();
    stateInit();
    moveInit(); 
    distanceInit();
    initCloud(process_message);

}
void MainThread(void)
{
    //rightStopTurn(0);
    /*int left,right;
    char s[40];
    while (1)
    {
        get_wheel_cnt_state(&left,&right);
        printf("left:%d,right:%d\n",left,right);
        TaskMsleep(1000);
    }*/
    
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