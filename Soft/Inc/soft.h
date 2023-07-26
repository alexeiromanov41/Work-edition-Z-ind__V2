#ifndef SOFT_H
#define SOFT_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "string.h"
#include "25lc040a.h"
#include <stdio.h>

/*defines*/
#define TIM_X_MAX_T 84000
#define TIM_X_MIN_T 22000

#define TIM_Y_MAX_T 84000
#define TIM_Y_MIN_T 22000

#define TIM_Z_MAX_T 84000
#define TIM_Z_MIN_T 22000

#define ENC_MAX_T 62
#define ENC_MIN_T 40

#define ENC_X_MAX_T 84
#define ENC_X_MIN_T 20

#define ENC_Y_MAX_T 64
#define ENC_Y_MIN_T 30

#define ENC_Z_MAX_T 20
#define ENC_Z_MIN_T 2

#define BUT_COUNT_MAX 200

#define Uzad 20.5

#define mmPer1X 141.32
#define smPer1X 14
#define kRedX 10
#define mmPer1Y 5
#define mmPer1Z 5
#define microStepDrv1 3200

#define deltaU 0.5
#define deltaU2 0.25
#define OScount 10

#define PAUSE_MAX 1200

#define ENC_U_MAX 250
#define ENC_U_MIN 25

#define ENC_DIR_MAX 22
#define ENC_DIR_MIN 16

#define INDUCTION_X_UP extInSost_5
#define INDUCTION_X_DOWN extInSost_2

#define INDUCTION_Y_UP extInSost_3
#define INDUCTION_Y_DOWN extInSost_4

#define INDUCTION_Z_UP extInSost_6
#define INDUCTION_Z_DOWN extInSost_1

/********/

/**********/
extern uint32_t i, i2, i3;
extern char str1[20];
extern char str2[20];
extern char str3[20];
extern char str4[20];
extern uint8_t tableRUS[];
extern uint32_t lcd_delay;
/**********/

/**********/
extern uint8_t butUp, butDown, butRezerved, butSS, butF2, butF1, butENC, butZ, butY, butX;
extern uint8_t	nameOfAxe, axeXenabled, axeYenabled, axeZenabled;
extern uint8_t alarmX, alarmY, alarmZ, alarm;
extern uint8_t butEmergency;
extern uint8_t extInSost_1, extInSost_2, extInSost_3, extInSost_4, extInSost_5, extInSost_6;
extern char symbMy;
extern uint16_t encVar, encVar2;
extern uint16_t iBut, iBut2;
extern float Uout, UoutF, UoutF3;
extern uint32_t ADC_Data[1];
extern int32_t UoutF2;
extern uint16_t cntU;
extern uint8_t start, Unorm;
extern uint16_t cntOS;
extern uint8_t butPressed, butPr, butRel;
extern uint8_t butUpEnabled, butDownEnabled, butRezervedEnabled, butSSEnabled, butF2Enabled, butF1Enabled, butENCEnabled, butZEnabled, butYEnabled, butXEnabled;		
extern uint16_t butID, butIDNext, butIDNext2;
extern uint8_t directonX;
extern uint16_t pause, pauseCount;
extern uint8_t F1_Ena, F2_Ena;
extern uint8_t menuPoint;
extern float Uref;
extern uint8_t encVarU, encVarDir, encVarSpeedX, encVarSpeedY, encVarSpeedZ;
extern uint8_t encVarU2, encVarDir2, encVarSpeedX2, encVarSpeedY2, encVarSpeedZ2;
extern uint8_t firstInP0, firstInP1, firstInP2;
extern uint8_t firstInP0X, firstInP0Y, firstInP0Z;
extern uint8_t step, zNorm;
extern uint8_t flashVarU, flashVarDir, flashVarSpeedX;
extern uint16_t speedXsm;
/**********/

extern void inInit(void);
extern void inMain(void);
extern void inTimH(void);
extern void inSysT(void);
extern void inSysTConfig(void);
/**********/

/**********/
extern void delay_100us(uint16_t delay_temp);
extern void delay_ms(uint16_t delay_temp);
extern void lcd_write(uint8_t data);
extern void lcd_write_cmd(uint16_t cmd);
extern void Init_LCD(void); // 4 bit mode;
extern void lcd_set_cursor(uint16_t pos, int line);
extern void Print_str(char* str);
extern void LCD_PrintAllStr(void);
extern void LCD_Clear(void);
/**********/
extern void U_calc(void);
extern void OS(void);
extern void osInd(void);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* End of SOFT_H */