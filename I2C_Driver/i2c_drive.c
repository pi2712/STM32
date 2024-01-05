#include "i2c_drive.h"
#include <stdio.h>
void I2C_init(char i2c, unsigned short speed_mode)
{
	RCC->APB2ENR |= 1;/* enable clock for port B */
	if (i2c == 1)
	{
		RCC->APB1ENR |= 0x200000; /* enable clock for I2C1 */
		/* Configure GPIO */
		init_GP(PB, 6, OUT50, O_AF_OD);
		init_GP(PB, 7, OUT50, O_AF_OD);
		
		I2C1->CR1 |= 0x8000; /*Reset I2C1*/
		I2C1->CR1 &= ~0x8000; /* turn off I2C1 to configure */
		
		I2C1->CR2 = 0x8; /* send 8 bit to send or receive */
		I2C1->CCR = 40;
		I2C1->TRISE = 9; /* ensures that the frequency of the SCL signal remains stable */
		I2C1->CR1 |= 1;
	}
	else if(i2c == 2)
	{
		RCC->APB1ENR |= 0x400000;
		
		init_GP(PB, 10, OUT50, O_AF_OD);
		init_GP(PB, 11, OUT50, O_AF_OD);
		
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		
		I2C2->CR2 = 0x8;
		I2C2->CCR = speed_mode;
		I2C2->TRISE = 0x9;
		I2C2->CR1 |= 1;
	}
}
/* start step */
void I2C_start(char i2c) 
{
	uint16_t status;
	if (i2c == 1)
	{
		I2C1->CR1 |= 0x100; /* turn on bit 8 start signal */
		//while ((I2C1->SR1 & 1) == 0);/*wait bit 1 of SR1 = 1, if =1 it means start signal accepted*/
		//Read SR1 reg and write data to DR reg to clear SB flag
		status = I2C1->SR1;
		I2C1->DR = (0x38) << 1;
		while(I2C1->SR1 & (1 << 0));
		
 	}
	else if (i2c == 2)
	{
		I2C2->CR1 |= 0x100;
		while ((I2C2->SR1 & 1) == 0);
	}
}

/* sending address and Read or Write */
void I2C_add(char i2c, char address, char RW)
{
	volatile int tmp;
	if (i2c == 1)
	{
		I2C1->DR = (address | RW);
		while ((I2C1->SR1 & 2) == 0);
		while ((I2C1->SR1 & 2))
		{
			tmp = I2C1->SR1;
			tmp = I2C1->SR2;
			if ((I2C1->SR1 & 2) == 0)
			{
				break;
			}
		}
	}
	else if (i2c == 2)
	{
		I2C2->DR = (address | RW); /*assign address of device and select opt read or write */
		while ((I2C2->SR1 & 2) == 0); /* busy wait until bit ADDR = 1, it means ADDR has been processed, ACK is received from device*/
		while ((I2C2->SR1 & 2))
		{
			tmp = I2C2->SR1;/* read value of status SR1 and SR2 for clear flags or read ADDR event details*/
			tmp = I2C2->SR2;
			if ((I2C2->SR1 & 2) == 0) /* when bit ADDR = 0, ADDR event has been processed */
			{
				break;
			}
		}
	}
	
}


// Sending data step
char I2C_data(char i2c, char data)
{
 char receivedData = 0;

    if (i2c == 1)
    {
        // Wait for the data register to be empty (TXE bit)
        while (!(I2C1->SR1 & (1 << 7)));

        // Send data
        I2C1->DR = data;

        // Wait for the transmission to complete (BTF bit)
        while (!(I2C1->SR1 & (1 << 2)));

        // Read the received data
        receivedData = (char)I2C1->DR;
    }
    else if (i2c == 2)
    {
        while ((I2C2->SR1 & 0x80) == 0);
        I2C2->DR = data;
        while ((I2C2->SR1 & 0x80) == 0);
        receivedData = (char)I2C2->DR; /* read the received data, if necessary */
    }

    return receivedData;
}

void I2C_stop(char i2c)
{
	volatile int tmp;
	if (i2c == 1)
	{
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}
	else if (i2c == 2)
	{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}

void I2C_write(char i2c, char address, char data[])
{
	int i = 0;
	I2C_start(i2c);
	I2C_add(i2c, address, 0);
	while (data[i])
	{
		I2C_data(i2c, data[i]);
		i++;
	}
	I2C_stop(i2c);
}
