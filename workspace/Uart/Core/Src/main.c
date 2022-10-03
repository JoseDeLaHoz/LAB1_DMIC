/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retarget.h"
#include "funciones.h"

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

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
int main(void) {
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
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */
	RetargetInit(&huart3);
	//char nombre[20];
	char buf[10];
	uint8_t receive[16] = { 0 };
	uint8_t seed[16] = { 0 };
	uint8_t pol[] = { 1, 0, 1, 0, 0 };
	uint8_t aux[] = { 0, 0, 0, 0, 0 };
	uint8_t xor[16] = { 0 };
	uint8_t buff[4];
	//uint8_t sp[] = {"\n\r"};

	Saludo();

	printf("\n\rNumero de bits termino de realimentacion\n\r");
	scanf("%s", buf);
	//printf("\n\rUART_Transmit ");
	//HAL_UART_Transmit(&huart3, (uint8_t *)buf, sizeof(buf), HAL_MAX_DELAY);
	int numbits = atoi(buf);
	printf("\n\rNumero de bits - Decimals: %d\n\r", numbits);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	for (int w = 0; w < numbits ; w++) {
		aux[w] = pol[numbits - 1 - w];
	}

	for (int w = 0; w < numbits ; w++) {
		pol[w] = aux[w];
	}

	while (1) {

		printf("\n\rIngrese el numero de la semilla de %d bits en binario\n\r", numbits);
		if (!HAL_UART_Receive(&huart3, (uint8_t*) receive, numbits, HAL_MAX_DELAY)) {

			for (int i = 0; (i <= 15); i++) {
				seed[i] = (receive[i] - 48);
			}
		}

		printf("\n\r");
		//////////////////////////////////////////////////////
		int k = 0;
		while (k < 32) {
			for (int i = 0; (i < numbits); i++) {
				if (pol[i] == 1) {
					xor[i] = seed[i];
				} else {
					xor[i] = 0;
				}
				//printf("\n\r%d",i);
				//printf("\n\r%d",xor[i]);
			}
			////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////
			uint8_t res = 0;
			for (int i = 0; (i < numbits); i++) {
				res = res + xor[i];
			}
			///////////////////////////////////////////////////////////////////////////////////

			// HAL_UART_Transmit(&huart3, &res, sizeof(res), HAL_MAX_DELAY);//envia el valor de la suma para determinar valor XOR

			////////DETERMINAMOS SI ES PAR O IMPAR////////////////////////////////

			if (res % 2 == 0) {
				res = 0;
			} else {
				res = 1;
			}
			//printf("\n\r%d",res);
			///////////////////////////////////////////////
			// HAL_UART_Transmit(&huart3, &res, sizeof(res), HAL_MAX_DELAY);
			///mover y poner el valor xor en la cabeza

			for (int i = numbits-1; i > 0; i--) {
				seed[i] = seed[i-1];
			}

			//seed[4] = seed[3];
			//seed[3] = seed[2];
			//seed[2] = seed[1];
			//seed[1] = seed[0];
			seed[0] = res;

			//uint8_t usr = 16 * seed[0] + 8 * seed[1] + 4 * seed[2] + 2 * seed[3]+ seed[4];

			int usr = 16 * seed[0] + 8 * seed[1] + 4 * seed[2] + 2 * seed[3] + seed[4];
			itoa(usr, (char*) buff, 16);
			printf("\n\r%s",buff);
			//HAL_UART_Transmit(&huart3, buff, sizeof(buff), HAL_MAX_DELAY);
			//HAL_UART_Transmit(&huart3, sp, sizeof(sp), HAL_MAX_DELAY);
			HAL_Delay(1000);

			k++;
		}

		//HAL_UART_Transmit(&huart3, seed, 16, HAL_MAX_DELAY);
		//HAL_UART_Transmit(&huart3, &seed[0], 1, HAL_MAX_DELAY);
		//HAL_UART_Transmit(&huart3, &seed[1], 1, HAL_MAX_DELAY);
		//HAL_UART_Transmit(&huart3, &seed[2], 1, HAL_MAX_DELAY);
		//HAL_UART_Transmit(&huart3, &seed[3], 1, HAL_MAX_DELAY);
	}

	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 96;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
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
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
