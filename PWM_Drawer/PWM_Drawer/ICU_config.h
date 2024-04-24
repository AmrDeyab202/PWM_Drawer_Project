
#ifndef ICU_CONFIG_H_
#define ICU_CONFIG_H_

#include "ICU_interface.h"

const ICU_Config ICU_SetUp =
{
	ICU_TIMER_1,
	ICU_PRESCALE_8,
	ICU_TRIGGER_FALLING_EDGE,
	ICU_INTERRUPT_DISABLED
};



#endif /* ICU_CONFIG_H_ */