

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

/* MCAL */
#include "DIO_interface.h"

/*HAL*/
#include "GLCD_config.h"



				/*********** DATA TYPES FOR GLCD MODULE ***********/


typedef enum {
	GLCD_DISPLAY_OFF				= 0x3EU,
	GLCD_DISPLAY_ON					= 0x3FU,
	GLCD_SET_Y_ADDRESS_PREFIX		= 0x40U,
	GLCD_SET_X_ADDRESS_PREFIX		= 0xB8U,
	GLCD_SET_Z_ADDRESS_PREFIX		= 0xC0U
}GLCD_CommandType;

typedef enum {
	GLCD_INSTRUCTION_REG,
	GLCD_DATA_REG
}GLCD_RegisterSelectType;

typedef enum {
	GLCD_NO_PAGES,
	GLCD_PAGE_0,
	GLCD_PAGE_1,
	GLCD_BOTH_PAGES
}GLCD_PageSelectType;

typedef enum {
	GLCD_WRITE_MODE,
	GLCD_READ_MODE
}GLCD_ReadWriteType;


			   /***********	APIS PROTOTYPES FOR GLCD MODULE ***********/


void GLCD_init(void);
void GLCD_SelectPage(GLCD_PageSelectType Page);
void GLCD_SendInstruction(GLCD_CommandType Instruction);
void GLCD_SendData(u8 Data);
void GLCD_Reset(void);
void GLCD_DisplayCharacter(u8 Data);
void GLCD_DisplayString(u8* Data_Ptr);
void GLCD_DisplayInteger(s32 Data);
void GLCD_DisplayFloatingPoint(f32 Data);
void GLCD_ClearDisplay(void);
void GLCD_GoToLine(u8 Line);
void GLCD_DisplaySpecialPattern(u64 Pattern);




#endif /* GLCD_INTERFACE_H_ */