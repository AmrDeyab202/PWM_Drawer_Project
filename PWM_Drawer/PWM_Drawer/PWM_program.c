
/* MCAL */
#include "PWM_interface.h"

void PWM_Init(const PWM_Config* Config_Ptr) {
	
	// PWM GENERATED FROM TMR0

	/* Make PB3=OC0 as output */
	SET_BIT(*PORTB_DIR_REG, 3U);
	
	/* Clear TCCR0 Register Configurations */
	*TIMER0_CTRL_REG = 0x00U;
	
	/* Set PWM Mode */
	*TIMER0_CTRL_REG |= (1U<<6U) | ((Config_Ptr->Mode)<<PWM_TIMER_0_FAST_BIT);
	
	/* Set PWM Output State (inverting or not) */
	*TIMER0_CTRL_REG |= (1U<<5U) | ((Config_Ptr->State)<<PWM_TIMER_0_INVERTING_BIT);
	
	/* Select Clock Source and Prescaler */
	switch (Config_Ptr->Clk_Prescale) {
		case PWM_NO_CLK_SRC:
		case PWM_PRESCALE_1:
		*TIMER0_CTRL_REG |= (Config_Ptr->Clk_Prescale); break;
		case PWM_PRESCALE_8:
		*TIMER0_CTRL_REG |= (Config_Ptr->Clk_Prescale); break;
		case PWM_PRESCALE_64:
		*TIMER0_CTRL_REG |= ((Config_Ptr->Clk_Prescale)); break;
		case PWM_PRESCALE_256:
		*TIMER0_CTRL_REG |= ((Config_Ptr->Clk_Prescale)); break;
		case PWM_PRESCALE_1024:
		*TIMER0_CTRL_REG |= ((Config_Ptr->Clk_Prescale)); break;
		case PWM_EXT_CLK_FALLING_EDGE:
		case PWM_EXT_CLK_RISING_EDGE:
		*TIMER0_CTRL_REG |= ((Config_Ptr->Clk_Prescale)-2U); break;
		default: break;
	}
	
	
	/* Set Duty Value in OCR0 Register */
	*TIMER0_CMP_REG = 0x00U;
	switch (Config_Ptr->State) {
		case PWM_NON_INVERTED: *TIMER0_CMP_REG = (u8)((Config_Ptr->Duty_Percent) * PWM_TIMER_0_RES / 100.0); break;
		case PWM_INVERTED: *TIMER0_CMP_REG = (u8)((100.0 - Config_Ptr->Duty_Percent) * PWM_TIMER_0_RES / 100.0); break;
		default: break;
	}
	
	/* Clear TCNT0 Register Configurations */
	*TIMER0_CNTR_REG = 0x00U;
	
	
}



void PWM_SetDuty(PWM_OutputState State, u16 Duty_Percent) {

	switch (State) {
		case PWM_NON_INVERTED: *TIMER0_CMP_REG = (u8)(Duty_Percent * PWM_TIMER_0_RES / 100.0); break;
		case PWM_INVERTED: *TIMER0_CMP_REG = (u8)((100.0 - Duty_Percent) * PWM_TIMER_0_RES / 100.0); break;
		default: break;
	}

}