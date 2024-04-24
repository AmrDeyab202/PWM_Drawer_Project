
#include "PWM_Drawer_interface.h"




void PWMDrawer_Init(void) {

	GLCD_init();
	GLCD_ClearDisplay();
	PWM_Init(&PWM_Setup[0]);		// Use Timer 0 to generate PWM on OC0=PB3
	ICU_Init(&ICU_SetUp);			// Timer 1 is used for Input Capture to get the PWM Signal
}

void PWM_MeasureSignal(PWM_Signal_SetUp* PWM_ptr) {
	ICU_DutyCycleType Duty_Cycle_EXM = {0, 0};
	ICU_GetDutyCycle(ICU_TIMER_1, 8U, &Duty_Cycle_EXM);
	PWM_ptr->Period_Time_ms = Duty_Cycle_EXM.Period_Time;
	PWM_ptr->High_Time_ms = Duty_Cycle_EXM.High_Time;
	
	PWM_ptr->Freq_kHz = (1.0 / (PWM_ptr->Period_Time_ms));
	PWM_ptr->Duty_Percent = (u8)((PWM_ptr->High_Time_ms) * 100.0 / (PWM_ptr->Period_Time_ms));
}

void PWM_DrawSignal(PWM_Signal_SetUp* Signal_Data_Ptr, f32 Scale_ms) {
	
	//Clear anything on the display at first
	GLCD_ClearDisplay(); 
	
	
	// Display  Frequency on Line 0  
	
	GLCD_GoToLine(0);
	char FreqKHz[15] = "Freq=\0";
	GLCD_DisplayString(FreqKHz);
	GLCD_DisplayFloatingPoint(Signal_Data_Ptr->Freq_kHz);
	char KHz[5] = " kHz\0";
	GLCD_DisplayString(KHz);

	// Display Duty cycle percentage on line 2 
	
	GLCD_GoToLine(2);
	char Duty_Val[15] = "Duty=\0";
	GLCD_DisplayString(Duty_Val);
	GLCD_DisplayInteger(Signal_Data_Ptr->Duty_Percent);
	char Percent[5] = " %\0";
	GLCD_DisplayString(Percent);


	/* Display Time in ms on Line 4 */
	
	GLCD_GoToLine(4);
	char Time_in_ms[15] = "Time=\0";
	GLCD_DisplayString(Time_in_ms);
	GLCD_DisplayFloatingPoint(Signal_Data_Ptr->Period_Time_ms);
	char milisecs[5] = "ms\0";
	GLCD_DisplayString(milisecs);
	
	
	/* Display PWM  Signal from Line 6 */
	
	GLCD_GoToLine(6);
	u8 pixel_width_count = 0;
	u8 i;
	while (pixel_width_count < GLCD_MAX_LINE_PIXEL_WIDTH - 8U) {
		GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_RISING_EDGE); pixel_width_count += 5;
		for (i = 0; i < ((u8)(Signal_Data_Ptr->High_Time_ms / Scale_ms)); i++) {
			GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_HIGH_LINE); pixel_width_count += 5;
		}
		GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_FALLING_EDGE); pixel_width_count += 5;
		for (i = 0; i < ((u8)(Signal_Data_Ptr->Low_Time_ms / Scale_ms)); i++) {
			GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_LOW_LINE); pixel_width_count += 5;
		}
	}
	
	/* Display Arrow for Time Period */
	
	GLCD_GoToLine(5);
	GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_LEFT_ARROW_HEAD);
	for (i = 0; i < ((u8)(Signal_Data_Ptr->High_Time_ms / Scale_ms)); i++) {
		GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
	}
	GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
	for (i = 0; i < ((u8)(Signal_Data_Ptr->Low_Time_ms / Scale_ms)); i++) {
		GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
	}
	GLCD_DisplaySpecialPattern(PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD);

}
