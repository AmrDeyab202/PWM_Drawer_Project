
#ifndef PWM_DRAWER_INTERFACE_H_
#define PWM_DRAWER_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "REGISTERS.h"
#include "GLCD_interface.h"
#include "PWM_interface.h"
#include "ICU_interface.h"
#include "PWM_Drawer_interface.h"

           
		    /************** Signal Wave Patterns (Font = 5 x 8) **************/

#define PWM_DRAWER_GLCD_HIGH_LINE					(0x0202020202UL)
#define PWM_DRAWER_GLCD_LOW_LINE					(0x4040404040UL)
#define PWM_DRAWER_GLCD_RISING_EDGE					(0x02027E4040UL)
#define PWM_DRAWER_GLCD_FALLING_EDGE				(0x40407E0202UL)
#define PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD			(0x003E081C2AUL)
#define PWM_DRAWER_GLCD_LEFT_ARROW_HEAD				(0x2A1C083E00UL)
#define PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY			(0x0808080808UL)





typedef struct {
	u8 Duty_Percent;
	f32 High_Time_ms;
	f32 Low_Time_ms;
	f32 Period_Time_ms;
	f32 Freq_kHz;
}PWM_Signal_SetUp;


                  /***********	APIS PROTOTYPES FOR PWM_Drawer MODULE ***********/

void PWMDrawer_Init(void);
void PWM_MeasureSignal(PWM_Signal_SetUp* Signal_Data_Ptr);
void PWM_DrawSignal(PWM_Signal_SetUp* Signal_Data_Ptr, f32 Scale_ms);





#endif /* PWM_DRAWER_INTERFACE_H_ */