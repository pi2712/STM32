#include "stm32f10x.h"
#include "gp_drive.h"



#define I2C_READ	1
#define I2C_WRITE	0

void I2C_init();
void I2C_write(uint8_t address, uint8_t *data, uint8_t dataSize);
void I2C_start(uint8_t address, uint8_t ReadWriteMode);
void I2C_data(uint8_t *data, uint8_t dataSize);
void I2C_stop(void);
void I2C_read(uint8_t address, uint8_t* data, uint8_t dataSize);
