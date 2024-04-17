#include"move.h"
#include"move_scan.h"
#include"hwCloud.h"
#include"iot_profile.h"
#define MOVING_COMMAND_NAME    "carMoving"
#define TURN_LEFT "LEFT"
#define TURN_RIGHT "RIGHT"
#define FORWARD "FORWARD"
#define STOP "STOP"
#define CN_COMMAND_INDEX                    "commands/request_id="
void reportStatus(){
    IoTProfileService service;
    IoTProfileKV property;
    memset_s(&property, sizeof(property), 0, sizeof(property));
    property.type = EN_IOT_DATATYPE_STRING;
    property.key = "status";
    property.value = "12345";
    memset_s(&service, sizeof(service), 0, sizeof(service));
    service.serviceID = "ControllModule";
    service.serviceProperty = &property;
    printf("\nreport\n");
    IoTProfilePropertyReport(CONFIG_DEVICE_ID, &service);
}
void feedBack(char *topic){
    const char *requesID;
    char *tmp;
    IoTCmdResp resp;
    tmp = strstr(topic, CN_COMMAND_INDEX);
    if (tmp != NULL) {
        // /< now you could deal your own works here --THE COMMAND FROM THE PLATFORM
        // /< now er roport the command execute result to the platform
        requesID = tmp + strlen(CN_COMMAND_INDEX);
        resp.requestID = requesID;
        resp.respName = NULL;
        resp.retCode = 0;   ////< which means 0 success and others failed
        resp.paras = NULL;
        (void)IoTProfileCmdResp(CONFIG_DEVICE_PWD, &resp);
    }
}
void process_message(int qos, char *topic, char *payload){
    if (strstr(payload, MOVING_COMMAND_NAME) != 0) {
        moving(payload);
        //reportStatus();
    }
    feedBack(topic);
}
static char restart=1;
void moving(char *payload){
    if(strstr(payload, TURN_LEFT) != 0){
        rightStopTurn(1);
        restart=1;
    }
    else if(strstr(payload, TURN_RIGHT) != 0){
        rightStopTurn(0);
        restart=1;
    }
    else if(strstr(payload, FORWARD) != 0){
        step_scan(restart);
        restart=0;
    }
    else if(strstr(payload, STOP) != 0){
        
    }
}
//$oc/devices/{device_id}/sys/commands/response/request_id={request_id}
