
/* APP */
#include "PWM_Drawer_interface.h"

#include <util/delay.h>

const PWM_Config PWM_Setup[1] =
{
	{
		PWM_TIMER_0_CHANNEL,		// PWM_ChannelType
		PWM_FAST,					// PWM MODE
		PWM_PRESCALE_256,				// PWM_ClockPrescaleType
		PWM_INVERTED,				// PWM_OutputState
		256U,						// Prescale_Value
		60U						    // Duty Cycle Percentage
	}
};

int main(void)
{
	PWMDrawer_Init();
	PWM_Signal_SetUp Signal_Data = {0, 0, 0, 0, 0};
	f32 Scale_ms = 0.25;
	
	while(1)   
	{
		
		PWM_MeasureSignal(&Signal_Data);
		Scale_ms=((Signal_Data.Period_Time_ms) / 5);
		PWM_DrawSignal(&Signal_Data, Scale_ms);
		_delay_ms(200);
	}
}

