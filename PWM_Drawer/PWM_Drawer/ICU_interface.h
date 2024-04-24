
	#ifndef ICU_INTERFACE_H_
	#define ICU_INTERFACE_H_

	#ifndef ICU_H_
	#define ICU_H_

	/* UTILITIES */
	#include "STD_TYPES.h"
	#include "BIT_MATH.h"
	#include "REGISTERS.h"


	#define ICU_TIMER1_RESOLUTION					65536
	#define ICU_TIMER1_EDGE_SELECT_BIT				6
	#define ICU_TIMER1_INT_BIT						5
	#define ICU_TIMER1_OVF_FLAG_BIT					2


						/*********** DATA TYPES FOR ICU MODULE ***********/

	typedef enum {
		ICU_TIMER_1			//ICP1 Pin on PD6
	}ICU_TimerChannelNo;

	typedef enum {
		ICU_NO_CLK_SRC,
		ICU_PRESCALE_1,
		ICU_PRESCALE_8,
		ICU_PRESCALE_64,
		ICU_PRESCALE_256,
		ICU_PRESCALE_1024,
		ICU_EXT_CLK_FALLING_EDGE,
		ICU_EXT_CLK_RISING_EDGE
	}ICU_ClockPrescale;

	typedef enum {
		ICU_TRIGGER_FALLING_EDGE,
		ICU_TRIGGER_RISING_EDGE
	}ICU_TriggerEdgeType;

	typedef enum {
		ICU_INTERRUPT_DISABLED,
		ICU_INTERRUPT_ENABLED
	}ICU_InterruptState;

	typedef enum {
		ICU_RUNNING,
		ICU_EVENT_CATURED
	}ICU_StatusType;

	typedef struct {
		f32 High_Time;
		f32 Period_Time;
	}ICU_DutyCycleType;

	typedef struct {
		ICU_TimerChannelNo Timer_Chnl;
		ICU_ClockPrescale Clk_Prescale;
		ICU_TriggerEdgeType Trigger_Edge;
		ICU_InterruptState Int_State;
	}ICU_Config;

						/***********	APIS PROTOTYPES FOR ICU MODULE ***********/
					
	void ICU_Init(const ICU_Config* Config_Ptr);
	void ICU_SetTriggerEdge(ICU_TimerChannelNo Timer_Chnl, ICU_TriggerEdgeType Edge);
	void ICU_ClearTimerValue(ICU_TimerChannelNo Timer_Chnl);
	u16 ICU_GetICUValue(ICU_TimerChannelNo Timer_Chnl);
	ICU_StatusType ICU_GetStatus(ICU_TimerChannelNo Timer_Chnl);
	void ICU_GetDutyCycle(ICU_TimerChannelNo Timer_Chnl, u16 Prescale_Value, ICU_DutyCycleType* Duty_Ptr);




	extern const ICU_Config ICU_SetUp;


	#endif /* ICU_H_ */
	#endif /* ICU_INTERFACE_H_ */