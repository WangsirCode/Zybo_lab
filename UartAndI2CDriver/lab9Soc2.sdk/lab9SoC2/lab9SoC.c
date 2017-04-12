/*
 * lab9SoC.c
 *
 *  Created on: 3/27/2017
 *  Author: wangyuhao
 */
#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"
#include <stdio.h>
#include <xiicps.h>
#include "xgpio.h"
#include <string.h>

#define PS_DEVICE_ID		XPAR_PS7_I2C_0_DEVICE_ID
#define PL_DEVICE_ID		XPAR_PS7_I2C_1_DEVICE_ID

#define IIC_SLAVE_ADDR 0b1001000

#define IIC_SCLK_RATE		100000  //100khz

#define LEN 30

XIicPs tmpPS;		/**< Instance of the IIC Device */
XIicPs tmpPL;

XGpio uart;
XGpio uart_full;

XIicPs_Config *tmpPS_config,*tmpPL_config;

u8 PSBuffer[2];
u8 PLBuffer[2];

#define DELEYLOOPCOUNT 200000000

void delayLoop();
int initilization();
void readTemp();
int main()
{
	initilization();
	while(1)
	{
		readTemp();
		delayLoop();
	}
	return 0;
}

/* init func*/
int initilization()
{
	int Status;
	char resolution[2] = { 0b00000001, 0b01100000 };
	char setToZero = 0;
	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table,
	 * then initialize it.
	 */
	tmpPS_config = XIicPs_LookupConfig(PS_DEVICE_ID);
	if (NULL == tmpPS_config) {
		return XST_FAILURE;
	}

	tmpPL_config = XIicPs_LookupConfig(PL_DEVICE_ID);
	if (NULL == tmpPL_config) {
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(&tmpPS, tmpPS_config, tmpPS_config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(&tmpPL, tmpPL_config, tmpPL_config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

/* Perform a self-test to ensure that the hardware was built correctly. */
	Status = XIicPs_SelfTest(&tmpPL);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XIicPs_SelfTest(&tmpPS);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the IIC serial clock rate.
	 */
	XIicPs_SetSClk(&tmpPL, IIC_SCLK_RATE);
	XIicPs_SetSClk(&tmpPS, IIC_SCLK_RATE);

	XIicPs_MasterSendPolled(&tmpPL, resolution,2, IIC_SLAVE_ADDR);
	XIicPs_MasterSendPolled(&tmpPS, resolution,2, IIC_SLAVE_ADDR);

	XIicPs_MasterSendPolled(&tmpPL, &setToZero,1, IIC_SLAVE_ADDR);
	XIicPs_MasterSendPolled(&tmpPS, &setToZero,1, IIC_SLAVE_ADDR);

	//set the gpio
	XGpio_Initialize(&uart, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&uart, 1, 0x00000000);
	XGpio_SetDataDirection(&uart, 2, 0x00000000);

	XGpio_Initialize(&uart_full, XPAR_AXI_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection(&uart_full, 1, 0xffffffff);

}

void printToUart(char* message)
{
	unsigned char count = 0;
	for(;count<strlen(message);count++)
	{
		while(XGpio_DiscreteRead(&uart_full,1) == 1){};
		XGpio_DiscreteWrite(&uart,1,message[count]);

		XGpio_DiscreteWrite(&uart,2,1);
		XGpio_DiscreteWrite(&uart,2,0);
	}
	
}

/* read temp from tmp101*/
void readTemp()
{
	float temp1;
	float temp2;
	if( XIicPs_MasterRecvPolled(&tmpPL,PLBuffer,2,IIC_SLAVE_ADDR) != XST_SUCCESS)
	{
		xil_printf("read PL error\r\n");
	}
	else
	{
		temp1 = (float)PLBuffer[0] + ((float)(PLBuffer[1] >> 5)) / 16;
		printf("PL tmp %7.4f C degrees \r\n",temp1);
		char message[LEN];
		memset(message,0,LEN);
		sprintf(message,"PL tmp %7.4f C degrees \r\n",temp1);
		printToUart(message);
	}

	if( XIicPs_MasterRecvPolled(&tmpPS,PSBuffer,2,IIC_SLAVE_ADDR) != XST_SUCCESS)
	{
		xil_printf("read PS error\r\n");
	}
	else
	{
		temp2 = (float)PSBuffer[0] + ((float)(PSBuffer[1] >> 5)) / 16;
		printf("PS tmp %7.4f C degrees \n",temp2);
		char message[LEN];
		memset(message,0,LEN);
		sprintf(message,"PS tmp %7.4f C degrees \r\n",temp2);
		printToUart(message);
	}
}

void delayLoop()
{
	int i;
	for (i = 0; i < DELEYLOOPCOUNT; i++);
}

