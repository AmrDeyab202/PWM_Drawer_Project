
#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

/* UTILITIES */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "REGISTERS.h"



#define PWM_TIMER_0_FAST_BIT			3
#define PWM_TIMER_0_INVERTING_BIT		4

#define PWM_TIMER_1_FAST_BIT			3
#define PWM_TIMER_1_A_INVERTING_BIT		6
#define PWM_TIMER_1_B_INVERTING_BIT		4

#define PWM_TIMER_2_FAST_BIT			3
#define PWM_TIMER_2_INVERTING_BIT		4

					/*********** TIMERS RESOLUTIONS FOR PWM MODULE ***********/
#define PWM_TIMER_0_RES				255
#define PWM_TIMER_1_RES				65535
#define PWM_TIMER_2_RES				255



						/*********** DATA TYPES FOR PWM MODULE ***********/
						
// Channels that could be used:

typedef enum {
	PWM_TIMER_0_CHANNEL,
	PWM_TIMER_1_CHANNEL_A,
	PWM_TIMER_1_CHANNEL_B,
	PWM_TIMER_2_CHANNEL
}PWM_ChannelType;



// PWM Modes
typedef enum {
	PWM_PHASE_CORRECT,
	PWM_FAST
}PWM_ModeType;


//Prescale types
typedef enum {
	PWM_NO_CLK_SRC,
	PWM_PRESCALE_1,
	PWM_PRESCALE_8,
	PWM_PRESCALE_64,
	PWM_PRESCALE_256,
	PWM_PRESCALE_1024,
	PWM_EXT_CLK_FALLING_EDGE,
	PWM_EXT_CLK_RISING_EDGE
}PWM_ClockPrescaleType;

typedef enum {
	PWM_NON_INVERTED,
	PWM_INVERTED
}PWM_OutputState;




typedef struct {
	PWM_ChannelType Timer_Chnl;
	PWM_ModeType Mode;
	PWM_ClockPrescaleType Clk_Prescale;
	PWM_OutputState State;
	u16 Prescale_Value;
	u8 Duty_Percent;
}PWM_Config;


					/***********	APIS PROTOTYPES FOR PWM MODULE ***********/

void PWM_Init(const PWM_Config* Config_Ptr);
void PWM_SetDuty(PWM_OutputState State, u16 Duty_Percent);



extern const PWM_Config PWM_Setup[1];



#endif /* PWM_INTERFACE_H_ */