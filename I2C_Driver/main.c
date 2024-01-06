#include "stm32f10x.h"                
#include "gp_drive.h"
#include "i2c_drive.h"
#include "systick_time.h"
#include <stdio.h>

#define AHT20_ADDRESS 0x38
#define AHT20_READ_STATUS 0x71
double actualTemperature;
double actualHumidity;
void AHT20_WaitAfterPowerOn(void);
void AHT20_ReadData(char *readBuffer, char bufferSize);
void AHT20_Initialize(void);
void AHT20_TriggerMeasurement(void);
void AHT20_WaitMeasurementComplete(void);
void calculate(char *data);

/*step 1: */
void AHT20_WaitAfterPowerOn(void)
{
	/* send 0x71 and read the status word */
	char status = 0;
	
	/* wait 40ms after power on */
	DelayMs(40);
	 
	
	I2C_start(1, 0x38);
	//I2C_add(1, AHT20_ADDRESS, 0);
	//I2C_data(1, AHT20_READ_STATUS);
	I2C_stop(1);
	
	
	//Read the status word 
	AHT20_ReadData(&status, 1);
	
	
	//check bit[3] (CAL enable)
	if (!(status & 0x08))
	{
		//CAL is not enable, need to initialize
		AHT20_Initialize();
	}
	
}
void AHT20_Initialize(void)
{
	/* send 0xBE command for initialization */
	  I2C_start(1, 0x38);
    I2C_add(1, AHT20_ADDRESS, 0);
    //I2C_data(1, 0xBE);
    //I2C_data(1, 0x08);
    //I2C_data(1, 0x00);
    I2C_stop(1);

    /* Wait for 10ms */
    DelayMs(10);
}

void AHT20_ReadData(char *readBuffer, char bufferSize)
{
	int i;
	I2C_start(1, 0x38);
	
	/*Send the device address with Read bit */
	I2C_add(1, AHT20_ADDRESS, 1);
	/* Loop to read data bytes with ACK */

	 for (i = 0; i < bufferSize - 1; i++)
    {
        //readBuffer[i] = I2C_data(1, '1', 1);
    }
	readBuffer[i] = I2C_data(1, 0, 1);
	I2C_stop(1);
	
}
/*step 2: */
void AHT20_TriggerMeasurement(void)
{
	int i;
	/* Commnand bytes for triggering measurement */
	char command_bytes[3] = {0xAC, 0x33, 0x00};
	
	/*send 0xAC for triggering measurement */
	I2C_start(1, (0x38));
	I2C_add(1, AHT20_ADDRESS, 0);
	/* loop through the command_bytes and send each bytes */
	for (i = 0; i < 3; i++)
	{
		//I2C_data(1, command_bytes[i]);
	}
	I2C_stop(1);
}


/*step 3: */
void AHT20_WaitMeasurementComplete(void)
{	
	/* Check the status word Bit [7] for measurement completion */
  char statusWord = 0;
	/* Wait for 80ms */
	DelayMs(80);
  do
   {
    /* Read the status word */
    AHT20_ReadData(&statusWord, 1);

		/* Continue to wait if Bit [7] is not 0 (measurement not completed) */
    } while (statusWord & 0x80);
}

void calculate(char *data)
{
	if ((data[0] & 0x80) == 0x00)
	{
		 uint32_t temperature = ((data[1] << 16) | (data[2] << 8) | data[3]) >> 4;
     uint32_t humidity = ((data[3] & 0x0F) << 16) | (data[4] << 8) | data[5];
		 actualTemperature = (temperature * 200.0 / 1048576.0) - 50.0;
     actualHumidity = (humidity * 100.0 / 1048576.0);
		 printf("Temperature: %.2lf, Humidity: %.2lf\n", actualTemperature, actualHumidity);
	}else
	{
		actualTemperature = 0.0;
		actualHumidity = 0.0;
		printf("Temperature: %.2lf, Humidity: %.2lf\n", actualTemperature, actualHumidity);
	}
}

int main(void)
{
	systick_init();
	I2C_init(1);
	while (1)
	{
		char data[] = {0x20, 0x51, 0x71};
		I2C_write(1, 0x38, data, 3);
		//I2C_start(1);
		/* Step 1: Wait 40ms after power-on */
    //AHT20_WaitAfterPowerOn();

    /* Step 2: Trigger measurement */
		//AHT20_TriggerMeasurement();
		
		/* Step 3: Wait for measurement completion */
		//AHT20_WaitMeasurementComplete();
		
		/* Step 4: Read six bytes of data and calculate temperature and humidity */
		//char data_sensor[6];
		//AHT20_ReadData(data_sensor, 6);
		//calculate(data_sensor);
		
	}
}


