
#ifndef GLCD_CONFIG_H_
#define GLCD_CONFIG_H_

// GLCD USED FOR (LGM12641BS1R)

						/************** GLCD Characteristics **************/

#define GLCD_MAX_LINES							8U
#define GLCD_MAX_LINE_PIXEL_WIDTH				128U
#define GLCD_MAX_PAGE_PIXEL_WIDTH				64U


						/************** GLCD Configurations **************/

#define GLCD_USE_TIMERS_FOR_DELAY				0U	   /*	0 to use delay.h 
															1 to use GPT for delay, */


						/**************	GLCD PORTS & PINS **************/

#define GLCD_CTRL_PORT							DIO_PORTB

#define GLCD_ENABLE_PIN							DIO_PIN0
#define GLCD_RW_PIN								DIO_PIN1
#define GLCD_RS_PIN								DIO_PIN2
#define GLCD_PAGE_SELECT_PIN_1					DIO_PIN4
#define GLCD_PAGE_SELECT_PIN_2					DIO_PIN5
#define GLCD_RESET_PIN							DIO_PIN6


#define GLCD_DATA_PORT							DIO_PORTA

#define GLCD_DATA_D0_PIN						DIO_PIN0
#define GLCD_DATA_D1_PIN						DIO_PIN1
#define GLCD_DATA_D2_PIN						DIO_PIN2
#define GLCD_DATA_D3_PIN						DIO_PIN3
#define GLCD_DATA_D4_PIN						DIO_PIN4
#define GLCD_DATA_D5_PIN						DIO_PIN5
#define GLCD_DATA_D6_PIN						DIO_PIN6
#define GLCD_DATA_D7_PIN						DIO_PIN7


					/************** Alphanumeric Characters (Font = 5 x 8) **************/

#define GLCD_CHAR_A						0x7C1211127CUL
#define GLCD_CHAR_B						0x364949497FUL
#define GLCD_CHAR_C						0x414141413EUL
#define GLCD_CHAR_D						0x003E41417FUL
#define GLCD_CHAR_E						0x414949497FUL
#define GLCD_CHAR_F						0x010909097FUL
#define GLCD_CHAR_G						0x7A2941413EUL
#define GLCD_CHAR_H						0x7F0808087FUL
#define GLCD_CHAR_I						0x41417F4141UL
#define GLCD_CHAR_J						0x013F414020UL
#define GLCD_CHAR_K						0x412214087FUL
#define GLCD_CHAR_L						0x404040407FUL
#define GLCD_CHAR_M						0x7F020C027FUL
#define GLCD_CHAR_N						0x7F201C027FUL
#define GLCD_CHAR_O						0x3E4141413EUL
#define GLCD_CHAR_P						0x060909097FUL
#define GLCD_CHAR_Q						0x5E2151413EUL
#define GLCD_CHAR_R						0x462919097FUL
#define GLCD_CHAR_S						0x3249494926UL
#define GLCD_CHAR_T						0x01017F0101UL
#define GLCD_CHAR_U						0x3F4040403FUL
#define GLCD_CHAR_V						0x1F2040201FUL
#define GLCD_CHAR_W						0x3F4020403FUL
#define GLCD_CHAR_X						0x6314081463UL
#define GLCD_CHAR_Y						0x030C700C03UL
#define GLCD_CHAR_Z						0x4345495161UL


#define GLCD_CHAR_1						0x00407F4200UL
#define GLCD_CHAR_2						0x4649516142UL
#define GLCD_CHAR_3						0x3649494941UL
#define GLCD_CHAR_4						0x107F121418UL
#define GLCD_CHAR_5						0x314949494FUL
#define GLCD_CHAR_6						0x3149494A7CUL
#define GLCD_CHAR_7						0x0709710103UL
#define GLCD_CHAR_8						0x3649494936UL
#define GLCD_CHAR_9						0x1E29494906UL
#define GLCD_CHAR_0						0x3E4549513EUL


					/************** Symbolic Characters (Font = 5 x 8) **************/

#define GLCD_CHAR_PERCENT				0xC3CE1873C3UL
#define GLCD_CHAR_EQUAL					0x2424242424UL
#define GLCD_CHAR_SPACE					0x0000000000UL
#define GLCD_CHAR_POINT					0x0070707000UL
#define GLCD_CHAR_NEGATIVE				0x1818181818UL



#endif /* GLCD_CONFIG_H_ */