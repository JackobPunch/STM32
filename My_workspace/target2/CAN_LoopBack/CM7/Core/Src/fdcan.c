/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    fdcan.c
 * @brief   This file provides code for the configuration
 *          of the FDCAN instances.
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
#include "fdcan.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;

/**
 * @brief FDCAN1 Initialization Function - ADVANCED CAN-FD PERIPHERAL (STM32H7)
 * @details This configures the FDCAN1 peripheral for Classic CAN operation in loopback mode
 * @note Generated as separate file - good practice for modular code organization
 * @param None
 * @retval None
 */
void MX_FDCAN1_Init(void)
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
                                            // Essential for reliable CAN communication
                                            // Much better than disabling this!

  hfdcan1.Init.TransmitPause = DISABLE; // No pause between transmissions
                                        // Allows back-to-back message sending

  hfdcan1.Init.ProtocolException = DISABLE; // Handle protocol exceptions in normal way
                                            // Advanced CAN-FD feature, not needed for Classic CAN

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

  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; // Use FIFO mode for TX buffer
                                                          // Messages sent in order (First In, First Out)
                                                          // Alternative: FDCAN_TX_QUEUE_OPERATION (priority-based)
                                                          // QUEUE mode is usually better for real CAN networks

  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8; // Each TX element holds up to 8 data bytes
                                                // Perfect for Classic CAN (max 8 bytes per frame)

  // Initialize the FDCAN peripheral with all these settings
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler(); // Handle initialization error
  }

  /* USER CODE BEGIN FDCAN1_Init 2 */
  // NOTE: FDCAN is now initialized but NOT started yet!
  // You'll need to call these HAL functions (which are already provided) in main.c:
  //
  // 1. HAL_FDCAN_Start(&hfdcan1) - Start the FDCAN peripheral (call this in main())
  // 2. HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, data) - Send CAN messages
  // 3. HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &RxHeader, data) - Receive CAN messages
  // 4. HAL_FDCAN_ConfigFilter(&hfdcan1, &filterConfig) - Optional: configure message filters
  //
  // These functions exist in stm32h7xx_hal_fdcan.c - you don't need to implement them!
  // You just need to CALL them with proper parameters in your main application code.
  /* USER CODE END FDCAN1_Init 2 */
}

/**
 * @brief FDCAN1 MSP (MCU Support Package) Initialization
 * @details This function configures the hardware resources for FDCAN1:
 *          - Clock configuration (PLL-based FDCAN clock)
 *          - GPIO configuration (PD0=RX, PD1=TX with alternate function)
 *          - Called automatically by HAL_FDCAN_Init()
 * @param fdcanHandle: FDCAN handle pointer
 * @retval None
 */
void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (fdcanHandle->Instance == FDCAN1)
  {
    /* USER CODE BEGIN FDCAN1_MspInit 0 */

    /* USER CODE END FDCAN1_MspInit 0 */

    // ---------------------------------------------------------------------------
    // FDCAN CLOCK CONFIGURATION - Set up the clock source for FDCAN peripheral
    // ---------------------------------------------------------------------------
    /** Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;   // Configure FDCAN clock
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL; // Use PLL as FDCAN clock source
                                                                      // This gives us the 50MHz FDCAN clock
                                                                      // Alternative sources: HSE, PLL2, etc.
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler(); // Handle clock configuration error
    }

    // -------------------------------------------------------------------------
    // PERIPHERAL CLOCK ENABLE - Enable clocks for FDCAN and GPIO
    // -------------------------------------------------------------------------
    __HAL_RCC_FDCAN_CLK_ENABLE(); // Enable FDCAN1 peripheral clock
                                  // Must be enabled before using FDCAN registers

    __HAL_RCC_GPIOD_CLK_ENABLE(); // Enable GPIOD clock for PD0 and PD1 pins
                                  // Required before configuring any GPIOD pins

    // -------------------------------------------------------------------------
    // GPIO CONFIGURATION - Configure pins for FDCAN communication
    // -------------------------------------------------------------------------
    /**FDCAN1 GPIO Configuration for NUCLEO-H755ZI-Q board
    PD0     ------> FDCAN1_RX  (Receive pin - input from CAN bus)
    PD1     ------> FDCAN1_TX  (Transmit pin - output to CAN bus)
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1; // Configure both PD0 and PD1
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        // Alternate Function Push-Pull mode
                                                   // AF = controlled by peripheral (FDCAN)
                                                   // PP = push-pull output (strong drive)
    GPIO_InitStruct.Pull = GPIO_NOPULL;            // No internal pull-up/pull-down
                                                   // CAN bus has its own termination
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;   // Low speed is sufficient for CAN
                                                   // CAN max speed << GPIO max speed
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;   // Alternate Function 9 = FDCAN1
                                                   // This connects PD0/PD1 to FDCAN1 peripheral
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);        // Apply GPIO configuration

    /* USER CODE BEGIN FDCAN1_MspInit 1 */
    // Add custom MSP initialization code here if needed
    // Examples: Additional GPIO setup, interrupt configuration, DMA setup
    /* USER CODE END FDCAN1_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *fdcanHandle)
{

  if (fdcanHandle->Instance == FDCAN1)
  {
    /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

    /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_FDCAN_CLK_DISABLE();

    /**FDCAN1 GPIO Configuration
    PD0     ------> FDCAN1_RX
    PD1     ------> FDCAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1);

    /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

    /* USER CODE END FDCAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
