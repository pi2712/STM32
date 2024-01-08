#include "stm32f10x.h"                
#include "gp_drive.h"
#include "i2c_drive.h"
#include "systick_time.h"


#define AHT20_ADDRESS 0x38
#define AHT20_READ_STATUS 0x71


void AHT20_Init();
void AHT20_GetData(char* sensor_data);

void AHT20_Init(){
	DelayMs(40);
	
	//Send Init command to AHT20
	char status;
	I2C_read(1, 0x38, &status, 1);
	if(!(status & (1<<3))){
		char init_command[] = {0xBE, 0x08, 0x00};
		I2C_write(1, 0x38, init_command, 3);
		DelayMs(10);
	}
}

void AHT20_GetData(char* sensor_data){
	
	
	//Send trigger measurement command
	char trigger_command[] = {0xAC, 0x38, 0x00};
	I2C_write(1, 0x38, trigger_command, 3);
	DelayMs(80);
	
	//Wait for measurement to be completed
	char status;
	do {
		DelayMs(10);
		I2C_read(1, 0x38, &status, 1);	
	}while(status & (1 << 7)); //Wait until slave is not busy with measurement
	
	//Get data
	I2C_read(1, 0x38, sensor_data, 6);
}

int main(void)
{
	systick_init();
	I2C_init(1);
	AHT20_Init();
	char sensor_data[6];
	AHT20_GetData(sensor_data);
	while (1)
	{
		
	}
}

