/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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

/* DUAL_CORE_BOOT_SYNC_SEQUENCE: Define for dual core boot synchronization    */
/*                             demonstration code based on hardware semaphore */
/* This define is present in both CM7/CM4 projects                            */
/* To comment when developping/debugging on a single core                     */
#define DUAL_CORE_BOOT_SYNC_SEQUENCE

#if defined(DUAL_CORE_BOOT_SYNC_SEQUENCE)
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
#endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

FDCAN_HandleTypeDef hfdcan1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_FDCAN1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

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
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
#if defined(DUAL_CORE_BOOT_SYNC_SEQUENCE)
  int32_t timeout;
#endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */
       /* USER CODE END Boot_Mode_Sequence_0 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
#if defined(DUAL_CORE_BOOT_SYNC_SEQUENCE)
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0))
    ;
  if (timeout < 0)
  {
    Error_Handler();
  }
#endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */
       /* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
#if defined(DUAL_CORE_BOOT_SYNC_SEQUENCE)
  /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
  HSEM notification */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /*Take HSEM */
  HAL_HSEM_FastTake(HSEM_ID_0);
  /*Release HSEM in order to notify the CPU2(CM4)*/
  HAL_HSEM_Release(HSEM_ID_0, 0);
  /* wait until CPU2 wakes up from stop mode */
  timeout = 0xFFFF;
  while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0))
    ;
  if (timeout < 0)
  {
    Error_Handler();
  }
#endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */
       /* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

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

  /** Supply configuration update enable
   */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
   */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
  {
  }

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 3072;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief FDCAN1 Initialization Function - ADVANCED CAN-FD PERIPHERAL (STM32H7)
 * @details This is the newer FDCAN peripheral that supports both Classic CAN and CAN-FD
 * @note Much more sophisticated than classic CAN peripheral found in STM32F4
 * @param None
 * @retval None
 */
static void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */

  // =============================================================================
  // ADVANCED FDCAN PERIPHERAL CONFIGURATION (STM32H7)
  // =============================================================================

  hfdcan1.Instance = FDCAN1; // Use FDCAN1 hardware peripheral

  // -----------------------------------------------------------------------------
  // FRAME FORMAT AND MODE CONFIGURATION
  // -----------------------------------------------------------------------------
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC; // Use Classic CAN frames (not CAN-FD)
                                                  // Could be FDCAN_FRAME_FD_BRS for CAN-FD
                                                  // or FDCAN_FRAME_FD_NO_BRS for CAN-FD without bit rate switching

  hfdcan1.Init.Mode = FDCAN_MODE_INTERNAL_LOOPBACK; // Internal loopback for testing
                                                    // TX messages are internally routed to RX
                                                    // Perfect for learning without external CAN bus

  hfdcan1.Init.AutoRetransmission = ENABLE; // ✅ Automatically retry failed transmissions
                                            // Much better than course's DISABLE!
                                            // Essential for reliable CAN communication

  hfdcan1.Init.TransmitPause = DISABLE; // No pause between transmissions
                                        // Allows back-to-back message sending

  hfdcan1.Init.ProtocolException = DISABLE; // Handle protocol exceptions in normal way
                                            // Advanced CAN-FD feature, not needed for Classic CAN

  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; // Use FIFO mode for TX buffer
                                                          // Messages sent in order (First In, First Out)
                                                          // Alternative: FDCAN_TX_QUEUE_OPERATION (priority-based)
                                                          // NOTE: QUEUE mode is usually better for real CAN networks
                                                          // because it respects CAN message priorities (lower ID = higher priority)
                                                          // But in loopback mode for learning, both work the same

  // -----------------------------------------------------------------------------
  // NOMINAL BIT TIMING (for Classic CAN data)
  // These settings create the timing for each CAN bit
  // 50MHz FDCAN Clock ÷ Prescaler = Time Quantum frequency
  // -----------------------------------------------------------------------------
  hfdcan1.Init.NominalPrescaler = 5; // Clock prescaler: 50MHz ÷ 5 = 10MHz
                                     // Time Quantum (Tq) = 1/10MHz = 100ns

  hfdcan1.Init.NominalSyncJumpWidth = 1; // Synchronization Jump Width: 1 Tq
                                         // Used for bit timing resynchronization
                                         // Can be 1-4 Tq, 1 is most common

  hfdcan1.Init.NominalTimeSeg1 = 16; // Time Segment 1: 16 Tq
                                     // Includes Propagation Segment + Phase Segment 1
                                     // This is where the CAN controller samples the bit

  hfdcan1.Init.NominalTimeSeg2 = 3; // Time Segment 2: 3 Tq (Phase Segment 2)
                                    // Buffer time after sampling, before next bit

  // CALCULATION VERIFICATION:
  // Total Bit Time = 1(Sync) + 16(TimeSeg1) + 3(TimeSeg2) = 20 Time Quanta
  // Bit Rate = 10MHz ÷ 20 = 500,000 bps = 500 kbps ✅
  // Sample Point = (1 + 16) ÷ 20 = 17/20 = 85% (excellent for CAN!)
  // Optimal sample point is 80-90%, so 85% is perfect!

  // -----------------------------------------------------------------------------
  // DATA BIT TIMING (for CAN-FD fast data phase - UNUSED in Classic CAN mode)
  // These settings would be used if we switched to CAN-FD mode later
  // -----------------------------------------------------------------------------
  hfdcan1.Init.DataPrescaler = 1;     // Fast data prescaler (not used in Classic CAN)
  hfdcan1.Init.DataSyncJumpWidth = 1; // Fast data sync jump width (not used)
  hfdcan1.Init.DataTimeSeg1 = 1;      // Fast data time segment 1 (not used)
  hfdcan1.Init.DataTimeSeg2 = 1;      // Fast data time segment 2 (not used)

  // -----------------------------------------------------------------------------
  // MESSAGE RAM CONFIGURATION - Advanced flexible buffer management
  // This is much more sophisticated than classic CAN fixed FIFOs!
  // -----------------------------------------------------------------------------
  hfdcan1.Init.MessageRAMOffset = 0; // Start at beginning of Message RAM
                                     // FDCAN has configurable memory layout

  // FILTER CONFIGURATION - Controls which messages are accepted
  hfdcan1.Init.StdFiltersNbr = 0; // Number of Standard ID filters (11-bit IDs)
                                  // 0 = Accept ALL standard ID messages
  hfdcan1.Init.ExtFiltersNbr = 0; // Number of Extended ID filters (29-bit IDs)
                                  // 0 = Accept ALL extended ID messages
                                  // Perfect for learning - no message filtering

  // RECEIVE BUFFER CONFIGURATION - Where incoming messages are stored
  hfdcan1.Init.RxFifo0ElmtsNbr = 2;                  // RX FIFO 0: 2 message elements
                                                     // This is where loopback messages will be received
                                                     // 2 elements = can store 2 messages before overflow
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8; // Each RX element can hold up to 8 data bytes
                                                     // Standard CAN frame max = 8 bytes ✅

  hfdcan1.Init.RxFifo1ElmtsNbr = 0;                  // RX FIFO 1: Not used (0 elements)
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8; // Size setting (unused since 0 elements)

  hfdcan1.Init.RxBuffersNbr = 0;                  // Dedicated RX buffers: Not used
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8; // RX buffer size (unused)

  // TRANSMIT BUFFER CONFIGURATION - Where outgoing messages are queued
  hfdcan1.Init.TxEventsNbr = 0; // TX Event FIFO: Not used
                                // Would log transmission confirmations

  hfdcan1.Init.TxBuffersNbr = 0; // Dedicated TX buffers: Not used
                                 // We use TX FIFO instead

  hfdcan1.Init.TxFifoQueueElmtsNbr = 32; // TX FIFO Queue: 32 message elements
                                         // Can queue up to 32 messages for transmission
                                         // Much larger than classic CAN's 3 TX mailboxes!

  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8; // Each TX element holds up to 8 data bytes
                                                // Perfect for Classic CAN (max 8 bytes per frame)

  // Initialize the FDCAN peripheral with all these settings
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler(); // Handle initialization error
  }

  /* USER CODE BEGIN FDCAN1_Init 2 */
  // TODO: Add filter configuration, start FDCAN, and implement TX/RX functions here
  // Example next steps:
  // 1. HAL_FDCAN_ConfigFilter() - if you want message filtering
  // 2. HAL_FDCAN_Start() - to start the FDCAN peripheral
  // 3. HAL_FDCAN_AddMessageToTxFifoQ() - to send messages
  // 4. HAL_FDCAN_GetRxMessage() - to receive messages
  /* USER CODE END FDCAN1_Init 2 */
}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
   */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

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
#endif /* USE_FULL_ASSERT */
