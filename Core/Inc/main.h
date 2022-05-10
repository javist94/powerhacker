/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
// OPEN-OCD COMMAND: openocd -f /usr/local/Cellar/open-ocd/0.10.0/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/Cellar/open-ocd/0.10.0/share/openocd/scripts/target/stm32f3x.cfg
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

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
#define CH1_VSETDAC_Pin GPIO_PIN_4
#define CH1_VSETDAC_GPIO_Port GPIOA
#define BUTTON_CHENABLE_Pin GPIO_PIN_5
#define BUTTON_CHENABLE_GPIO_Port GPIOA
#define CH2_VSETDAC_Pin GPIO_PIN_6
#define CH2_VSETDAC_GPIO_Port GPIOA
#define BUTTON_MODE_Pin GPIO_PIN_0
#define BUTTON_MODE_GPIO_Port GPIOB
#define VIN_VREAD_SDADC1_Pin GPIO_PIN_1
#define VIN_VREAD_SDADC1_GPIO_Port GPIOB
#define CH1_CREAD_SDADC1_Pin GPIO_PIN_2
#define CH1_CREAD_SDADC1_GPIO_Port GPIOB
#define CH1_VREAD_SDADC2_Pin GPIO_PIN_9
#define CH1_VREAD_SDADC2_GPIO_Port GPIOE
#define CH2_CREAD_SDADC3_Pin GPIO_PIN_15
#define CH2_CREAD_SDADC3_GPIO_Port GPIOB
#define CH2_VREAD_SDADC3_Pin GPIO_PIN_8
#define CH2_VREAD_SDADC3_GPIO_Port GPIOD
#define BUTTON_CHSELECT_Pin GPIO_PIN_9
#define BUTTON_CHSELECT_GPIO_Port GPIOA
#define SDCARD_SCRIPT_LED_Pin GPIO_PIN_6
#define SDCARD_SCRIPT_LED_GPIO_Port GPIOF
#define SDCARD_LOG_LED_Pin GPIO_PIN_7
#define SDCARD_LOG_LED_GPIO_Port GPIOF
#define LOAD_CH2_LED_Pin GPIO_PIN_3
#define LOAD_CH2_LED_GPIO_Port GPIOB
#define ENCODER_IN_BTN_Pin GPIO_PIN_4
#define ENCODER_IN_BTN_GPIO_Port GPIOB
#define ENCODER_IN_A_Pin GPIO_PIN_5
#define ENCODER_IN_A_GPIO_Port GPIOB
#define ENCODER_IN_B_Pin GPIO_PIN_6
#define ENCODER_IN_B_GPIO_Port GPIOB
#define LOAD_CH1_LED_Pin GPIO_PIN_8
#define LOAD_CH1_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
