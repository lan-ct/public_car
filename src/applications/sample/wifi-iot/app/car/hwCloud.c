

#include"hwCloud.h"

void initCloud(FnMsgCallBack MsgRcvCallBack){
    IoTWatchDogDisable();
    ConnectToHotspot();
    CJsonInit();
    IoTMain();
    IoTSetMsgCallback(MsgRcvCallBack);/**/
}
int sendMessage(int qos, char *topic, char *payload){
    return IotSendMsg(qos,topic,payload); 
}