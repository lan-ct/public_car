#include "move.h"
#include "move_scan.h"
#include "hwCloud.h"
#include "iot_profile.h"
#include "state.h"

#define MOVING_COMMAND_NAME "moveForward"

#define TURN_COMMAND_NAME "turn"
#define TURN_LEFT "left"
#define TURN_RIGHT "right"

#define SCAN_COMMAND_NAME "scan"
#define SCAN_LEFT "left"
#define SCAN_RIGHT "right"
#define SCAN_FRONT "front"
#define SCAN_ALL "all"

#define STOP "STOP"
#define CN_COMMAND_INDEX "commands/request_id="
void reportStatus(const char *message)
{
  IoTProfileService service;
    IoTProfileKV property;
    memset_s(&property, sizeof(property), 0, sizeof(property));
    property.type = EN_IOT_DATATYPE_STRING;
    property.key = "status";
    property.value = message;
    memset_s(&service, sizeof(service), 0, sizeof(service));
    service.serviceID = "ControllModule";
    service.serviceProperty = &property;
     /* printf("\nreport\n");
    IoTProfilePropertyReport(CONFIG_DEVICE_ID, &service);*/
    //$oc/devices/{device_id}/sys/messages/up
    IoTProfilePropertyUp(CONFIG_DEVICE_ID, &service);
}
void feedBack(char *topic)
{
    const char *requesID;
    char *tmp;
    IoTCmdResp resp;
    tmp = strstr(topic, CN_COMMAND_INDEX);
    if (tmp != NULL)
    {
        // /< now you could deal your own works here --THE COMMAND FROM THE PLATFORM
        // /< now er roport the command execute result to the platform
        requesID = tmp + strlen(CN_COMMAND_INDEX);
        resp.requestID = requesID;
        resp.respName = NULL;
        resp.retCode = 0; ////< which means 0 success and others failed
        resp.paras = NULL;
        (void)IoTProfileCmdResp(CONFIG_DEVICE_PWD, &resp);
    }
}
void process_message(int qos, char *topic, char *payload)
{ 
    struct scan_message message={0,0,0};
    char message_string[100];
    if (strstr(payload, MOVING_COMMAND_NAME) != 0)
    {
        moving(payload);
        // reportStatus();
    }
    else if (strstr(payload, TURN_COMMAND_NAME) != 0)
    {
        turn(payload);
        // reportStatus();
        message=scan();
        make_status(message_string,message);
        reportStatus(message_string); 
    }
    else if (strstr(payload, SCAN_COMMAND_NAME) != 0)
    {
        command_scan(payload);
        // reportStatus();
    }
    feedBack(topic);
}
void make_status(char *dst_message, const struct scan_message src_message)
{
    sprintf(dst_message, "{\"front\":%.0f,\"left\":%.0f,\"right\":%.0f,\"cycles\":%hd}", src_message.front, src_message.left, src_message.right, get_wheel_cnt_left());
    printf(dst_message);
}
void moving(char *payload)
{
    struct scan_message message={0,0,0};
    char message_string[100];
    char *begin;
    int cycles = 0, i = 0;
    char restart;
    begin = strstr(payload, "cycles") + strlen("cycles") + 2;
    while (begin[i] != '\0' && begin[i] >= '0' && begin[i] <= '9')
    {
        cycles *= 10;
        cycles += begin[i] - '0';
        i++;
    }
    restart = strstr(payload, "true") != NULL;
    printf("cycles:%d\n", cycles);
    if (restart)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    moveForward_wheel(cycles, NORMAL_SPEED, restart);
    message=scan();
    make_status(message_string,message);
    reportStatus(message_string); 
}
//$oc/devices/{device_id}/sys/commands/response/request_id={request_id}
void turn(char *payload)
{
    struct scan_message message;
    char message_string[100];
    if (strstr(payload, TURN_LEFT) != 0)
    {
        rightStopTurn(1);
    }
    else if (strstr(payload, TURN_RIGHT) != 0)
    {
        rightStopTurn(0);
    }
}
void command_scan(char *payload)
{
    struct scan_message message={0,0,0};
    char message_string[100];
    if (strstr(payload, SCAN_LEFT) != 0)
    {
        message.left=get_distance(LEFT);
    }
    else if (strstr(payload, SCAN_RIGHT) != 0)
    {
        message.right=get_distance(RIGHT);
    }
    else if (strstr(payload, SCAN_FRONT) != 0)
    {
        message.front=get_distance(FRONT);
    }
    else if (strstr(payload,SCAN_ALL) != 0)
    {
        message=scan();
    }
    make_status(message_string,message);
    reportStatus(message_string); 
}