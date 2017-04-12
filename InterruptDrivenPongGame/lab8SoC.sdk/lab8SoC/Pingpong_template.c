/*
 * Pingpong_template.c
 *
 *  Created on: 3/27/2017
 *  Author: wangyuhao
 */

#include "xparameters.h"
#include "xgpio.h"
#include "led_ip.h"
#include "xtmrctr.h"
#include "xscugic.h"
#include "xil_exception.h"

#include "Pingpong_template.h"

/* button interrupt handler*/
void BTN_Intr_Handler(void *InstancePtr)
{
	// Disable GPIO interrupts
	XGpio_InterruptDisable(&push, BTN_INT);
	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&push) & BTN_INT) !=
			BTN_INT) {
			return;
		}
	psb_check = XGpio_DiscreteRead(&push, 1);
	xil_printf("button value = %d\r\n",psb_check);
	setStatus();
    (void)XGpio_InterruptClear(&push, BTN_INT);
    // Enable GPIO interrupts
    XGpio_InterruptEnable(&push, BTN_INT);
}

/* timer interrupt handler*/
void TMR_Intr_Handler(void *data)
{
	if (XTmrCtr_IsExpired(&TMRInst,0)){

		setLED();
		XTmrCtr_Reset(&TMRInst,0);
		XTmrCtr_Start(&TMRInst,0);
	}
}
int main (void)
{
	//initialize variables, timers, ports
	initialize();

	while (1)
	{
		dip_check = XGpio_DiscreteRead(&dip, 1);
		if (dip_check != dip_check_prev)
		{
			setTimer();
		}
	}

}
void setStatus()
{
	switch(psb_check)
	{
		case RESETBUTTON:
			GameOver = STOP;
			scoreright = 0;
			scoreleft = 0;
			xil_printf("Score Left = %d   Score Right = %d\r\n", scoreright, scoreleft);
			break;
		case STARTBUTTON:
			GameOver = START;
			if(StartDirection == LEFT)
			{
				StartDirection = RIGHT;
				LEDDirection = RIGHT;
				LedState = RIGHT_INIT_STATE;
			}
			else
			{
				StartDirection = LEFT;
				LEDDirection = LEFT;
				LedState = LEFT_INIT_STATE;
			}
			xil_printf("Score Left = %d   Score Right = %d\r\n", scoreright, scoreleft);
			break;
		case LEFTPADDLE:
			if(LEDDirection == RIGHT)
			{
				if(LedState == RIGHT_END)
				{
					LEDDirection = LEFT;
				}
				else
				{
					GameOver = STOP;
					scoreright += 1;
				}
			}
			break;
		case RIGHTPADDLE:
			if(LEDDirection == LEFT)
			{
				if(LedState == LEFT_END)
				{
					LEDDirection = RIGHT;
				}
				else
				{
					GameOver = STOP;
					scoreleft += 1;
				}
			}
			break;
		default:
			break;
	}
}
void setTimer()
{
	xil_printf("DIP Switch Status %x, %x\r\n", dip_check_prev, dip_check);
	dip_check_prev = dip_check;
	// load timer with the new switch settings
	XTmrCtr_SetResetValue(&TMRInst, 0, TRM_OVERFLOW - TRM_LOAD / ( 1 + dip_check));
}
void setLED()
{
	if(GameOver == STOP)
	{
		LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, 0);
	}
	else
	{
		if(LEDDirection == RIGHT)
		{
			LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, LED_PATTERNS[LedState]);
			if(LedState == RIGHT_END)
			{
				GameOver = STOP;
				scoreleft += 1;
			}
			else
			{
				LedState += 1;
			}
		}
		else
		{
			LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, LED_PATTERNS[LedState]);
			if(LedState == LEFT_END)
			{
				GameOver = STOP;
				scoreright += 1;
			}
			else
			{
				LedState -= 1;
			}
		}
	}
}
int initialize()
{
	int status;
	xil_printf("-- Start of the Ping Pong Program --\r\n");

	//set init status
	GameOver=START;
	scoreright = 0; scoreleft = 0;
	xil_printf("Score Left = %d   Score Right = %d\r\n", scoreright, scoreleft);
	StartDirection=LEFT;
	LEDDirection = LEFT;

	//init gpio
	XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID);
	XGpio_SetDataDirection(&dip, 1, 0xffffffff);

	XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID);
	XGpio_SetDataDirection(&push, 1, 0xffffffff);

	//init timer
	status = XTmrCtr_Initialize(&TMRInst, XPAR_TMRCTR_0_DEVICE_ID);
	if(status != XST_SUCCESS) return XST_FAILURE;
	XTmrCtr_SetHandler(&TMRInst, TMR_Intr_Handler, &TMRInst);
	dip_check = XGpio_DiscreteRead(&dip, 1);
	XTmrCtr_SetResetValue(&TMRInst, 0, TRM_OVERFLOW - TRM_LOAD / ( 1 + dip_check));
	XTmrCtr_SetOptions(&TMRInst, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);


	// Initialize interrupt controller
	status = IntcInitFunction(XPAR_PS7_SCUGIC_0_DEVICE_ID, &TMRInst, &push);
	if(status != XST_SUCCESS) return XST_FAILURE;

	XTmrCtr_Start(&TMRInst, 0);


}

int InterruptSystemSetup(XScuGic *XScuGicInstancePtr)
{
	// Enable interrupt
	XGpio_InterruptEnable(&push, XPAR_BUTTONS_DEVICE_ID);
	XGpio_InterruptGlobalEnable(&push);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 	 	 	 	 	 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
			 	 	 	 	 	 XScuGicInstancePtr);
	Xil_ExceptionEnable();


	return XST_SUCCESS;

}

/* init interrupts config*/
int IntcInitFunction(u16 DeviceId, XTmrCtr *TmrInstancePtr, XGpio *GpioInstancePtr)
{
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Call to interrupt setup
	status = InterruptSystemSetup(&INTCInst);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst,
			XPAR_FABRIC_BUTTONS_IP2INTC_IRPT_INTR,
					  	  	 (Xil_ExceptionHandler)BTN_Intr_Handler,
					  	  	 (void *)GpioInstancePtr);
	if(status != XST_SUCCESS) return XST_FAILURE;


	// Connect timer interrupt to handler
	status = XScuGic_Connect(&INTCInst,
			XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR,
							 (Xil_ExceptionHandler)TMR_Intr_Handler,
							 (void *)TmrInstancePtr);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Enable GPIO interrupts interrupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(&INTCInst, XPAR_FABRIC_BUTTONS_IP2INTC_IRPT_INTR);

	XScuGic_Enable(&INTCInst, XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR);

	return XST_SUCCESS;
}
