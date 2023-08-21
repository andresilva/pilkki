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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define SPI1_DR_8bit (*(__IO uint8_t *)((uint32_t)&(SPI1->DR)))
#define SPI1_DR_16bit (*(__IO uint16_t *)((uint32_t)&(SPI1->DR)))



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
	void uPrintf(const char* fmt, ...);
	
	
	
	
	uint8_t SpiSendByte(uint8_t data);
	uint16_t SpiSendWord(uint16_t data);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SWDIR_Pin GPIO_PIN_4
#define SWDIR_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define iRST_Pin GPIO_PIN_5
#define iRST_GPIO_Port GPIOB
#define PWR_BRR_Pin GPIO_PIN_6
#define PWR_BRR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SWD_R		HAL_GPIO_ReadPin(DI_GPIO_Port, DI_Pin)
#define SWD_W(x)	HAL_GPIO_WritePin(DO_GPIO_Port, DO_Pin, x)
#define SWD_C(x)	HAL_GPIO_WritePin(DCK_GPIO_Port, DCK_Pin, x)
#define SWD_CR  	HAL_GPIO_ReadPin(DCK_GPIO_Port, DCK_Pin)
	
	
#define LEDB(x)		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, x);
#define LEDR(x)		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, x);
#define LEDY(x)		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, x);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
