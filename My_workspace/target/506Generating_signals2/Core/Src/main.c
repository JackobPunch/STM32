/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
int values1[] = {379,376,378,389,380,378,377,389,378,376,383,387,387,375,379,381,384,379,388,380,379,378,378,381,377,390,383,380,376,388,378,384,387,383,378,377,379,393,385,383,380,376,386,390,381,381,384,403,377,379,382,391,377,376,380,382,380,374,380,386,393,378,407,382,374,382,392,378,381,376,375,378,378,384,382,380,393,380,381,383,378,383,379,378,384,390,377,379,375,389,394,377,378,386,380,390,380,378,379,397,376,382,383,392,376,378,376,385,393,388,379,383,397,379,371,381,385,382,379,377,377,377,378,377,382,372,392,382,376,381,380,382,380,378,377,389,380,380,382,397,386,387,381,380,386,382,382,379,377,377,391,378,379,380,390,382,378,373,394,384,378,378,394,377,377,375,392,381,379,384,383,384,379,377,387,395,378,374,378,385,376,381,375,394,381,384,383,388,379,382,401,372,374,376,391,383,377,379,394,383,390,381,379,378,378,399,380,377,384,396,389,377,375,406,385,425,381,382,379,379,396,387,376,379,404,378,386,379,392,381,382,382,394,394,379,381,377,391,388,375,379,378,396,385,387,390,392,380,390,382,384,383,379,382,383,396,377,401,382,384,380,394,396,387,384,377,391,382,381,376,377,377,376,375,380,396,378,392,384,391,373,374,364,393,415,472,547,660,749,884,1008,1160,1262,1358,1435,1461,1493,1518,1533,1549,1557,1558,1565,1555,1526,1466,1343,1217,1098,962,833,695,589,512,474,417,392,397,410,386,389,382,393,377,376,376,383,384,384,376,379,397,390,383,383,386,397,380,385,384,399,381,408,390,381,376,383,378,381,387,382,386,384,380,386,397,385,385,383,391,398,386,382,383,401,387,385,380,391,381,388,380,396,384,385,382,382,391,380,373,379,391,374,383,386,384,392,380,385,381,401,384,389,388,402,381,382,385,395,383,386,385,391,389,381,382,395,383,384,398,384,382,378,398,389,384,380,394,380,378,379,394,381,383,385,380,377,400,381,384,383,392,384,379,380,378,378,380,381,384,389,383,383,381,387,391,385,384,384,392,379,384,379,398,383,383,381,394,385,390,381,388,392,384,397,386,398,376,379,377,381,383,382,378,384,388,375,381,383,390,378,386,374,385,374,367,364,388,412,486,624,764,944,1164,1409,1573,1719,1805,1879,1906,1927,1926,1952,1956,2004,2043,2064,2088,2056,1946,1800,1603,1394,1135,925,758,642,514,445,407,404,407,401,393,384,397,379,383,373,379,391,381,386,395,395,387,392,392,401,384,382,381,383,402,390,376,387,382,394,384,396,384,388,383,399,383,382,385,381,388,393,385,384,391,396,375,382,389,384,400,380,384,380,384,390,394,387,382,378,392,397,381,381,388,397,389,380,384,394,381,385,385,384,384,378,387,383,387,379,387,392,383,412,409,414,410,392,381,381,380,417,417,376,379,383,388,385,383,380,380,404,379,379,378,397,384,385,381,397,384,389,379,392,382,388,380,398,383,383,376,386,398,382,382,377,388,387,380,382,383,395,379,384,381,400,384,382,383,382,390,389,384,392,383,383,396,381,380,379,401,381,385,381,389,395,382,378,392,399,379,381,380,383,394,383,383,376,399,394,378,383,388,391,378,378,378,380,384,383,383,397,384,379,391,397,381,384,389,400,384,383,385,383,404,388,382,386,398,388,382,412,379,383,380,402,385,381,384,399,389,383,376,394,389,380,383,398,381,380,378,384,383,384,381,389,385,388,380,392,378,397,381,383,378,395,382,380,381,405,391,384,387,403,394,383,372,392,384,387,379,382,384,380,380,389,393,379,382,374,388,396,379,377,379,394,385,411,383,376,374,374,371,376,415,469,554,620,782,881,1015,1152,1248,1332,1380,1426,1438,1452,1455,1462,1475,1488,1502,1507,1478,1424,1339,1230,1088,938,793,680,594,504,442,403,424,398,393,376,412,377,382,392,394,376,381,382,396,390,383,419,417,390,394,386,386,386,387,416,412,413,417,412,411,410,407,415,418,417,419,375,407,407,420,467,516,578,641,758,903,997,1128,1241,1373,1408,1485,1474,1480,1491,1518,1551,1567,1574,1582,1518,1449,1370,1261,1177,1004,868,755,645,553,482,433,407,391,438,430,418,422,418,416,426,417,412,418,419,423,415,422,423,422,423,425,421,424,427,424,420,417,420,419,419,420,416,422,423,423,419,421,418,420,407,437,478,540,618,714,837,965,1125,1243,1344,1414,1461,1496,1519,1533,1547,1551,1573,1587,1591,1585,1553,1488,1394,1270,1136,980,838,726,588,507,449,449,392,394,386,426,378,380,439,377,381,378,426,380,384,388,434,389,389,401,426,384,380,385,385,430,382,387,383,385,394,387,384,385,427,383,431,386,386,383,407,385,383,385,382,389,381,384,384,430,383,376,382,425,390,419,380,382,381,384,414,385,384,384,382,394,384,380,383,414,400,380,382,380,420,386,383,384,417,383,383,385,405,377,384,391,401,383,384,384,392,383,384,382,384,387,394,382,385,398,392,384,382,397,380,381,382,398,379,379,377,388,381,382,397,390,434,432,406,380,405,388,381,374,384,386,396,380,381,397,396,381,375,402,383,381,380,383,382,381,380,391,389,381,381,388,404,384,380,387,401,382,375,375,378,385,394,381,380,405,389,382,385,390,382,400,383,410,376,384,380,392,412,408,412,389,389,379,381,384,405,382,387,380,398,375,404,380,380,403,377,385,378,391,396,382,380,375,408,385,378,384,400,378,379,378,407,379,382,378,397,381,376,378,382,397,383,377,376,380,393,378,418,411,421,417,416,424,421,416,405,423,416,422,414,424,419,415,416,411,424,418,421,419,416,418,414,416,426,424,413,410,420,397,394,430,417,421,424,417,373,384,386,417,422,423,424,380,378,377,418,380,382,380,427,374,381,428,425,423,414,418,423,415,427,419,416,420,424,418,423,422,415,418,418,417,412,415,414,422,422,421,422,421,414,421,416,425,424,416,421,425,421,419,418,415,419,423,416,422,419,417,419,423,426,417,419,423,423,421,418,421,426,426,419,421,423,416,425,417,429,425,426,420,421,425,425,423,423,418,418,419,423,417,416,416,414,384,420,418,423,423,418,418,420,419,420,416,419,419,422,419,417,418,423,416,422,425,425,414,421,420,410,429,420,417,419,419,420,426,423,422,418,422,422,420,416,417,421,419,411,421,423,420,415,412,420,420,429,429,428,424,420,423,423,422,423,417,417,423,419,421,472,547,660,749,884,1008,1160,1262,1358,1435,1461,1493,1518,1533,1549,1557,1558,1565,1555,1526,1466,1343,1217,1098,962,833,695,589,501,469,486,624,764,944,1164,1409,1573,1719,1805,1879,1906,1927,1926,1952,1956,2004,2043,2064,2088,2056,1946,1800,1603,1394,1135,925,758,642,502,435,501,570,658,826,928,1064,1179,1267,1356,1392,1427,1441,1460,1456,1455,1469,1495,1508,1500,1454,1397,1307,1180,1038,883,756,661,569,467,455,515,573,626,744,881,975,1103,1219,1353,1396,1480,1471,1475,1490,1522,1548,1564,1576,1579,1521,1467,1419,1279,1193,1029,896,805,656,565,482,437,435,471,525,608,693,819,912,1095,1231,1325,1404,1455,1490,1510,1532,1541,1548,1563,1580,1593,1589,1559,1502,1407,1292,1151,1008,860,735,601,507,449,436,439,434,434,438};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    static int index = 0;

    if (htim->Instance == TIM6) {
        // Update DAC channels
    	printf("%d", values1[index]);
    	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, values1[index]);
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, values1[index]);
        index++;
    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	printf("start\r\n");
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);

  HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	__disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
