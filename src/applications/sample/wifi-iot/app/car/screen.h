#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio_ex.h"
#include "iot_i2c.h"
#include "iot_gpio.h"
#include "iot_errno.h"
#include "iot_watchdog.h"
#include "hi_errno.h"
#include "hi_i2c.h"
#include "oled_ssd1306.h"

#define IOT_I2C_IDX_BAUDRATE (400 * 1000)
#define CW2015_I2C_IDX 0
#define IOT_PWM_PORT_PWM3   3
#define CW2015_READ_ADDR     (0xC5)
#define CW2015_WRITE_ADDR    (0xC4)
#define WRITELEN  2
#define CW2015_HIGHT_REGISTER 0x02
#define CW2015_LOW_REGISTER   0x03
#define CW2015_WAKE_REGISTER  0x0A
#define DELYA_US20            20

/*
 * @berf i2c read
 * @param hi_u8 reg_high_8bit_cmd:Transmit register value 8 bits high
 * @param hi_u8 reg_low_8bit_cmd:Transmit register value low 8 bits
 * @param hi_u8* recv_data:Receive data buff
 * @param hi_u8 send_len:Sending data length
 * @param hi_u8 read_len:Length of received data
 */
uint32_t Cw20_WriteRead(uint8_t reg_high_8bit_cmd, uint8_t send_len, uint8_t read_len);

uint32_t Cw20_Write(uint8_t addr, uint8_t writedata, uint32_t buffLen);

void CW2015Init(void);

float GetVoltage(void);

void screenInit(void);

void screenClear(void);

void screenShow(const char* str);

void screenShowRow1(const char* str);

void screenShowRow2(const char* str);

void screenShowRow3(const char* str);

void screenShowRow4(const char* str);