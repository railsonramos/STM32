/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

extern UART_HandleTypeDef huart2;
extern volatile uint16_t adcResultsDMA[9];
extern TIM_HandleTypeDef htim4;
extern const int adcChannelCount;
extern volatile short unsigned adcConversionComplete;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define L_AUX_REDE_RED_Pin GPIO_PIN_5
#define L_AUX_REDE_RED_GPIO_Port GPIOA
#define LED_AUX_GP_AZUL_Pin GPIO_PIN_6
#define LED_AUX_GP_AZUL_GPIO_Port GPIOA
#define SW5_Pin GPIO_PIN_7
#define SW5_GPIO_Port GPIOA
#define IO_SW_Pin GPIO_PIN_13
#define IO_SW_GPIO_Port GPIOF
#define LIGA_EXT_Pin GPIO_PIN_14
#define LIGA_EXT_GPIO_Port GPIOF
#define SAMPLE_Pin GPIO_PIN_15
#define SAMPLE_GPIO_Port GPIOF
#define LED_YELLOW_Pin GPIO_PIN_7
#define LED_YELLOW_GPIO_Port GPIOE
#define LED_GREEN2_Pin GPIO_PIN_8
#define LED_GREEN2_GPIO_Port GPIOE
#define LIGA_REDE_Pin GPIO_PIN_9
#define LIGA_REDE_GPIO_Port GPIOE
#define LED_RED_Pin GPIO_PIN_10
#define LED_RED_GPIO_Port GPIOE
#define LIGA_BAT_Pin GPIO_PIN_11
#define LIGA_BAT_GPIO_Port GPIOE
#define DEBUG_Pin GPIO_PIN_12
#define DEBUG_GPIO_Port GPIOE
#define SW_STATE_Pin GPIO_PIN_13
#define SW_STATE_GPIO_Port GPIOE
#define Debug2_Pin GPIO_PIN_14
#define Debug2_GPIO_Port GPIOE
#define SW2_Pin GPIO_PIN_15
#define SW2_GPIO_Port GPIOE
#define SW3_Pin GPIO_PIN_10
#define SW3_GPIO_Port GPIOB
#define SW4_Pin GPIO_PIN_11
#define SW4_GPIO_Port GPIOB
#define CHAVE_STATE_Pin GPIO_PIN_15
#define CHAVE_STATE_GPIO_Port GPIOB
#define LED_GREEN1_Pin GPIO_PIN_9
#define LED_GREEN1_GPIO_Port GPIOG
#define LIGA_SAIDAS_Pin GPIO_PIN_14
#define LIGA_SAIDAS_GPIO_Port GPIOG
#define L_AUX_BAT_VERDE_Pin GPIO_PIN_8
#define L_AUX_BAT_VERDE_GPIO_Port GPIOB
#define L_AUX_EXT_ORANGE_Pin GPIO_PIN_9
#define L_AUX_EXT_ORANGE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
