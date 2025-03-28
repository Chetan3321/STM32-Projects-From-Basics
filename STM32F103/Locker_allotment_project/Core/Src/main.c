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
#include "rc522.h"
#include "string.h"

#include "ssd1306.h"
#include "fonts.h"
#include "stdio.h"
#include "bitmap.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Predefined card IDs (in hexadecimal format)
//#define CARD_USER1 "\x83\x31\x84\xE4\xD2"  // Card 1 (Access Allowed)
//#define CARD_USER2 "\x93\x20\x68\xA3\x7C"  // Card 2 (Access Allowed)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t status;
uint8_t str[MAX_LEN]; // Max_LEN = 16
uint8_t sNum[5];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(LOCKER1_GPIO_Port, LOCKER1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LOCKER2_GPIO_Port, LOCKER2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LOCKER3_GPIO_Port, LOCKER3_Pin, GPIO_PIN_RESET);

  	MFRC522_Init();

	SSD1306_Init (); // initialise the display
	SSD1306_GotoXY (10,10); // goto 10, 10
	SSD1306_Puts ("HELLO", &Font_11x18, 1); // print Hello
	SSD1306_GotoXY (10, 28);
	SSD1306_Puts ("Locker", &Font_11x18, 1);
	SSD1306_GotoXY (10, 45);
	SSD1306_Puts ("Allotment", &Font_11x18, 1);
    SSD1306_UpdateScreen(); // update screen
    HAL_Delay(2000);

    SSD1306_Clear();
    SSD1306_UpdateScreen(); // update screen


//  int num = 123456; float flt = 123.45;
//  char bufnum[7]; char bufflt[7];
//  SSD1306_Init (); // initialise the display
//  sprintf (bufnum, "%d", num);
//  sprintf (bufflt, "%.2f", flt);
//  SSD1306_GotoXY (10,10); // goto 10, 10
//  SSD1306_Puts (bufnum, &Font_11x18, 1); // print Hello
//  SSD1306_GotoXY (10, 30);
//  SSD1306_Puts (bufflt, &Font_11x18, 1);
//  SSD1306_UpdateScreen(); // update screen

//  SSD1306_Init();
//  SSD1306_DrawBitmap(0, 0, logo, 128, 64, 1);
//  SSD1306_UpdateScreen(); // update screen


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
 	  status = MFRC522_Request(PICC_REQIDL, str);
	  status = MFRC522_Anticoll(str);
	  memcpy(sNum, str, 5);
	  HAL_Delay(100);
	  HAL_Delay(100);
	  	SSD1306_GotoXY (10, 10);
		SSD1306_Puts ("Scan", &Font_11x18, 1);
		SSD1306_GotoXY (10, 28);
		SSD1306_Puts ("Your", &Font_11x18, 1);
		SSD1306_GotoXY (10, 45);
		SSD1306_Puts ("Card", &Font_11x18, 1);
		SSD1306_UpdateScreen(); // update screen

	 if(strcmp(sNum, "\x83\x31\x84\xE4\xD2") == 0)
	 {
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

		 SSD1306_GotoXY (10, 10);
		 SSD1306_Puts (" User 1 ", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 28);
		 SSD1306_Puts (" Access", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 45);
		 SSD1306_Puts (" Alloted", &Font_11x18, 1);
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);

		 HAL_GPIO_WritePin(LOCKER1_GPIO_Port, LOCKER1_Pin, GPIO_PIN_SET);
		 HAL_Delay(2000);
		 HAL_GPIO_WritePin(LOCKER1_GPIO_Port, LOCKER1_Pin, GPIO_PIN_RESET);
		 HAL_Delay(1000);
		 memset(sNum, 0, sizeof(sNum));
		 memset(str, 0, sizeof(str));

		 SSD1306_Clear();
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	 }
	 else if(strcmp(sNum, "\x93\x20\x68\xA3\x7C") == 0)
	 {
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		 SSD1306_GotoXY (10, 10);
		 SSD1306_Puts (" User 2 ", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 28);
		 SSD1306_Puts (" Access", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 45);
		 SSD1306_Puts (" Alloted", &Font_11x18, 1);
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);

		 HAL_GPIO_WritePin(LOCKER2_GPIO_Port, LOCKER2_Pin, GPIO_PIN_SET);
		 HAL_Delay(2000);
		 HAL_GPIO_WritePin(LOCKER2_GPIO_Port, LOCKER2_Pin, GPIO_PIN_RESET);
		 HAL_Delay(1000);
		 memset(sNum, 0, sizeof(sNum));
		 memset(str, 0, sizeof(str));

		 SSD1306_Clear();
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	 }
	 else if(strcmp(sNum, "\x2D\x5F\x92\x00\xE0") == 0)
	 {
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		 SSD1306_GotoXY (10, 10);
		 SSD1306_Puts (" User 3 ", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 28);
		 SSD1306_Puts (" Access", &Font_11x18, 1);
		 SSD1306_GotoXY (10, 45);
		 SSD1306_Puts (" Alloted", &Font_11x18, 1);
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);

		 HAL_GPIO_WritePin(LOCKER3_GPIO_Port, LOCKER3_Pin, GPIO_PIN_SET);
		 HAL_Delay(2000);
		 HAL_GPIO_WritePin(LOCKER3_GPIO_Port, LOCKER3_Pin, GPIO_PIN_RESET);
		 HAL_Delay(1000);
		 memset(sNum, 0, sizeof(sNum));
		 memset(str, 0, sizeof(str));

		 SSD1306_Clear();
		 SSD1306_UpdateScreen(); // update screen
		 HAL_Delay(100);
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	 }
	 else if((sNum[0] != 0) && (sNum[1] != 0) && (sNum[2] != 0) && (sNum[3] != 0) && (sNum[4] != 0))
	 {
		 if((strcmp(sNum, "\x93\x20\x68\xA3\x7C") == 0) || (strcmp(sNum, "\x83\x31\x84\xE4\xD2") == 0))
		 {
			 SSD1306_GotoXY (10, 10);
			 SSD1306_Puts ("        ", &Font_11x18, 1);
			 SSD1306_GotoXY (10, 28);
			 SSD1306_Puts (" Access", &Font_11x18, 1);
			 SSD1306_GotoXY (10, 45);
			 SSD1306_Puts (" Denied ", &Font_11x18, 1);
			 SSD1306_UpdateScreen(); // update screen
			 HAL_Delay(1000);
			 memset(sNum, 0, sizeof(sNum));
			 memset(str, 0, sizeof(str));

		 }
	 }
	 else
	 {
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		 memset(sNum, 0, sizeof(sNum));
		 memset(str, 0, sizeof(str));
	 }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LOCKER1_Pin|LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|LOCKER2_Pin|LOCKER3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LOCKER1_Pin LED_Pin */
  GPIO_InitStruct.Pin = LOCKER1_Pin|LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 LOCKER2_Pin LOCKER3_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|LOCKER2_Pin|LOCKER3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
