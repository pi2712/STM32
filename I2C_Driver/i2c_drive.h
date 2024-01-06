#include "stm32f10x.h"
#include "gp_drive.h"

#define I2C_FM 0x2D /* Fast mode */
#define I2C_SM 0xB4 /* Standard mode */

#define I2C_READ	1
#define I2C_WRITE	0

void I2C_init(char i2c);
void I2C_write(char i2c, char address, char* data, char dataSize);
void I2C_start(char i2c, uint8_t address, uint8_t ReadWriteMode);
void I2C_add(char i2c, char address, char RW);
char I2C_receive(char i2c, char data);
char I2C_data(char i2c, char* data, char dataSize);
void I2C_stop(char i2c);
char I2C_read(char i2c, char address,char* data, char dataSize);
