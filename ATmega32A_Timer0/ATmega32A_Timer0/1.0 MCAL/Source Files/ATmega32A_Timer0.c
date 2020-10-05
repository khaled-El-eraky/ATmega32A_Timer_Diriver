/*
 * ATmega32A_Timer0.c
 *
 * Created: 3/7/2020 11:03:58 AM
 *  Author: Khaled Osaa Eraky
 */ 


#include "ATmega32A_Timer0.h"
#include "Microcontroller_config.h"

#define  TCCR0		((reg8 *) (0x33 + IO_OFFSET))
#define  TCNT0		((reg8 *) (0x32 + IO_OFFSET))
#define  OCR0		((reg8 *) (0x3C + IO_OFFSET))

#define TIMER0_OVF_VECT		_VECTOR(11)
#define TIMER0_COMP_VECT	_VECTOR(10)

#define NULL	((void *) 0x00)

void (* Timer0_OVF_CallBack)(void) = NULL;
void (* Timer0_Comp_CallBack)(void)= NULL;

ISR(TIMER0_COMP_VECT)
{
	if (Timer0_Comp_CallBack != NULL)
	{
		Timer0_Comp_CallBack();
	}
}
ISR(TIMER0_OVF_VECT)
{
		if (Timer0_OVF_CallBack != NULL)
		{
			Timer0_OVF_CallBack();
		}
}

void Timer0_Init(Timer0_FreqSelect T_Freq,Timer0_Modes  T_Mode,Timer0_OC0_ControlMode T_OC0_Mode,Timer0_Interrupt  T_Interrupt)
{
		TCCR0->allRegister = T_Freq | T_Mode | T_OC0_Mode;
		/* Clear the two bits of Interrupt */
		TIMSK->allRegister &= 0xFC;
		TIMSK->allRegister |= T_Interrupt;
}


void Timer0_SetCompareValue (uint8_t Compare)
{
	OCR0->allRegister = Compare;
}


void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq)
{
	/*+0.5 To Equation for Rounding as if it is less than 0.5 it will be 
	  cast and neglected and if more than 0.5 it will be rounded to ceil*/
		OCR0->allRegister =	(uint8_t)((Timer0_Freq/(2.0*SignalFreq)) - 1.0 + 0.5);		
}


void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0_ControlMode InvertionState)
{
	switch (InvertionState)
	{
		case Timer0_PWM_NonInvert:
			 OCR0->allRegister = ((DutyCycle/100.0) * 255)+0.5;
		break;
		case Timer0_PWM_Invert:
		     /* 100- as invert start at LOW and OCR value will determine the LOW percentage*/ 
			 OCR0->allRegister = (((100-DutyCycle)/100.0) * 255)+0.5;
		break;
		default:
		break;
	}
}
