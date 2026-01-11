/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
CAN_HandleTypeDef hcan1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
void CAN1_TX(void);
void CAN1_Rx(void);
void CAN_Filter_Config(void);
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
  MX_CAN1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  CAN_Filter_Config(); // Configure CAN filters

  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    CAN1_Tx();
    HAL_Delay(1000); // Wait 1 second between messages

    CAN1_Rx();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief CAN1 Initialization Function
 * @param None
 * @retval None
 */
/**
 * @brief CAN1 Initialization Function - CLASSIC CAN PERIPHERAL (STM32F4)
 * @details This is the older CAN peripheral found in STM32F4 series
 * @note Uses simpler configuration compared to FDCAN
 * @param None
 * @retval None
 */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */

  // =============================================================================
  // CLASSIC CAN PERIPHERAL CONFIGURATION (STM32F4)
  // =============================================================================

  hcan1.Instance = CAN1; // Use CAN1 hardware peripheral

  // -----------------------------------------------------------------------------
  // BIT TIMING CONFIGURATION - Creates the CAN bit timing
  // -----------------------------------------------------------------------------
  hcan1.Init.Prescaler = 16; // Clock prescaler: CAN_Clock / 16
                             // With 42MHz APB1: 42MHz/16 = 2.625MHz
                             // Time Quantum (Tq) = 1/2.625MHz = 380ns

  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ; // Sync Jump Width: 1 Time Quantum
                                          // Used for resynchronization

  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ; // Bit Segment 1: 8 Time Quanta
                                     // Includes Propagation + Phase Seg1
                                     // This is where bit sampling occurs

  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ; // Bit Segment 2: 1 Time Quantum
                                     // Phase Segment 2 (after sampling)

  // TOTAL BIT TIME = 1(Sync) + 8(TimeSeg1) + 1(TimeSeg2) = 10 Time Quanta
  // Bit Rate = 2.625MHz / 10 = 262.5 kbps
  // Sample Point = (1 + 8) / 10 = 90% (very late sampling)

  // -----------------------------------------------------------------------------
  // OPERATIONAL MODE CONFIGURATION
  // -----------------------------------------------------------------------------
  hcan1.Init.Mode = CAN_MODE_NORMAL; // Normal CAN operation mode
                                     // NOTE: Course uses LOOPBACK in software!

  // -----------------------------------------------------------------------------
  // ADVANCED FEATURES (mostly disabled for simplicity)
  // -----------------------------------------------------------------------------
  hcan1.Init.TimeTriggeredMode = DISABLE;  // No time-triggered transmission
  hcan1.Init.AutoBusOff = DISABLE;         // No automatic bus-off recovery
  hcan1.Init.AutoWakeUp = DISABLE;         // No automatic wake-up from sleep
  hcan1.Init.AutoRetransmission = DISABLE; // No automatic retransmission on error
                                           // NOTE: Usually should be ENABLED!

  // -----------------------------------------------------------------------------
  // FIFO CONFIGURATION
  // -----------------------------------------------------------------------------
  hcan1.Init.ReceiveFifoLocked = DISABLE;    // RX FIFO overwrites old messages
  hcan1.Init.TransmitFifoPriority = DISABLE; // TX priority by message ID, not FIFO order

  // Initialize the CAN peripheral with these settings
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler(); // Handle initialization error
  }

  /* USER CODE BEGIN CAN1_Init 2 */
  // NOTE: Course adds filter configuration and loopback mode here
  /* USER CODE END CAN1_Init 2 */
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

void CAN1_TX(void)
{
  char msg[50];

  CAN_TxHeaderTypeDef TxHeader;

  uint32_t TxMailbox;

  uint8_t TxData[5] = {'H', 'E', 'L', 'L', 'O'};

  TxHeader.DLC = 5;
  TxHeader.StdId = 0x65;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_DATA;

  if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
  {
    Error_Handler();
  }

  while (HAL_CAN_IsTxMessagePending(&hcan1, TxMailbox))
    ;

  sprintf(msg, "Message Transmitted\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

void CAN1_Rx(void)
{
  char msg[50];

  CAN_RxHeaderTypeDef RxHeader;

  uint8_t RxData[5];

  while (!HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0))
  {
    // Wait for message to be received
  };

  if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    Error_Handler();
  }

  sprintf(msg, "Message Received: %s\r\n", RxData);
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

void CAN_Filter_Config(void)
{
  CAN_FilterTypeDef canfilterconfig;

  canfilterconfig.FilterActivation = ENABLE;
  canfilterconfig.FilterBank = 0;
  canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  canfilterconfig.FilterIdHigh = 0x0000;
  canfilterconfig.FilterIdLow = 0x0000;
  canfilterconfig.FilterMaskIdHigh = 0x0000;
  canfilterconfig.FilterMaskIdLow = 0x0000;
  canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canfilterconfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig) != HAL_OK)
  {
    Error_Handler();
  }
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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

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

#ifdef USE_FULL_ASSERT
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
#endif /* USE_FULL_ASSERT */\n\n /*\n================================================================================\nFOR COMPARISON: YOUR STM32H7 FDCAN1 CONFIGURATION WITH DETAILED COMMENTS\n================================================================================\n\n**\n  * @brief FDCAN1 Initialization Function - ADVANCED CAN-FD PERIPHERAL (STM32H7)\n  * @details This is the newer FDCAN peripheral that supports both Classic CAN and CAN-FD\n  * @note Much more sophisticated than classic CAN peripheral\n  * @param None\n  * @retval None\n  *\nstatic void MX_FDCAN1_Init(void)\n{\n  // =============================================================================\n  // ADVANCED FDCAN PERIPHERAL CONFIGURATION (STM32H7)\n  // =============================================================================\n  \n  hfdcan1.Instance = FDCAN1;                        // Use FDCAN1 hardware peripheral\n  \n  // -----------------------------------------------------------------------------\n  // FRAME FORMAT AND MODE CONFIGURATION\n  // -----------------------------------------------------------------------------\n  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;   // Use Classic CAN frames (not CAN-FD)\n                                                     // Could be FDCAN_FRAME_FD_BRS for CAN-FD\n  \n  hfdcan1.Init.Mode = FDCAN_MODE_INTERNAL_LOOPBACK; // Internal loopback for testing\n                                                     // TX -> RX internally, no external bus\n  \n  hfdcan1.Init.AutoRetransmission = ENABLE;         // ✅ Auto retry on transmission errors\n                                                     // Much better than course's DISABLE!\n  \n  hfdcan1.Init.TransmitPause = DISABLE;             // No pause between transmissions\n  hfdcan1.Init.ProtocolException = DISABLE;         // Handle protocol exceptions normally\n  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; // Use FIFO mode for TX\n  \n  // -----------------------------------------------------------------------------\n  // NOMINAL BIT TIMING (for Classic CAN data)\n  // 50MHz FDCAN Clock with these settings:\n  // -----------------------------------------------------------------------------\n  hfdcan1.Init.NominalPrescaler = 5;                // Clock prescaler: 50MHz/5 = 10MHz\n                                                     // Time Quantum (Tq) = 100ns\n  \n  hfdcan1.Init.NominalSyncJumpWidth = 1;            // Sync Jump Width: 1 Tq\n  hfdcan1.Init.NominalTimeSeg1 = 16;                // Time Segment 1: 16 Tq (prop + phase1)\n  hfdcan1.Init.NominalTimeSeg2 = 3;                 // Time Segment 2: 3 Tq (phase2)\n  \n  // TOTAL BIT TIME = 1(Sync) + 16(TimeSeg1) + 3(TimeSeg2) = 20 Time Quanta\n  // Bit Rate = 10MHz / 20 = 500 kbps\n  // Sample Point = (1 + 16) / 20 = 85% (excellent sampling point!)\n  \n  // -----------------------------------------------------------------------------\n  // DATA BIT TIMING (for CAN-FD fast data phase - not used in Classic mode)\n  // -----------------------------------------------------------------------------\n  hfdcan1.Init.DataPrescaler = 1;                   // Fast data prescaler (unused in Classic)\n  hfdcan1.Init.DataSyncJumpWidth = 1;               // Fast data sync jump (unused)\n  hfdcan1.Init.DataTimeSeg1 = 1;                    // Fast data time seg1 (unused)\n  hfdcan1.Init.DataTimeSeg2 = 1;                    // Fast data time seg2 (unused)\n  \n  // -----------------------------------------------------------------------------\n  // MESSAGE RAM CONFIGURATION - Advanced buffer management\n  // -----------------------------------------------------------------------------\n  hfdcan1.Init.MessageRAMOffset = 0;                // Start at beginning of Message RAM\n  \n  // FILTER CONFIGURATION\n  hfdcan1.Init.StdFiltersNbr = 0;                   // No standard ID filters (accept all)\n  hfdcan1.Init.ExtFiltersNbr = 0;                   // No extended ID filters (accept all)\n  \n  // RECEIVE BUFFER CONFIGURATION\n  hfdcan1.Init.RxFifo0ElmtsNbr = 2;                 // 2 elements in RX FIFO 0\n  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8; // Each element can hold 8 data bytes\n  hfdcan1.Init.RxFifo1ElmtsNbr = 0;                 // RX FIFO 1 not used\n  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;\n  hfdcan1.Init.RxBuffersNbr = 0;                    // No dedicated RX buffers\n  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;\n  \n  // TRANSMIT BUFFER CONFIGURATION\n  hfdcan1.Init.TxEventsNbr = 0;                     // No TX event logging\n  hfdcan1.Init.TxBuffersNbr = 0;                    // No dedicated TX buffers\n  hfdcan1.Init.TxFifoQueueElmtsNbr = 32;            // 32 elements in TX FIFO queue\n  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;     // Each TX element holds 8 data bytes\n  \n  // Initialize the FDCAN peripheral\n  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)\n  {\n    Error_Handler();\n  }\n}\n\n================================================================================\nKEY DIFFERENCES SUMMARY:\n================================================================================\n\n1. PERIPHERAL TYPE:\n   - CAN1 (STM32F4):  Classic CAN only, simpler\n   - FDCAN1 (STM32H7): Advanced, supports Classic CAN + CAN-FD\n\n2. BIT TIMING:\n   - CAN1:    10 Time Quanta total (1+8+1), ~262.5 kbps, 90% sample point\n   - FDCAN1:  20 Time Quanta total (1+16+3), 500 kbps, 85% sample point\n   - FDCAN1 timing is much more robust!\n\n3. LOOPBACK:\n   - CAN1:    Set in software after initialization (in main_app.c)\n   - FDCAN1:  Built into peripheral configuration\n\n4. BUFFER MANAGEMENT:\n   - CAN1:    Fixed hardware FIFOs, simple\n   - FDCAN1:  Configurable Message RAM, very flexible\n\n5. AUTO RETRANSMISSION:\n   - CAN1:    DISABLED (course setting - not recommended!)\n   - FDCAN1:  ENABLED (proper setting for reliability)\n\n6. HAL FUNCTIONS:\n   - CAN1:    HAL_CAN_* functions\n   - FDCAN1:  HAL_FDCAN_* functions\n\n7. FILTERING:\n   - CAN1:    Configured separately with HAL_CAN_ConfigFilter()\n   - FDCAN1:  Built into initialization structure\n\nYour FDCAN1 configuration is much more sophisticated and robust!\n================================================================================\n*/
