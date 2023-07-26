/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define emergency_Pin GPIO_PIN_13
#define emergency_GPIO_Port GPIOC
#define emergency_EXTI_IRQn EXTI15_10_IRQn
#define extIn_6_Pin GPIO_PIN_14
#define extIn_6_GPIO_Port GPIOC
#define extIn_6_EXTI_IRQn EXTI15_10_IRQn
#define extIn_5_Pin GPIO_PIN_15
#define extIn_5_GPIO_Port GPIOC
#define extIn_5_EXTI_IRQn EXTI15_10_IRQn
#define extIn_4_Pin GPIO_PIN_0
#define extIn_4_GPIO_Port GPIOC
#define extIn_4_EXTI_IRQn EXTI0_IRQn
#define extIn_3_Pin GPIO_PIN_1
#define extIn_3_GPIO_Port GPIOC
#define extIn_3_EXTI_IRQn EXTI1_IRQn
#define extIn_2_Pin GPIO_PIN_2
#define extIn_2_GPIO_Port GPIOC
#define extIn_2_EXTI_IRQn EXTI2_IRQn
#define extIn_1_Pin GPIO_PIN_3
#define extIn_1_GPIO_Port GPIOC
#define ENC_A_Pin GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOA
#define ADC_U_Pin GPIO_PIN_2
#define ADC_U_GPIO_Port GPIOA
#define alarm_3_Pin GPIO_PIN_3
#define alarm_3_GPIO_Port GPIOA
#define PWM_1_Pin GPIO_PIN_5
#define PWM_1_GPIO_Port GPIOA
#define PWM_2_Pin GPIO_PIN_6
#define PWM_2_GPIO_Port GPIOA
#define MOSI_Pin GPIO_PIN_7
#define MOSI_GPIO_Port GPIOA
#define alarm_2_Pin GPIO_PIN_4
#define alarm_2_GPIO_Port GPIOC
#define alarm_1_Pin GPIO_PIN_5
#define alarm_1_GPIO_Port GPIOC
#define ena_3_Pin GPIO_PIN_0
#define ena_3_GPIO_Port GPIOB
#define ena_2_Pin GPIO_PIN_1
#define ena_2_GPIO_Port GPIOB
#define ena_1_Pin GPIO_PIN_2
#define ena_1_GPIO_Port GPIOB
#define dir_3_Pin GPIO_PIN_10
#define dir_3_GPIO_Port GPIOB
#define dir_2_Pin GPIO_PIN_11
#define dir_2_GPIO_Port GPIOB
#define dir_1_Pin GPIO_PIN_12
#define dir_1_GPIO_Port GPIOB
#define rele_2_Pin GPIO_PIN_13
#define rele_2_GPIO_Port GPIOB
#define rele_1_Pin GPIO_PIN_14
#define rele_1_GPIO_Port GPIOB
#define led_2_Pin GPIO_PIN_15
#define led_2_GPIO_Port GPIOB
#define led_1_Pin GPIO_PIN_6
#define led_1_GPIO_Port GPIOC
#define in_10_Pin GPIO_PIN_7
#define in_10_GPIO_Port GPIOC
#define LCD_DB7_Pin GPIO_PIN_8
#define LCD_DB7_GPIO_Port GPIOC
#define LCD_DB6_Pin GPIO_PIN_9
#define LCD_DB6_GPIO_Port GPIOC
#define LCD_DB5_Pin GPIO_PIN_8
#define LCD_DB5_GPIO_Port GPIOA
#define LCD_DB4_Pin GPIO_PIN_9
#define LCD_DB4_GPIO_Port GPIOA
#define LCD_E_Pin GPIO_PIN_10
#define LCD_E_GPIO_Port GPIOA
#define LCD_RW_Pin GPIO_PIN_11
#define LCD_RW_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_12
#define LCD_RS_GPIO_Port GPIOA
#define SW_DIO_Pin GPIO_PIN_13
#define SW_DIO_GPIO_Port GPIOA
#define SW_CLK_Pin GPIO_PIN_14
#define SW_CLK_GPIO_Port GPIOA
#define in_9_Pin GPIO_PIN_15
#define in_9_GPIO_Port GPIOA
#define in_8_Pin GPIO_PIN_10
#define in_8_GPIO_Port GPIOC
#define in_7_Pin GPIO_PIN_11
#define in_7_GPIO_Port GPIOC
#define in_6_Pin GPIO_PIN_12
#define in_6_GPIO_Port GPIOC
#define in_5_Pin GPIO_PIN_2
#define in_5_GPIO_Port GPIOD
#define SCK_Pin GPIO_PIN_3
#define SCK_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_4
#define MISO_GPIO_Port GPIOB
#define in_4_Pin GPIO_PIN_5
#define in_4_GPIO_Port GPIOB
#define PWM_3_Pin GPIO_PIN_6
#define PWM_3_GPIO_Port GPIOB
#define in_3_Pin GPIO_PIN_7
#define in_3_GPIO_Port GPIOB
#define in_2_Pin GPIO_PIN_8
#define in_2_GPIO_Port GPIOB
#define in_2_EXTI_IRQn EXTI9_5_IRQn
#define in_1_Pin GPIO_PIN_9
#define in_1_GPIO_Port GPIOB
#define NSS_Pin GPIO_PIN_4
#define NSS_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
