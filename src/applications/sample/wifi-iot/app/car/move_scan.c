#include"move.h"
#include"move_scan.h"
#include"servo.h"
#include"distance.h"
#define LEFT 0
#define RIGHT 1
#define FRONT 2
#define RESTART 1
#define CONTINUE 0
float get_distance(short direction){
    switch (direction)
    {
    case LEFT:
        RegressMiddle();
        EngineTurnLeft();
        break;
    case RIGHT:
        RegressMiddle();
        EngineTurnRight();
        break;
    case FRONT:
        RegressMiddle();
        break;
    default:
        break;
    }
    return GetDistance();
}
struct scan_message scan(void){
    //float left=0,right=0,front=0;
    struct scan_message message;
    message.left=get_distance(LEFT);
    message.front=get_distance(FRONT);
    message.right=get_distance(RIGHT);
    RegressMiddle();
    printf("distance,left:%f,right:%f,front:%f",message.left,message.right,message.front);
    return message;
}
void step(char restart){
    int cycles=100;
    moveForward_wheel(cycles,NORMAL_SPEED,restart);
}
struct scan_message step_scan(char restart){
    step(restart);
    return scan();
}


