#include"screen.h"
uint32_t Cw20_WriteRead(uint8_t reg_high_8bit_cmd, uint8_t send_len, uint8_t read_len)
{
    uint32_t status = 0;
    uint32_t ret = 0;
    uint8_t recvData[888] = { 0 };
    hi_i2c_data i2c_write_cmd_addr = { 0 };
    uint8_t send_user_cmd[1] = {reg_high_8bit_cmd};
    memset(recvData, 0x0, sizeof(recvData));
    i2c_write_cmd_addr.send_buf = send_user_cmd;
    i2c_write_cmd_addr.send_len = send_len;

    i2c_write_cmd_addr.receive_buf = recvData;
    i2c_write_cmd_addr.receive_len = read_len;

    status = hi_i2c_writeread(CW2015_I2C_IDX, CW2015_READ_ADDR, &i2c_write_cmd_addr);
    if (status != IOT_SUCCESS) {
        printf("I2cRead() failed, %0X!\n", status);
        return status;
    }
    ret = recvData[0];
    return ret;
}

uint32_t Cw20_Write(uint8_t addr, uint8_t writedata, uint32_t buffLen)
{
    uint8_t buffer[2] = {addr, writedata};
    uint32_t retval = IoTI2cWrite(CW2015_I2C_IDX, CW2015_WRITE_ADDR, buffer, buffLen);
    if (retval != IOT_SUCCESS) {
        printf("IoTI2cWrite(%02X) failed, %0X!\n", buffer[0], retval);
        return retval;
    }
    //printf("IoTI2cWrite(%02X)\r\n", buffer[0]);
    return IOT_SUCCESS;
}

void CW2015Init(void)
{
    /*
     * 初始化I2C设备0，并指定波特率为400k
     * Initialize I2C device 0 and specify the baud rate as 400k
     */
    IoTI2cInit(CW2015_I2C_IDX, IOT_I2C_IDX_BAUDRATE);
    /*
     * 设置I2C设备0的波特率为400k
     * Set the baud rate of I2C device 0 to 400k
     */
    IoTI2cSetBaudrate(CW2015_I2C_IDX, IOT_I2C_IDX_BAUDRATE);
    /*
     * 设置GPIO13的管脚复用关系为I2C0_SDA
     * Set the pin reuse relationship of GPIO13 to I2C0_ SDA
     */
    IoSetFunc(IOT_IO_NAME_GPIO_13, IOT_IO_FUNC_GPIO_13_I2C0_SDA);
    /*
     * 设置GPIO14的管脚复用关系为I2C0_SCL
     * Set the pin reuse relationship of GPIO14 to I2C0_ SCL
     */
    IoSetFunc(IOT_IO_NAME_GPIO_14, IOT_IO_FUNC_GPIO_14_I2C0_SCL);
    /* 使电量检测模块从sleep mode变为wake up mode,0x00代表唤醒,0x11代表沉睡,2代表2bit控制 */
    /* Change the power detection module from sleep mode to wake up mode. */
    /* 0x00 represents wake-up, 0x11 represents deep sleep, and 2 bit control */
    Cw20_Write(CW2015_WAKE_REGISTER, 0x00, 2);
}

float GetVoltage(void)
{
    uint8_t buff[WRITELEN] = {0};
    float voltage = 0;
    uint32_t temp = 0;
    // 读取电压的前6位 Read the first 6 bits of voltage
    buff[0] = Cw20_WriteRead(CW2015_HIGHT_REGISTER, 1, 1);
    // 读取电压的后8位 Read the last 8 bits of voltage
    buff[1] = Cw20_WriteRead(CW2015_LOW_REGISTER, 1, 1);
    /* 通过位运算最后得到14位的A/D测量值 */
    /* The final 14 bit A/D measurement value is obtained through bit operation */
    /* 将buf[0]左移8位与buf[1]组成最终电压值 */
    /* Move buf [0] to the left by 8 bits to form the final voltage value with buf [1] */
    temp = (buff[0] << 8) | buff[1];
    /* 通过计算得到最终的电压值 （CW2015的电压分辨率为305.0uV,转换1uv = 1 / 1000000） */
    /* The final voltage value is obtained through calculation */
    /* the voltage resolution of CW2015 is 305.0uV, and the conversion 1uv=1/1000000) */
    voltage = temp * 305.0 / 1000000;
    return voltage;
}

void screenInit(void){
    CW2015Init();
    OledInit();
    OledFillScreen(0);
}

void screenClear(void){
     OledFillScreen(0);
}

void screenShow(const char* str){
    int len=strlen(str);
    int i=0;
    char text[49]={0};
    for(i=0;i<49;i++){
        text[i]=' ';
    }
    text[48]='\0';
    if(len<48){
       memcpy(text,str,len);
       OledShowString(0, 0, text, 1);
    }
    else{
       OledShowString(0, 0, str, 1);
    }
}
void screenShowRow1(const char* str){
       OledShowString(0, 0, str, 1);
}
void screenShowRow2(const char* str){
       OledShowString(0, 1, str, 1);
}
void screenShowRow3(const char* str){
       OledShowString(0, 2, str, 1);
}
void screenShowRow4(const char* str){
       OledShowString(0, 3, str, 1);
}