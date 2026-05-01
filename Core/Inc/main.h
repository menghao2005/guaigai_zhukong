/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include <stdio.h>	
#include "tim.h"
#include "usart.h"
#include <Math.h>
#include "Stepping_Motor.h"
#include "Gyro.h"
#include "PID.h"
#include "MPU.h"
#include "redandhui.h"
#include "Route.h"
#include "oledfont.h"
#include "oled.h"
#include "ToServo.h"
#include "QRread.h"
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
#define left4_Pin GPIO_PIN_3
#define left4_GPIO_Port GPIOF
#define left3_Pin GPIO_PIN_5
#define left3_GPIO_Port GPIOF
#define right1_Pin GPIO_PIN_10
#define right1_GPIO_Port GPIOF
#define zuoqian_Pin GPIO_PIN_0
#define zuoqian_GPIO_Port GPIOC
#define youqian_Pin GPIO_PIN_1
#define youqian_GPIO_Port GPIOC
#define zuoho_Pin GPIO_PIN_2
#define zuoho_GPIO_Port GPIOC
#define youho_Pin GPIO_PIN_3
#define youho_GPIO_Port GPIOC
#define right2_Pin GPIO_PIN_11
#define right2_GPIO_Port GPIOF
#define right3_Pin GPIO_PIN_12
#define right3_GPIO_Port GPIOF
#define right4_Pin GPIO_PIN_13
#define right4_GPIO_Port GPIOF
#define right5_Pin GPIO_PIN_14
#define right5_GPIO_Port GPIOF
#define right6_Pin GPIO_PIN_15
#define right6_GPIO_Port GPIOF
#define GyroTx_Pin GPIO_PIN_10
#define GyroTx_GPIO_Port GPIOB
#define GyroRx_Pin GPIO_PIN_11
#define GyroRx_GPIO_Port GPIOB
#define RED1_Pin GPIO_PIN_8
#define RED1_GPIO_Port GPIOC
#define RED2_Pin GPIO_PIN_9
#define RED2_GPIO_Port GPIOC
#define left2_Pin GPIO_PIN_11
#define left2_GPIO_Port GPIOG
#define left1_Pin GPIO_PIN_13
#define left1_GPIO_Port GPIOG
#define left5_Pin GPIO_PIN_14
#define left5_GPIO_Port GPIOG
#define left6_Pin GPIO_PIN_15
#define left6_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
