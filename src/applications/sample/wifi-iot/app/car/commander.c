#include"move.h"
#include"move_scan.h"
#define MOVING_COMMAND_NAME    "carMoving"
#define TURN_LEFT "LEFT"
#define TURN_RIGHT "RIGHT"
#define FORWARD "FORWARD"
#define STOP "STOP"
void process_message(int qos, char *topic, char *payload){
    if (strstr(payload, MOVING_COMMAND_NAME) != 0) {
        moving(payload);
    }
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