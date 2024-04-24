
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GLCD_interface.h"
#include "GLCD_private.h"

#include <util/delay.h>



u8 Current_X_Address = 0;
u8 Current_Y_Address = 0;
u8 Current_Page = 0;

void GLCD_init(void) 
{
	#if GLCD_USE_TIMERS_FOR_DELAY == 1
		// GPT_Init(gaStrGPT_Config);
	#endif
	
	/* Initialize Port Directions */
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_RESET_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, DIO_PIN_OUTPUT);
	DIO_setPinDirection(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, DIO_PIN_OUTPUT);

	DIO_setPortDirection(GLCD_DATA_PORT, DIO_PIN_OUTPUT);
	/* Keep reset pin inactive (high) */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, DIO_PIN_HIGH);
	/* Initialization of GLCD Sequence */
	GLCD_SelectPage(GLCD_BOTH_PAGES);
	GLCD_SendInstruction(GLCD_DISPLAY_OFF);
	GLCD_SendInstruction(GLCD_SET_X_ADDRESS_PREFIX + 0);  /* line=0 */
	Current_X_Address = 0;
	GLCD_SendInstruction(GLCD_SET_Y_ADDRESS_PREFIX + 0);  /* column=0 */
	Current_Y_Address = 0;
	GLCD_SendInstruction(GLCD_SET_Z_ADDRESS_PREFIX + 0);  /* start_line=0 */
	GLCD_SendInstruction(GLCD_DISPLAY_ON);
	GLCD_SelectPage(GLCD_PAGE_0);
	Current_Page = 0;
}


void GLCD_SelectPage(GLCD_PageSelectType Page) 
{
	switch (Page) {
		case GLCD_NO_PAGES:
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, DIO_PIN_LOW);
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, DIO_PIN_LOW);
			break;
		case GLCD_PAGE_0:
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, DIO_PIN_HIGH);
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, DIO_PIN_LOW);
			break;
		case GLCD_PAGE_1:
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, DIO_PIN_LOW);
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, DIO_PIN_HIGH);
			break;
		case GLCD_BOTH_PAGES:
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, DIO_PIN_HIGH);
			DIO_setPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, DIO_PIN_HIGH);
			break;
		default: break;
	}
}


void GLCD_SendInstruction(GLCD_CommandType Instruction) 
{
	/* Select Instruction Register */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, GLCD_INSTRUCTION_REG);
	/* Select Write Operation */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, GLCD_WRITE_MODE);
	/* Send Command on Data Pins */
	DIO_setPortValue(GLCD_DATA_PORT, Instruction);
	/* Enable Pulse of min. width 1us */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, DIO_PIN_HIGH);
	
	#if GLCD_USE_TIMERS_FOR_DELAY == 1
		
	#else
		_delay_us(5);
	#endif
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, DIO_PIN_LOW);
}

void GLCD_SendData(u8 Data) {
	
	/* Select Data Register */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, GLCD_DATA_REG);
	/* Select Write Operation */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, GLCD_WRITE_MODE);
	/* Send Command on Data Pins */
	DIO_setPortValue(GLCD_DATA_PORT, Data);
	/* Enable Pulse of min. width 1us */
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, DIO_PIN_HIGH);
	#if GLCD_USE_TIMERS_FOR_DELAY == 1
	 
	#else
		_delay_us(5);
	#endif
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, DIO_PIN_LOW);
}

void GLCD_Reset(void) 
{
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, DIO_PIN_LOW);
	#if GLCD_USE_TIMERS_FOR_DELAY == 1
		//GPT_Delay_us(&gaStrGPT_Config[0], 10);
	#else
	_delay_us(10);
	#endif
	DIO_setPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, DIO_PIN_HIGH);
}

void GLCD_DisplaySpecialPattern(u64 Pattern) {
	for(u8 i = 0; i < 5; i++) 
	{
		GLCD_SendInstruction(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		GLCD_SendInstruction(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
		GLCD_SendData((Pattern>>(i*8U)) & 0x00000000FFUL);
		Current_Y_Address++;
		
		if (Current_Y_Address >= GLCD_MAX_PAGE_PIXEL_WIDTH && Current_Page == 0) 
		{
			GLCD_SelectPage(GLCD_PAGE_1);
			Current_Y_Address = 0;
		}
	}
}

void GLCD_DisplayCharacter(u8 Data) 
{
	if ((Current_Page == 0) | (Current_Y_Address < GLCD_MAX_PAGE_PIXEL_WIDTH - 7U)) {
		/* Enough space to write character */
		switch (Data) {
			case 'A': case 'a': GLCD_DisplaySpecialPattern(GLCD_CHAR_A); break;
			case 'B': case 'b': GLCD_DisplaySpecialPattern(GLCD_CHAR_B); break;
			case 'C': case 'c': GLCD_DisplaySpecialPattern(GLCD_CHAR_C); break;
			case 'D': case 'd': GLCD_DisplaySpecialPattern(GLCD_CHAR_D); break;
			case 'E': case 'e': GLCD_DisplaySpecialPattern(GLCD_CHAR_E); break;
			case 'F': case 'f': GLCD_DisplaySpecialPattern(GLCD_CHAR_F); break;
			case 'G': case 'g': GLCD_DisplaySpecialPattern(GLCD_CHAR_G); break;
			case 'H': case 'h': GLCD_DisplaySpecialPattern(GLCD_CHAR_H); break;
			case 'I': case 'i': GLCD_DisplaySpecialPattern(GLCD_CHAR_I); break;
			case 'J': case 'j': GLCD_DisplaySpecialPattern(GLCD_CHAR_J); break;
			case 'K': case 'k': GLCD_DisplaySpecialPattern(GLCD_CHAR_K); break;
			case 'L': case 'l': GLCD_DisplaySpecialPattern(GLCD_CHAR_L); break;
			case 'M': case 'm': GLCD_DisplaySpecialPattern(GLCD_CHAR_M); break;
			case 'N': case 'n': GLCD_DisplaySpecialPattern(GLCD_CHAR_N); break;
			case 'O': case 'o': GLCD_DisplaySpecialPattern(GLCD_CHAR_O); break;
			case 'P': case 'p': GLCD_DisplaySpecialPattern(GLCD_CHAR_P); break;
			case 'Q': case 'q': GLCD_DisplaySpecialPattern(GLCD_CHAR_Q); break;
			case 'R': case 'r': GLCD_DisplaySpecialPattern(GLCD_CHAR_R); break;
			case 'S': case 's': GLCD_DisplaySpecialPattern(GLCD_CHAR_S); break;
			case 'T': case 't': GLCD_DisplaySpecialPattern(GLCD_CHAR_T); break;
			case 'U': case 'u': GLCD_DisplaySpecialPattern(GLCD_CHAR_U); break;
			case 'V': case 'v': GLCD_DisplaySpecialPattern(GLCD_CHAR_V); break;
			case 'W': case 'w': GLCD_DisplaySpecialPattern(GLCD_CHAR_W); break;
			case 'X': case 'x': GLCD_DisplaySpecialPattern(GLCD_CHAR_X); break;
			case 'Y': case 'y': GLCD_DisplaySpecialPattern(GLCD_CHAR_Y); break;
			case 'Z': case 'z': GLCD_DisplaySpecialPattern(GLCD_CHAR_Z); break;
			
			case '%': GLCD_DisplaySpecialPattern(GLCD_CHAR_PERCENT); break;
			case '=': GLCD_DisplaySpecialPattern(GLCD_CHAR_EQUAL); break;
			case '.': GLCD_DisplaySpecialPattern(GLCD_CHAR_POINT); break;
			case ' ': GLCD_DisplaySpecialPattern(GLCD_CHAR_SPACE); break;
			case '-': GLCD_DisplaySpecialPattern(GLCD_CHAR_NEGATIVE); break;
			
			case '0': GLCD_DisplaySpecialPattern(GLCD_CHAR_0); break;
			case '1': GLCD_DisplaySpecialPattern(GLCD_CHAR_1); break;
			case '2': GLCD_DisplaySpecialPattern(GLCD_CHAR_2); break;
			case '3': GLCD_DisplaySpecialPattern(GLCD_CHAR_3); break;
			case '4': GLCD_DisplaySpecialPattern(GLCD_CHAR_4); break;
			case '5': GLCD_DisplaySpecialPattern(GLCD_CHAR_5); break;
			case '6': GLCD_DisplaySpecialPattern(GLCD_CHAR_6); break;
			case '7': GLCD_DisplaySpecialPattern(GLCD_CHAR_7); break;
			case '8': GLCD_DisplaySpecialPattern(GLCD_CHAR_8); break;
			case '9': GLCD_DisplaySpecialPattern(GLCD_CHAR_9); break;
			default: break;
		}
		GLCD_SendInstruction(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		GLCD_SendInstruction(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
		GLCD_SendData(0);
		Current_Y_Address++;
		if (Current_Y_Address >= GLCD_MAX_PAGE_PIXEL_WIDTH && Current_Page == 0) {
			GLCD_SelectPage(GLCD_PAGE_1);
			Current_Y_Address = 0;
		}
	}
}

void GLCD_DisplayString(u8* Data_Ptr) 
{
	while (*Data_Ptr != '\0') {
		GLCD_DisplayCharacter(*Data_Ptr);
		Data_Ptr++;
	}
}

void GLCD_DisplayInteger(s32 Data)
{
	if (Data < 0) {
		GLCD_DisplayCharacter('-');
		Data = -1 * Data;
	}
	u8 u8Local_Digit = 0U;
	char str_reversed[5] = "";
	char* str_ptr = str_reversed;
	do {
		u8Local_Digit = Data%10;
		*str_ptr = (char)(48 + u8Local_Digit); /* 48 is the ASCII code of '0' */
		Data = Data/10;
		str_ptr++;
	} while (Data > 0);
	do {
		str_ptr--;
		GLCD_DisplayCharacter(*str_ptr);
	} while (str_ptr != str_reversed);
}

void GLCD_DisplayFloatingPoint(f32 Data)
{
	/* Will display only 3 Decimal Places */
	u16 IntegerPart = (u16)Data;
	GLCD_DisplayInteger(IntegerPart);
	GLCD_DisplayCharacter('.');
	f32 DecimalPart = (Data - IntegerPart);
	u8 Digit = 0;
	for (u8 i = 0; i < 3; i++) {
		Digit = (u8)(DecimalPart * 10.0);
		GLCD_DisplayCharacter((char)(48+Digit));
		DecimalPart = ((DecimalPart*10.0) - Digit);
	}
}

void GLCD_GoToLine(u8 Line) {
	if (Line < GLCD_MAX_LINES) {
		GLCD_SelectPage(GLCD_PAGE_0);
		Current_X_Address = Line;
		GLCD_SendInstruction(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		Current_Y_Address = 0;
		GLCD_SendInstruction(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
	}
}

void GLCD_ClearDisplay(void) {
	for (u8 Line = 0; Line < GLCD_MAX_LINES; Line++) {
		GLCD_GoToLine(Line);
		GLCD_SelectPage(GLCD_BOTH_PAGES);
		for (u8 i = 0; i < GLCD_MAX_PAGE_PIXEL_WIDTH; i++) {
			GLCD_SendInstruction(GLCD_SET_Y_ADDRESS_PREFIX + i);
			GLCD_SendData(0);
		}
	}
	GLCD_Reset();
	GLCD_SelectPage(GLCD_PAGE_0);
	Current_Page = 0;
	GLCD_GoToLine(0);
}
