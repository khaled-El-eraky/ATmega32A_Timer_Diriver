/*
 * ATmega32A_Timer0.h
 *
 * Created: 3/7/2020 11:03:48 AM
 *  Author: Khaled Osama Eraky 
 */ 


#ifndef ATMEGA32A_TIMER0_H_
#define ATMEGA32A_TIMER0_H_


	#include "StdTypes.h"
	
	/* Enumeration for Timer0 Modes witch is divide into PWM and NON PWM  */
	typedef enum
	{
		Timer0_NormalMode=0x00,
		Timer0_CTCMode=0x08,
		Timer0_PWMPhaseCorrect=0x40,
		Timer0_PWMFast=0x48,
	}Timer0_Modes;
	
	/* Enumeration for controlling the Output compare pin OC0 */
	typedef enum
	{
		/*Disconnecting is common in the 3 tables*/
		Timer0_OC0_Disconnect=0x00,
		Timer0_NonPWM_Toggle_OC0=0x10,
		Timer0_NonPWM_Clear_OC0=0x20,
		Timer0_NonPWM_Set_OC0=0x30,
		Timer0_PWM_NonInvert=0x20,
		Timer0_PWM_Invert=0x30,
	}Timer0_OC0_ControlMode;

    /* Enumeration for determining the Timer_Freq 
	   Their values are set by default in ENUM as they 
	   are in the the first bits in the Register */
	typedef enum
	{
		Timer0_Disable,
		Timer0_FCPU,
		Timer0_FCPU_BY8,
		Timer0_FCPU_BY64,
		Timer0_FCPU_BY256,
		Timer0_FCPU_BY1024,
		Timer0_EXTCLK_Falling,
		Timer0_EXTCLK_Rising,
	}Timer0_FreqSelect;

    /* Enumeration for controlling the two interrupt in TIMSK Register 
	   Their values are set by default in ENUM as they
	   are in the the first bits in the Register */
	typedef enum
	{
		Timer0_InterruptDisable,
		Timer0_OVFInterruptEnable,
		Timer0_COMP_InterruptEnable,
		Timer0_OVF_COMP_InterruptEnable,
	}Timer0_Interrupt;
	
	/* Callback Pointer to function */
	extern void (* Timer0_OVF_CallBack)(void) ;
	extern void (* Timer0_Comp_CallBack)(void);
	
	void Timer0_Init
					(Timer0_FreqSelect T_Freq,
					 Timer0_Modes  T_Mode,
					 Timer0_OC0_ControlMode T_OC0_Mode,
					 Timer0_Interrupt      T_Interrupt
					);
					
	void Timer0_SetCompareValue (uint8_t Compare);
	
	void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq);
			
	void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0_ControlMode InvertionState);		
	
#endif /* ATMEGA32A_TIMER0_H_ */