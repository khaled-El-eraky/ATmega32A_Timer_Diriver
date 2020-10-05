/*
 * ATmega32A_Timer0.c
 *
 * Created: 10/5/2020 10:34:26 PM
 *  Author: Khaled Osama Eraky
 */ 


#include "DIO.h"
#include "ATmega32A_Timer0.h"

int main(void)
{
	
	//DIO_pinConfigure(DIOB,PIN3,OUTPUT);
	//Timer0_Init(Timer0_FCPU_BY256,Timer0_CTCMode,Timer0_NonPWM_Toggle_OC0,Timer0_InterruptDisable);
	//Timer0_CTC_SquareGenerate(1500.0 , (F_CPU/256.0));
	
	
	
	
	DIO_pinConfigure(DIOB,PIN3,OUTPUT);
	Timer0_Init(Timer0_FCPU_BY256,Timer0_PWMPhaseCorrect,Timer0_PWM_NonInvert,Timer0_InterruptDisable);
	Timer0_PWMSetDutyCycle(70,Timer0_PWM_NonInvert);
	
	
    while(1)
    {
      
    }
}