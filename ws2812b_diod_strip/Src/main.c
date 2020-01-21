
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_host.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "stm32f4xx_hal.h"
#include "../Drivers/STM32F4Discovery/Inc/stm32f411e_discovery_accelerometer.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

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
	 extern void initialise_monitor_handles(void);
	 initialise_monitor_handles();
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
  MX_I2S2_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */

  volatile uint8_t err_res = BSP_ACCELERO_Init();
    if (err_res != HAL_OK)
    {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
      /* Initialization Error */
      while(1){
      }
    }
    void delay_asm(uint32_t useconds) {
    	asm volatile("   mov r0, %[useconds]    \n"
    			"1: subs r0, #1            \n"
    			"   bhi 1b                 \n": :[useconds] "r" (useconds): "r0");
    }

    inline void send_byte(int a) {
    	for (int i = 7; i >= 0; i--) {
    		int x = (a >> i) & 1;
    		if (x == 1) {
    			GPIOB->BSRR = GPIO_PIN_8;
    			delay_asm(20); //high_delay
    			GPIOB->BSRR = (uint32_t) GPIO_PIN_8 << 16U;
    			delay_asm(10); //low delay
    		} else {
    			GPIOB->BSRR = GPIO_PIN_8;
    			delay_asm(10); //low delay
    			GPIOB->BSRR = (uint32_t) GPIO_PIN_8 << 16U;
    			delay_asm(20);//high_delay

    		}
    	}
    }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    int16_t buffer[3] = {0};
    int16_t prev_buffer[3] = {0};
    BSP_ACCELERO_GetXYZ(prev_buffer);
    int shaking = 0;
    int change = 0;
    while (1)
    {
     BSP_ACCELERO_GetXYZ(buffer);
     if (abs(buffer[0] - prev_buffer[0]) > 2500 || abs(buffer[1] - prev_buffer[1]) > 2500 || abs(buffer[2] - prev_buffer[2]) > 2500) {
    	 if (!shaking) {
    		 change = 1;
    	 } else {
    		 change = 0;
    	 }
    	 shaking = 1;
     } else {
    	 if (shaking) {
    		 change = -1;
    	 } else {
    		 change = 0;
    	 }
    	 shaking = 0;
     }
     if (change == 1) {
    	 for (int j = 0; j < 60; j++) {
			 for (int i = 0; i < 60; i++) {
											send_byte(0x00 + j);
											send_byte(0x3C - j);
											send_byte(0x00);
					 }
			 HAL_Delay(2);
    	 }
     } else if (change == -1) {
    	 for (int j = 0; j < 60; j++) {
    	 			 for (int i = 0; i < 60; i++) {
    	 											send_byte(0x3C - j);
    	 											send_byte(0x00 + j);
    	 											send_byte(0x00);
    	 					 }
    	 			 HAL_Delay(2);
    	     	 }
     }
     if (shaking) {
		 for (int i = 0; i < 60; i++) {
								send_byte(0x3C);
								send_byte(0x00);
								send_byte(0x00);
		 }
     } else {
    	 for (int i = 0; i < 60; i++) {
    	 						send_byte(0x00);
    	 						send_byte(0x3C);
    	 						send_byte(0x00);
    	 }

     }

     for (int i = 0; i < 3; i++) {
    	 prev_buffer[i] = buffer[i];
     }

     HAL_Delay(300);

    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */


  /* USER CODE END 3 */
}}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
