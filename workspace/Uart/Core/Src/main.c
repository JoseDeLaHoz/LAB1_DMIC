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
 *
 ******************************************************************************
 ******************************************************************************
 *Autores: Jhan Carlos Reyes
 *Autores: Jose Luis De La Hoz
 *Autores: Esneider Silva
 *
 * El siguiente código presenta un desarrollo en la tarjeta de desarrollo
 * Nucleo - F767zi con un ARM-Cortex M7
 *
 * Consiste en una interfaz de terminar serial por la cual el usuario puede
 * interactuar de manera amigable para la generación de número pseudoaleatorios
 * mediante el uso de desplazamientos y compuertas XOR con determinadas
 * posiciones o taps
 *
 * Dentro de las características del programa está la interfaz antes mencionada
 * que transmite a 9600 bps 8N1. Además de identificar si se optienen periodo
 * máximo durante la generación. Si utiliza una única salida que corresponde al
 * led verde en la tarjeta
 ******************************************************************************
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//Adición de librerías para
// transmisión UART stdio y string
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// cálculos matemáticos (potencia)
#include <math.h>
// incluir las funciones de printf y scanf
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

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
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
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); //Apagar el LED

	RetargetInit(&huart3); // declarar Uart3 (conectado con el stlink)



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



	while (1) {
		char buf_lfsr[10];
			uint8_t receive[32] = { 0 }; // Arreglo para recibir
			uint8_t seed[32] = { 0 };	//Arreglo semilla
			uint8_t seed_init[32] = { 0 }; //Arreglo semilla inicial
			uint8_t pol[32] = { 0 }; // Almacenar polinomio
			uint8_t aux[32] = { 0 }; // Auxiliar para invertir
			uint8_t xor[32] = { 0 }; // Almacena las xor
			uint8_t buffer_lfsr[16]={0};	//Transmitir
			uint8_t band = 1;		//bandera de ciclo max

			//Uso del timer 2 para LED_Blinking
			HAL_TIM_Base_Start(&htim2);
			__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
			int16_t timerLimit = 250;

			//Mensaje de saludo
			Saludo();

			//Etiqueta para reiniciar
			init:
			printf("\n\rNumero de bits termino de realimentacion\n\r");
			scanf("%s", buf_lfsr);
			int numbits = atoi(buf_lfsr);
			printf("\n\rNumero de bits - Decimals: %d\n\r", numbits);

			printf("\n\rIngrese el polinomio de %d bits en binario\n\r", numbits);
			if (!HAL_UART_Receive(&huart3, (uint8_t*) receive, numbits,
					HAL_MAX_DELAY)) {

				for (int i = 0; (i < numbits); i++) {
					pol[i] = (receive[i] - 48);
				}
			}


			///////////

		printf("\n\rIngrese el numero de la semilla de %d bits en binario\n\r",
				numbits);
		if (!HAL_UART_Receive(&huart3, (uint8_t*) receive, numbits, HAL_MAX_DELAY)) {

			//Recibe una semilla del tamaño de bits anteriormente especificado en binario
			for (int i = 0; (i < numbits); i++) {
				seed[i] = (receive[i] - 48);
				seed_init[i] = seed[i];
			}
			band = 1;
			//Convertir de arreglo a byte
			uint64_t usr = 0;
			for (int i = 0; (i < numbits); i++) {
				usr = usr + pow(2, ((numbits - 1) - i)) * seed_init[i];
			}

			uint64_t taps = 0;
			for (int i = 0; (i < numbits); i++) {
				taps = taps + pow(2, (numbits-1)-i) * pol[(numbits-1)-i];
			}


			printf("\n\r\n\r***************************************************************");
			printf("\n\r\t*\t RESUMEN INICIAL DE LA SECUENCIA \t*\n\r");
			printf("***************************************************************");
			printf("\n\rNumero de bits termino de realimentacion: %d \n\r",numbits);
			printf("Funcion de realimentacion: BIN ");

			printf("\n\rNumero de bits termino de realimentacion: %d \n\r",numbits);
			printf("Funcion de realimentacion; ");
			itoa(taps, (char*) buffer_lfsr, 2);
			printf("%s", buffer_lfsr);
			printf(" - ");
			itoa(taps, (char*) buffer_lfsr, 16);
			printf("%s", buffer_lfsr);

			printf("\n\rValor inicial - Semilla : ");
			itoa(usr, (char*) buffer_lfsr, 2);
			printf("%s", buffer_lfsr);
			printf(" - ");
			itoa(usr, (char*) buffer_lfsr, 16);
			printf("%s", buffer_lfsr);

			uint64_t a = pow(2,numbits)-1;
			printf("\n\rTotal de numeros esperados en la secuencia: %llu ", a);
			printf("\r\n");

		}

		printf("\n\r");
		//////////////////////////////////////////////////////
		//Invertir el polinomio de acuerdo con los parámetros establecidos
			for (int w = 0; w < numbits; w++) {
				aux[w] = pol[numbits - 1 - w];
			}

			for (int w = 0; w < numbits; w++) {
				pol[w] = aux[w];
			}

		uint64_t k = 0;
		while (k < pow(2, numbits)) {

			//Revisa si la bandera de interrupción del TIM esta en 1
			if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET) {
				__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE); //Borra la bandera de interrupcion del timer.
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				timerLimit = 250;
			} else if (__HAL_TIM_GET_COUNTER(&htim2) >= timerLimit) {
				timerLimit += 250;
			}

			for (int i = 0; (i < numbits); i++) {
				if (pol[i] == 1) {
					xor[i] = seed[i];
				} else {
					xor[i] = 0;
				}
			}
			////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////
			//Determinar cuantos 1's tiene
			uint64_t res = 0;
			for (int i = 0; (i < numbits); i++) {
				res = res + xor[i];
			}
			///////////////////////////////////////////////////////////////////////////////////

			// Función utilizada en DEBUGG
			// HAL_UART_Transmit(&huart3, &res, sizeof(res), HAL_MAX_DELAY);//envia el valor de la suma para determinar valor XOR

			////////DETERMINAMOS SI ES PAR O IMPAR////////////////////////////////

			if (res % 2 == 0) {
				res = 0;
			} else {
				res = 1;
			}
			///////////////////////////////////////////////
			// HAL_UART_Transmit(&huart3, &res, sizeof(res), HAL_MAX_DELAY);

			///mover y poner el valor xor en la cabeza
			for (int i = numbits - 1; i > 0; i--) {
				seed[i] = seed[i - 1];
			}

			seed[0] = res;

			uint64_t usr = 0;
			for (int i = 0; (i < numbits); i++) {
				usr = usr + pow(2, ((numbits - 1) - i)) * seed[i];
			}
			// Línea equivalente al anterior ciclo pero con tamaño de 4 bits
			//int usr = 16 * seed[0] + 8 * seed[1] + 4 * seed[2] + 2 * seed[3] + seed[4];


			itoa(usr, (char*) buffer_lfsr, 16);
			printf("\n\r%s", buffer_lfsr);

			if(HAL_GPIO_ReadPin (GPIOC, btn_Pin)){
				printf("\n\r\n\r***************************************************************");
				printf("\n\r\t*\t DETENER LA SECUENCIA POR EL USUARIO\t*\n\r");
				printf("***************************************************************");
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				goto last;
			}


			if (band == 1) {
				band = 2;
			} else {
				band = 0;
				for (int i = 0; i < numbits; i++) {
					if (seed[i] != seed_init[i]) {
						band = 2;
					}
				}
			}

			if (band == 0) {
				if (k == pow(2, numbits) - 2) {
					printf("\n\rMAXIMO\n\r");
				} else {
					printf("\n\rNO MAX\n\r");
				}
				break;
			}
			if (band == 2 && k== pow(2, numbits) - 1) {
				printf("\n\rNO MAX\n\r");
			}
			k++;
		}
		last:
		printf("\n\r\n\r***************************************************************");
		printf("\n\r\t*\t RESUMEN FINAL DE LA SECUENCIA \t*\n\r");
		printf("***************************************************************");
		printf("\n\rNumero de bits termino de realimentacion: %d \n\r",numbits);
		printf("Funcion de realimentacion: BIN ");

		uint64_t usr = 0;
		for (int i = 0; (i < numbits); i++) {
			usr = usr + pow(2, ((numbits - 1) - i)) * seed_init[i];
		}

		uint64_t taps = 0;
		for (int i = 0; (i < numbits); i++) {
			taps = taps + pow(2, (numbits-1)-i) * pol[(numbits-1)-i];
		}
		/*
		for (int i = 0; (i < numbits); i++) {
					usr = usr + pow(2, ((numbits - 1) - i)) * seed_init[i];
				}

		for (int w = 0; w < numbits; w++) {
				aux[w] = pol[numbits - 1 - w];
			}

			for (int w = 0; w < numbits; w++) {
				pol[w] = aux[w];
			}
		 */
		itoa(taps, (char*) buffer_lfsr, 2);
		printf("%s", buffer_lfsr);
		printf(" - HEX ");
		itoa(taps, (char*) buffer_lfsr, 16);
		printf("%s", buffer_lfsr);

		printf("\n\rValor inicial - Semilla : ");
		itoa(usr, (char*) buffer_lfsr, 2);
		printf("%s", buffer_lfsr);
		printf(" - ");
		itoa(usr, (char*) buffer_lfsr, 16);
		printf("%s", buffer_lfsr);


		printf("\n\rNumero de valores calculados en la secuencia: %llu ", k+1);
		if (band == 0) {
			if (k == pow(2, numbits) - 2) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				printf("\n\rMAXIMO\n\r");
			} else {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				printf("\n\rNO MAX\n\r");
			}
		}
		if (band == 2 && k== pow(2, numbits) - 1) {
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			printf("\n\rNO MAX\n\r");
		}
		printf("\n\r***************************************************************\n\r");
		goto init;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 32000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 5000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
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
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : btn_Pin */
  GPIO_InitStruct.Pin = btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

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
