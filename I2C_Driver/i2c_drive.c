#include "i2c_drive.h"
#include "stm32f10x.h"                 

void I2C_init(char i2c)
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
}
/* start step */
void I2C_start(char i2c, uint8_t address, uint8_t ReadWriteMode) 
{
	if (i2c == 1)
	{
		
		// Generate Start condition
		I2C1->CR1 |= 0x100; /* turn on bit 8 start signal */
		
		while ((I2C1->SR1 & 1) == 0);/*wait SB bit = 1, if =1 it means start signal accepted*/
		I2C1->DR = ((address) << 1) | ReadWriteMode;
		while(I2C1->SR1 & (1 << 0)); //Wait to reset SB bit
		while(!(I2C1->SR1 & (1 << 1)));//Wait ADDR bit to set
		uint8_t tmp = I2C1->SR1;/* read value of status SR1 and SR2 for clear flags or read ADDR event details*/
		tmp = I2C1->SR2;		
		while(I2C1->SR1 & (1 << 1));//Wait ADDR bit to reset
 	}
}

// Sending data step
void I2C_data(char i2c, char* data, char dataSize)
{
    if (i2c == 1)
    {
			uint8_t count = 0;
			while (count < dataSize){
					while ((I2C1->SR1 & 0x80) == 0); /* wait for TxE, indicating data register is empty and ready to receive new data */
					I2C1->DR = data[count]; /* begin the process of transmitting data */
					count++;
					while ((I2C1->SR1 & 0x80) == 0);  //Wait until buffer is empty	
			}
    }
}

void I2C_write(char i2c, char address, char* data, char dataSize)
{

	I2C_start(i2c, address, I2C_WRITE);
	I2C_data(i2c, data, dataSize);
}

void I2C_stop(char i2c) {
    if (i2c == 1) {
        // Generate Stop condition
        I2C1->CR1 |= (1 << 9); // Set the 9th bit (STOP bit) in CR1 register

        // Wait for stop condition to be executed
        while (I2C1->CR1 & (1 << 9)); // Wait until the STOP bit is cleared
    }
}




void I2C_read(char i2c, char address, char* data, char dataSize) {
   if (i2c == 1)
	 {
		 //select mode read
		 I2C_start(i2c, address, I2C_READ);
		 uint8_t cnt = 0;
		 while (cnt < dataSize)
		 {
			 if (cnt == dataSize - 1)
			 {
				 I2C1->CR1 &= ~(1 << 10); //for last byte send NACK
			 }
			 else 
			 {
				 I2C1->CR1 |= (1 << 10); // send ACK
			 }
			 while ((I2C1->SR1 & (1 << 6)) == 0); // wait until RxNe set
			 
			 data[cnt] = I2C1->DR;
			 cnt++;
		 }
		 I2C_stop(i2c);
	 }
}


