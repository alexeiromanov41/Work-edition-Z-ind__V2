#include "soft.h"

/**********/
uint32_t i, i2, i3;
char str1[20];
char str2[20];
char str3[20];
char str4[20];
uint8_t tableRUS[] = {
//
		'A', 0xA0, 'B', 0xA1, 0xE0, 'E', 0xA3, 0xA4, 0xA5, 0xA6, 'K', 0xA7, 'M',
		'H', 'O', 0xA8, 'P', 'C', 'T', 0xA9, 0xAA, 'X', 0xE1, 0xAB, 0xAC, 0xE2,
		0xAD, 0xAE, 'b', 0xAF, 0xB0, 0xB1,
//
		'a', 0xB2, 0xB3, 0xB4, 0xE3, 'e', 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB,
		0xBC, 0xBD, 'o', 0xBE, 'p', 'c', 0xBF, 'y', 0xE4, 'x', 0xE5, 0xC0, 0xC1,
		0xE6, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7 };
uint32_t lcd_delay;
/**********/
		
/**********/
uint8_t butUp, butDown, butRezerved, butSS, butF2, butF1, butENC, butZ, butY, butX;		
uint8_t	nameOfAxe, axeXenabled, axeYenabled, axeZenabled;
uint8_t alarmX, alarmY, alarmZ, alarm;
uint8_t butEmergency;
uint8_t extInSost_1, extInSost_2, extInSost_3, extInSost_4, extInSost_5, extInSost_6;
char symbMy;
uint16_t encVar, encVar2;
uint16_t iBut, iBut2;
float Uout, UoutF, UoutF3;
uint32_t ADC_Data[1];
int32_t UoutF2;
uint16_t cntU;	
uint8_t start, Unorm;
uint16_t cntOS;
uint8_t butPressed, butPr, butRel;
uint8_t butUpEnabled, butDownEnabled, butRezervedEnabled, butSSEnabled, butF2Enabled, butF1Enabled, butENCEnabled, butZEnabled, butYEnabled, butXEnabled;		
uint16_t butID, butIDNext, butIDNext2;
uint8_t directonX;
uint16_t pause, pauseCount;
uint8_t F1_Ena, F2_Ena;
uint8_t menuPoint;
float Uref;
uint8_t encVarU, encVarDir, encVarSpeedX, encVarSpeedY, encVarSpeedZ;
uint8_t encVarU2, encVarDir2, encVarSpeedX2, encVarSpeedY2, encVarSpeedZ2;
uint8_t firstInP0, firstInP1, firstInP2;
uint8_t firstInP0X, firstInP0Y, firstInP0Z;
uint8_t step, zNorm;
uint8_t flashVarU, flashVarDir, flashVarSpeedX;
uint16_t speedXsm;
/**********/
uint8_t data;
uint8_t arrPage0[16] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
/**********/

/**********/		

/**********/
void inInit(void);
void inMain(void);
void inTimH(void);
void inSysT(void);
void inSysTConfig(void);
/**********/

/**********/
void delay_100us(uint16_t delay_temp);
void delay_ms(uint16_t delay_temp);
void lcd_write(uint8_t data);
void lcd_write_cmd(uint16_t cmd);
void Init_LCD(void);
void lcd_set_cursor(uint16_t pos, int line);
void Print_str(char* str);
void LCD_PrintAllStr(void);
void LCD_Clear(void);
/**********/
void U_calc(void);
void OS(void);
void osInd(void);

//Prototypes

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void inInit(void) {
	
	EEPROM_Init(&hspi1, NSS_GPIO_Port, NSS_Pin);
	for (i = 0; i < 10000; i++) {}
	EEPROM_ReadByte(0, &flashVarSpeedX);
	EEPROM_ReadByte(1, &flashVarU);
	EEPROM_ReadByte(2, &flashVarDir);

	
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_Data, 1);
	
	HAL_GPIO_WritePin(led_2_GPIO_Port, led_2_Pin, GPIO_PIN_SET); // led LINE

	encVarSpeedX = flashVarSpeedX;
  encVarSpeedX2 = encVarSpeedX;  
	encVarSpeedY = ENC_Y_MAX_T;
	encVarSpeedZ = ENC_Z_MAX_T;
	encVarU = flashVarU;
	encVarDir = flashVarDir;
	
	Uref = (encVarU * 2) / 10.0; // U zadaniya
	
	if (encVarDir == ENC_DIR_MAX)	{
		directonX = 1;
	}	else if (encVarDir == ENC_DIR_MIN)	{
			directonX = 0;
	}
	
	step = 0;
	zNorm = 0;

	for (i = 0; i < 10000; i++) {}
	Init_LCD();
	for (i = 0; i < 10000; i++) {}
	LCD_Clear();
	for (i = 0; i < 10000; i++) {}
		
	sprintf((char *) str1, "Welding portal");
	lcd_set_cursor(0, 0);
	Print_str(str1);
	
	sprintf(str2, "NovoTechReil");
	lcd_set_cursor(0, 1);
	Print_str(str2);
	
	sprintf(str3, "SVARMASTER");
	lcd_set_cursor(20, 0);
	Print_str(str3);
	
	sprintf(str4, "+7-(4832)-77-2000");
	lcd_set_cursor(20, 1);
	Print_str(str4);

  __HAL_TIM_SET_AUTORELOAD(&htim5, ENC_X_MAX_T + 20);    
	__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedX);			
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);		
		
	for (i = 0; i < 9000000; i++) {}	
	LCD_Clear();
	for (i = 0; i < 10000; i++) {}

	if(butEmergency == 0) {
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	}	else {
		alarm = 1;
	}

  for (i = 0; i < 900000; i++) {}	
		
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void inMain(void) {

/*********************if alarm DRV or induction ON*****************************/	
	if((alarmX == 0) || (alarmY == 0) || (alarmZ == 0) || (alarm == 1) || 
    (INDUCTION_X_UP == 0) || (INDUCTION_X_DOWN == 0) || (INDUCTION_Y_UP == 0)
    || (INDUCTION_Y_DOWN == 0) || (INDUCTION_Z_UP == 0)) {
		HAL_GPIO_WritePin(led_1_GPIO_Port, led_1_Pin, GPIO_PIN_SET); // led ALARM		
	} else {
      HAL_GPIO_WritePin(led_1_GPIO_Port, led_1_Pin, GPIO_PIN_RESET); // led ALARM
	}
/*****************************************************************************/	

/***************************F1 button handler*********************************/		
	if(butF1Enabled) {
		HAL_GPIO_WritePin(rele_1_GPIO_Port, rele_1_Pin, GPIO_PIN_SET);
		F1_Ena = 1;
		
		sprintf(str4, "F1: ON ");
		lcd_set_cursor(20, 1);
		Print_str(str4);
	} else {
		HAL_GPIO_WritePin(rele_1_GPIO_Port, rele_1_Pin, GPIO_PIN_RESET);
		F1_Ena = 0;
		
		sprintf(str4, "F1: OFF");
		lcd_set_cursor(20, 1);
		Print_str(str4);
	}
/*****************************************************************************/	

/***************************Switch in menu points*****************************/	
	switch (menuPoint)
    {
/*_____________________________________________________________*/			
    	case 0: // point of Speed on Axes
				firstInP1 = 0;
				firstInP2 = 0;
			
				if((butXEnabled) || (butYEnabled) || (butZEnabled)) {
					sprintf(str1, "*");
					lcd_set_cursor(7, 0);
					Print_str(str1);	
				}

				sprintf(str2, " ");
				lcd_set_cursor(9, 1);
				Print_str(str2);

				sprintf(str3, " ");
				lcd_set_cursor(29, 0);
				Print_str(str3);

				/********************/
				if (butXEnabled)
				{
					firstInP0X ++;
					if(firstInP0X >= 2) {
						firstInP0X = 2;
					} else if(firstInP0X == 1){
						__HAL_TIM_SET_AUTORELOAD(&htim5, ENC_X_MAX_T + 20);		
            __HAL_TIM_SET_COUNTER(&htim5, encVarSpeedX);            
					}
					firstInP0Y = 0;
					firstInP0Z = 0;
          
          for (i = 0; i < 10000; i++) {}

				if(firstInP0X == 2) {
					encVarSpeedX = __HAL_TIM_GET_COUNTER(&htim5);
					if(encVarSpeedX < ENC_X_MIN_T) {
						encVarSpeedX = ENC_X_MIN_T;
						__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedX);
					}
					if(encVarSpeedX > ENC_X_MAX_T) {
						encVarSpeedX = ENC_X_MAX_T;
						__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedX);
					}			
					
					if(encVarSpeedX != encVarSpeedX2) {
						//__HAL_TIM_SET_AUTORELOAD(&htim2, (encVarSpeedX * 1000));
            EEPROM_WriteByte(0, encVarSpeedX);
					}

					encVarSpeedX2 = encVarSpeedX;					
				}	
										
				}
				/********************/

				/********************/
				if (butYEnabled)
				{
//					firstInP0Y ++;
//					if(firstInP0Y >= 2) {
//						firstInP0Y = 2;
//					} else {
//						__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedY);
//						__HAL_TIM_SET_AUTORELOAD(&htim5, ENC_Y_MAX_T + 20);						
//					}
//					firstInP0X = 0;
//					firstInP0Z = 0;
//					
//					if(firstInP0Y == 2) {
//						encVarSpeedY = __HAL_TIM_GET_COUNTER(&htim5);
//						if(encVarSpeedY < ENC_Y_MIN_T) {
//							encVarSpeedY = ENC_Y_MIN_T;
//							__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedY);
//						}
//						if(encVarSpeedY > ENC_Y_MAX_T) {
//							encVarSpeedY = ENC_Y_MAX_T;
//							__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedY);
//						}			
//						
//						if(encVarSpeedY != encVarSpeedY2) {
//							__HAL_TIM_SET_AUTORELOAD(&htim3, (encVarSpeedY * 1000));						
//						}

//						encVarSpeedY2 = encVarSpeedY;					
//					}
					
				}
				/********************/
				
				/********************/
				if (butZEnabled)
				{
//					firstInP0Z ++;
//					if(firstInP0Z >= 2) {
//						firstInP0Z = 2;
//					} else {
//						__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedZ);
//						__HAL_TIM_SET_AUTORELOAD(&htim5, ENC_Z_MAX_T + 20);						
//					}
//					firstInP0X = 0;
//					firstInP0Y = 0;
//					
//					if(firstInP0Z == 2) {
//						encVarSpeedZ = __HAL_TIM_GET_COUNTER(&htim5);
//						if(encVarSpeedZ < ENC_Z_MIN_T) {
//							encVarSpeedZ = ENC_Z_MIN_T;
//							__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedZ);
//						}
//						if(encVarSpeedZ > ENC_Z_MAX_T) {
//							encVarSpeedZ = ENC_Z_MAX_T;
//							__HAL_TIM_SET_COUNTER(&htim5, encVarSpeedZ);
//						}			
//						
//						if(encVarSpeedZ != encVarSpeedZ2) {
//							__HAL_TIM_SET_AUTORELOAD(&htim4, (encVarSpeedZ * 1000));						
//						}

//						encVarSpeedZ2 = encVarSpeedZ;					
//					}
					
				}									
				/********************/				
    		break;
/*_____________________________________________________________*/

/*_____________________________________________________________*/				
    	case 1: // point of Uref for control
				firstInP1 ++;
				if(firstInP1 >= 2) {
					firstInP1 = 2;
				} else {
					__HAL_TIM_SET_COUNTER(&htim5, encVarU);
					__HAL_TIM_SET_AUTORELOAD(&htim5, ENC_U_MAX + 20);				
				}
				firstInP0 = 0;
				firstInP2 = 0;

				firstInP0X = 0;
				firstInP0Y = 0;
				firstInP0Z = 0;				
			
				sprintf(str2, "*");
				lcd_set_cursor(9, 1);
				Print_str(str2);
			
				sprintf(str1, " ");
				lcd_set_cursor(7, 0);
				Print_str(str1);
			
				sprintf(str3, " ");
				lcd_set_cursor(29, 0);
				Print_str(str3);
				
				if(firstInP1 == 2) {
					encVarU = __HAL_TIM_GET_COUNTER(&htim5);
					if(encVarU < ENC_U_MIN) {
						encVarU = ENC_U_MIN;
						__HAL_TIM_SET_COUNTER(&htim5, encVarU);
					}
					if(encVarU > ENC_U_MAX) {
						encVarU = ENC_U_MAX;
						__HAL_TIM_SET_COUNTER(&htim5, encVarU);
					}			
					
					if(encVarU != encVarU2) {
						Uref = (encVarU * 2) / 10.0;
						EEPROM_WriteByte(1, encVarU);
					}

					encVarU2 = encVarU;				
				}
				
    		break;
/*_____________________________________________________________*/

/*_____________________________________________________________*/				
			case 2:  // point of Direction on Axe X for auto mode
				firstInP2 ++;
				if(firstInP2 >= 2) {
					firstInP2 = 2;
				} else {
					__HAL_TIM_SET_COUNTER(&htim5, encVarDir);
					__HAL_TIM_SET_AUTORELOAD(&htim5, ENC_DIR_MAX + 20);						
				}
				firstInP1 = 0;
				firstInP0 = 0;

				firstInP0X = 0;
				firstInP0Y = 0;
				firstInP0Z = 0;				
			
				sprintf(str3, "*");
				lcd_set_cursor(29, 0);
				Print_str(str3);
			
				sprintf(str2, " ");
				lcd_set_cursor(9, 1);
				Print_str(str2);
			
				sprintf(str1, " ");
				lcd_set_cursor(7, 0);
				Print_str(str1);
				
				if(firstInP2 == 2) {
					encVarDir = __HAL_TIM_GET_COUNTER(&htim5);
					if(encVarDir < ENC_DIR_MIN) {
						encVarDir = ENC_DIR_MIN;
						__HAL_TIM_SET_COUNTER(&htim5, encVarDir);
					}
					if(encVarDir > ENC_DIR_MAX) {
						encVarDir = ENC_DIR_MAX;
						__HAL_TIM_SET_COUNTER(&htim5, encVarDir);
					}			
					
					if(encVarDir != encVarDir2) {
						if (encVarDir == ENC_DIR_MAX)
						{
							directonX = 1;
						}
						else if (encVarDir == ENC_DIR_MIN)
						{
							directonX = 0;
						}
						
						EEPROM_WriteByte(2, encVarDir);	
					}

					encVarDir2 = encVarDir;				
				}
							
    		break;
/*_____________________________________________________________*/				
			
    	default:
    		break;
    }	
/*****************************************************************************/		

/***************************Switch button F2, not use now*****************************/
	if(butF2Enabled) {
		HAL_GPIO_WritePin(rele_2_GPIO_Port, rele_2_Pin, GPIO_PIN_SET);
		F2_Ena = 1;
		
		sprintf(str4, "F2: ON ");
		lcd_set_cursor(33, 1);
		Print_str(str4);		
	} else {
		HAL_GPIO_WritePin(rele_2_GPIO_Port, rele_2_Pin, GPIO_PIN_RESET);
		F2_Ena = 0;
		
		sprintf(str4, "F2: OFF");
		lcd_set_cursor(33, 1);
		Print_str(str4);
	}
/*****************************************************************************/	

/***************************Switch direction axe X for auto mode*****************************/
	if(directonX) {
		sprintf(str3, "Dir: For");
		lcd_set_cursor(20, 0);
		Print_str(str3);		
	}	else {
		sprintf(str3, "Dir: Rev");
		lcd_set_cursor(20, 0);
		Print_str(str3);		
	}
/*****************************************************************************/	
	
/***************************Switch start / stop on LCD*****************************/	
	if(start) {
		sprintf(str3, "Start");
		lcd_set_cursor(35, 0);
		Print_str(str3);		
	}	else {
		sprintf(str3, "Stop ");
		lcd_set_cursor(35, 0);
		Print_str(str3);		
	}
/*****************************************************************************/	

/***************************Switch button axe X on LCD*****************************/		
	if(butXEnabled) {
		butYEnabled = 0;
		butZEnabled = 0;
		
		sprintf(str1, "X");
		lcd_set_cursor(5, 0);
		Print_str(str1);
	}
/*****************************************************************************/		
	
/***************************Switch button axe Y on LCD*****************************/	
	if(butYEnabled) {
		butXEnabled = 0;
		butZEnabled = 0;
		
		sprintf(str1, "Y");
		lcd_set_cursor(5, 0);
		Print_str(str1);
	}
/*****************************************************************************/	

/***************************Switch button axe Z on LCD*****************************/	
	if(butZEnabled) {
		butXEnabled = 0;
		butYEnabled = 0;
		
		sprintf(str1, "Z");
		lcd_set_cursor(5, 0);
		Print_str(str1);
	}
/*****************************************************************************/

/***************************If no axis is selected*****************************/	
	if((butZEnabled == 0) && (butYEnabled == 0) && (butXEnabled == 0)) {
		sprintf(str1, "Axe: 0             ");
		lcd_set_cursor(0, 0);
		Print_str(str1);
	}
/*****************************************************************************/	

/**********************If one of the axes is active and the up or down button is pressed*********************/	
	if (((butDownEnabled) || (butUpEnabled)) && ((butXEnabled) || (butYEnabled) || (butZEnabled)))	{
/*_____________________________________________________________*/		
		if((butXEnabled) && (start == 0)) { 
      __HAL_TIM_SET_AUTORELOAD(&htim2, (ENC_X_MIN_T * 1000));
			if ((butDownEnabled) && (INDUCTION_X_DOWN)) {
				HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ((ENC_X_MIN_T * 1000) / 2));
			} else if(butUpEnabled == 0) {
         butDownEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0); 
      }
			if ((butUpEnabled) && (INDUCTION_X_UP)) {
				HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ((ENC_X_MIN_T * 1000) / 2));
			} else if(butDownEnabled == 0) {
         butUpEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0); 
      }
			if((butDownEnabled == 0) && (butUpEnabled == 0))	{
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
			}	
		} else if((butXEnabled) && (start == 1)) {
				__HAL_TIM_SET_AUTORELOAD(&htim2, (encVarSpeedX * 1000));
		} else if((butXEnabled == 0) && (start == 0)) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
		}
/*_____________________________________________________________*/		

/*_____________________________________________________________*/		
		if(butYEnabled) { 
			__HAL_TIM_SET_AUTORELOAD(&htim3, (ENC_Y_MAX_T * 1000));
			if ((butDownEnabled) && (INDUCTION_Y_DOWN)) {
        HAL_GPIO_WritePin(dir_2_GPIO_Port, dir_2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ((ENC_Y_MAX_T * 1000) / 2));	
			} else if(butUpEnabled == 0) {
         butDownEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0); 
      }
			if ((butUpEnabled) && (INDUCTION_Y_UP)) {
				HAL_GPIO_WritePin(dir_2_GPIO_Port, dir_2_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ((ENC_Y_MAX_T * 1000) / 2));
			} else if(butDownEnabled == 0) {
         butUpEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0); 
      }
			if((butDownEnabled == 0) && (butUpEnabled == 0))	{
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			}
		}
/*_____________________________________________________________*/

/*_____________________________________________________________*/
		if((butZEnabled) && (start == 0)) {
			__HAL_TIM_SET_AUTORELOAD(&htim4, (ENC_Z_MIN_T * 1000));
			if ((butDownEnabled) && (INDUCTION_Z_DOWN)) {
				HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MIN_T * 1000) / 2));
			} else if(butUpEnabled == 0) {
         butDownEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0); 
      }
			if ((butUpEnabled) && (INDUCTION_Z_UP)) {
				HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_SET);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MIN_T * 1000) / 2));
			} else if(butDownEnabled == 0) {
         butUpEnabled = 0;
         __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0); 
      }
			if((butDownEnabled == 0) && (butUpEnabled == 0))  {
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
			}			
		} else if((butZEnabled) && (start == 1)) {
				__HAL_TIM_SET_AUTORELOAD(&htim4, (ENC_Z_MAX_T * 1000));
		} else if((butZEnabled == 0) && (start == 0)) {
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
		}
/*_____________________________________________________________*/		
	} else {
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		
		if(start == 0) {
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);		
		}

	}
/*****************************************************************************/	

/***************************If axe X is selected*****************************/	
    speedXsm = ((((84000000 / encVarSpeedX) / microStepDrv1) / kRedX) * smPer1X * 60) / 1000;  
  
		if(butXEnabled) {
			sprintf(str1, "Speed_X:%3d", speedXsm);
			lcd_set_cursor(8, 0);
			Print_str(str1);
		}
/*****************************************************************************/		

/***************************If axe Y is selected*****************************/		
		if(butYEnabled) {
			sprintf(str1, "Speed_Y: %2d", encVarSpeedY);
			lcd_set_cursor(8, 0);
			Print_str(str1);
		}
/*****************************************************************************/		

/***************************If axe Z is selected*****************************/		
		if(butZEnabled) {
			sprintf(str1, "Speed_Z: %2d", encVarSpeedZ);
			lcd_set_cursor(8, 0);
			Print_str(str1);
		}
/*****************************************************************************/		

/***************************Uref out on LCD*****************************/
		sprintf(str2, "Uz: %2.1f", Uref);
		lcd_set_cursor(0, 1);
		Print_str(str2);
/*****************************************************************************/		

/***************************Uout filtered out on LCD*****************************/		
		sprintf(str2, "Uo: %2.1f", UoutF);
		lcd_set_cursor(11, 1);
		Print_str(str2);
/*****************************************************************************/		
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void inTimH(void) {

	
		
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void inSysT(void) {
	if (lcd_delay > 0) {
		lcd_delay--;
	}

	butRezerved = HAL_GPIO_ReadPin(in_1_GPIO_Port, in_1_Pin);
	butSS = HAL_GPIO_ReadPin(in_2_GPIO_Port, in_2_Pin);
	butF2 = HAL_GPIO_ReadPin(in_3_GPIO_Port, in_3_Pin);
	butF1 = HAL_GPIO_ReadPin(in_4_GPIO_Port, in_4_Pin);
	butDown = HAL_GPIO_ReadPin(in_5_GPIO_Port, in_5_Pin);
	butUp = HAL_GPIO_ReadPin(in_6_GPIO_Port, in_6_Pin);
	butENC = HAL_GPIO_ReadPin(in_7_GPIO_Port, in_7_Pin);
	butZ = HAL_GPIO_ReadPin(in_8_GPIO_Port, in_8_Pin);
	butY = HAL_GPIO_ReadPin(in_9_GPIO_Port, in_9_Pin);
	butX = HAL_GPIO_ReadPin(in_10_GPIO_Port, in_10_Pin);
	
	butEmergency = HAL_GPIO_ReadPin(emergency_GPIO_Port, emergency_Pin);
	
	butID = (butX << 10) + (butY << 9) + (butZ << 8) + (butENC << 7) + (butUp << 6) + (butDown << 5) + (butF1 << 4) + (butF2 << 3) + (butSS << 2) + (butRezerved << 1);
	
	if(butID != 2046) {
		iBut ++;
		if(iBut >= BUT_COUNT_MAX) {
			iBut = BUT_COUNT_MAX;
			butIDNext = butID;
		}		
	} else if((iBut == BUT_COUNT_MAX) && (butID == 2046)) {
			iBut2 ++;
			if(iBut2 >= BUT_COUNT_MAX) {
				iBut2 = BUT_COUNT_MAX;
			}

			if((iBut == BUT_COUNT_MAX) && (iBut2 == BUT_COUNT_MAX)) {
				
				switch (butIDNext)
					{
						case 1918: // ENC
							butENCEnabled = ~butENCEnabled;
							menuPoint ++;
							if(menuPoint > 2) {
								menuPoint = 0;
							}
							break;
						case 1022: // X
							butXEnabled = ~butXEnabled;
							butYEnabled = 0;
							butZEnabled = 0;
							butDownEnabled = 0;
							butUpEnabled = 0;
							break;
						case 1534: // Y
							butYEnabled = ~butYEnabled;
							butXEnabled = 0;
							butZEnabled = 0;
							butDownEnabled = 0;
							butUpEnabled = 0;						
							break;
						case 1790: // Z
							butZEnabled = ~butZEnabled;
							butXEnabled = 0;
							butYEnabled = 0;
							butDownEnabled = 0;
							butUpEnabled = 0;						
							break;
						case 2030: // F1
							butF1Enabled = ~butF1Enabled;
							break;
						case 2038: // F2
							butF2Enabled = ~butF2Enabled;
							break;
						case 1982: // UP
							butUpEnabled = ~butUpEnabled;
							butDownEnabled = 0;
							break;
						case 2014: // DOWN
							butDownEnabled = ~butDownEnabled;
							butUpEnabled = 0;
							break;
						case 2042: // SS
							butSSEnabled = ~butSSEnabled;
							start = ~start;
              if (butSSEnabled == 0) {
                __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
              }
							butDownEnabled = 0;
							butUpEnabled = 0;
							butXEnabled = 0;
							butYEnabled = 0;
							butZEnabled = 0;						
							break;					
						default:
							iBut = 0;
							iBut2 = 0;
							butIDNext = 2046;
							break;
					}				
				
				iBut = 0;
				iBut2 = 0;
				butIDNext = 2046;
			}
			
	} else {
		iBut = 0;
		iBut2 = 0;
		butIDNext = 2046;
	}
	
	extInSost_1 = HAL_GPIO_ReadPin(extIn_1_GPIO_Port, extIn_1_Pin);
	extInSost_2 = HAL_GPIO_ReadPin(extIn_2_GPIO_Port, extIn_2_Pin);
	extInSost_3 = HAL_GPIO_ReadPin(extIn_3_GPIO_Port, extIn_3_Pin);
	extInSost_4 = HAL_GPIO_ReadPin(extIn_4_GPIO_Port, extIn_4_Pin);
	extInSost_5 = HAL_GPIO_ReadPin(extIn_5_GPIO_Port, extIn_5_Pin);
	extInSost_6 = HAL_GPIO_ReadPin(extIn_6_GPIO_Port, extIn_6_Pin);
	
	alarmX = HAL_GPIO_ReadPin(alarm_1_GPIO_Port, alarm_1_Pin);
	alarmY = HAL_GPIO_ReadPin(alarm_2_GPIO_Port, alarm_2_Pin);
	alarmZ = HAL_GPIO_ReadPin(alarm_3_GPIO_Port, alarm_3_Pin);
	
	U_calc();
	
	cntOS ++;
	
	if(cntOS >= OScount) {
		cntOS = 0;
		osInd();	
	}

}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void inSysTConfig(void) {
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 16800);
	/**Configure the Systick 
	 */
	HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 12, 0);	
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void delay_100us(uint16_t delay_temp) {
	lcd_delay = delay_temp;
	while (lcd_delay > 0) {
		lcd_delay = lcd_delay;
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void delay_ms(uint16_t delay_temp) {
	lcd_delay = delay_temp * 10;
	while (lcd_delay > 0) {
		lcd_delay = lcd_delay;
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void lcd_write(uint8_t data) {
	GPIOC->BSRR = (GPIO_BSRR_BR8 | GPIO_BSRR_BR9); // 
	GPIOA->BSRR = (GPIO_BSRR_BR8 | GPIO_BSRR_BR9); // 
	delay_100us(1);
	if (data & 128) {
		GPIOC->BSRR = GPIO_BSRR_BS8;
	}
	if (data & 64) {
		GPIOC->BSRR = GPIO_BSRR_BS9;
	}
	if (data & 32) {
		GPIOA->BSRR = GPIO_BSRR_BS8;
	}
	if (data & 16) {
		GPIOA->BSRR = GPIO_BSRR_BS9;
	}

	GPIOA->BSRR = GPIO_BSRR_BR10; // 
	delay_100us(1);
	GPIOA->BSRR = GPIO_BSRR_BS10; // 
	delay_100us(1);
	GPIOA->BSRR = GPIO_BSRR_BR10; // 
	delay_100us(1);

	GPIOC->BSRR = (GPIO_BSRR_BR8 | GPIO_BSRR_BR9); // 
	GPIOA->BSRR = (GPIO_BSRR_BR8 | GPIO_BSRR_BR9); // 
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void lcd_write_cmd(uint16_t cmd) {
	delay_100us(1);
	GPIOA->BSRR = GPIO_BSRR_BR12;

	lcd_write(cmd);
	lcd_write(cmd << 4);

	GPIOA->BSRR = GPIO_BSRR_BS12;
	delay_100us(1);
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void Init_LCD(void)	{
	GPIOA->BSRR = GPIO_BSRR_BS12;
	GPIOA->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9 | GPIO_BSRR_BR10
			| GPIO_BSRR_BR11;
	GPIOC->BSRR = GPIO_BSRR_BR8 | GPIO_BSRR_BR9;
	delay_ms(10);

	// function set
	GPIOA->BSRR = GPIO_BSRR_BR12;
	lcd_write(0x20);
	GPIOA->BSRR = GPIO_BSRR_BS12;
	lcd_write_cmd(0x2A);
	delay_100us(10);

	// display on control
	lcd_write_cmd(0x0C);
	delay_100us(10);

	// display clear
	lcd_write_cmd(1);
	delay_100us(10);

	// return home
	lcd_write_cmd(2);
	delay_100us(10);

	// entry mode set
	lcd_write_cmd(0x06);
	delay_100us(50);
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void lcd_set_cursor(uint16_t pos, int line) {
	pos |= (1 << 7);
	if (line == 1) {
		pos += 0x40;
	}
	lcd_write_cmd(pos);
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void lcd_write_data(uint8_t c) {
	switch (c) {
//	case '�':
//		c = 0xA2;
//		break;
//	case '�':
//		c = 0xB5;
//		break;
//	case '�':
//		c = 0xEF;
//		break;
	default:
		if ((c >= 0xC0) && (c <= 0xFF))
			c = tableRUS[c - 0xC0];
		break;
	}
	lcd_write(c);
	lcd_write(c << 4);
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void Print_str(char* str) {
	int32_t i;
	uint8_t c;
	for (i = 0; i < 20; i++) {
		c = str[i];
		if (c == 0)
			break;
		lcd_write_data(c);
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void LCD_PrintAllStr(void) {


	lcd_set_cursor(0, 0);
	Print_str(str1);
	for (i = 0; i < 100; i++) {
	}
	lcd_set_cursor(0, 1);
	Print_str(str2);
	for (i = 0; i < 100; i++) {
	}
	lcd_set_cursor(20, 0);
	Print_str(str3);
	for (i = 0; i < 100; i++) {
	}
	lcd_set_cursor(20, 1);
	Print_str(str4);
	for (i = 0; i < 100; i++) {
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void LCD_Clear(void) {
	GPIOA->BSRR = GPIO_BSRR_BR12;
	lcd_write_cmd(1);
	delay_100us(50);
	lcd_write_cmd(2);
	GPIOA->BSRR = GPIO_BSRR_BS12;
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void U_calc(void) {
	
	if(ADC_Data[0] > 100) {
		Uout = ADC_Data[0] / 56.25;
		UoutF3 += (Uout - UoutF3) * 0.05;
	} else {
		Uout = 0;
		UoutF3 = 0;
	}
	
	cntU ++;
	
	if(cntU >= 5000) {
		cntU = 0;
		UoutF = UoutF3;
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void OS(void) {	
	if(start) {
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ((encVarSpeedX * 1000) / 2));
		if(directonX) {
			HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_SET);
		}
		
		pauseCount ++;
		if(pauseCount >= PAUSE_MAX) {
			pauseCount = PAUSE_MAX;

		if(UoutF3 > Uref + deltaU) {
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((encVarSpeedZ * 1000) / 2));
			HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_RESET);
			Unorm = 0;
		}
		
		if(UoutF3 < Uref - deltaU) {
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((encVarSpeedZ * 1000) / 2));
			HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_SET);
			Unorm = 0;
		}		
		
		if((UoutF3 >= Uref - deltaU2) && (UoutF3 <= Uref + deltaU2)) {
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
			Unorm = 1;
		}			
			
		} else {
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);	
		}
				
	}	else {
		pauseCount = 0;
		
	}

}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void osInd(void) {	
	if(start) {
		
    __HAL_TIM_SET_AUTORELOAD(&htim2, (encVarSpeedX * 1000));
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ((encVarSpeedX * 1000) / 2));
		if(directonX) {
			HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(dir_1_GPIO_Port, dir_1_Pin, GPIO_PIN_SET);
		}
		
    __HAL_TIM_SET_AUTORELOAD(&htim4, (ENC_Z_MAX_T * 1000));
		/********************/
		switch (step)
    {
    	case 0:
				if(extInSost_1 == 1) {
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MAX_T * 1000) / 2));
					HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_RESET);
				} else {
						__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MAX_T * 1000) / 2));
						HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_SET);
						zNorm = 1;
						step = 1;	
				}	
    		break;
		/********************/	
    	case 1:
				if(extInSost_1 == 0) {
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MAX_T * 1000) / 2));
					HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_SET);
				} else {
						__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ((ENC_Z_MAX_T * 1000) / 2));
						HAL_GPIO_WritePin(dir_3_GPIO_Port, dir_3_Pin, GPIO_PIN_RESET);
						zNorm = 0;
						step = 0;	
				}
    		break;
    }
		/********************/				

    if((INDUCTION_X_UP == 0) || (INDUCTION_X_DOWN == 0) || (INDUCTION_Z_UP == 0)) {
      butSSEnabled = 0;
      start = 0;
      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
      butDownEnabled = 0;
      butUpEnabled = 0;
      butXEnabled = 0;
      butYEnabled = 0;
      butZEnabled = 0;      
    }
		
	} else {
			step = 0;
			zNorm = 0;
	}
}
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

