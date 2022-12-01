/* USER CODE BEGIN Header */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

//Adición de librerías para
// transmisión UART stdio y string

#include <stdlib.h>

// cálculos matemáticos (potencia)
#include <math.h>
// incluir las funciones de printf y scanf
#include "retarget.h"
#include "funciones.h"

	uint8_t tx_int[2]={0};
	uint8_t buf_int[2]={0};
	uint8_t prnt = 0;

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

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Lfsr(void){

				char buf_lfsr[10];
				uint8_t receive[32] = { 0 }; // Arreglo para recibir
				uint8_t seed[32] = { 0 };	//Arreglo semilla
				uint8_t seed_init[32] = { 0 }; //Arreglo semilla inicial
				uint8_t pol[32] = { 0 }; // Almacenar polinomio
				uint8_t aux[32] = { 0 }; // Auxiliar para invertir
				uint8_t xor[32] = { 0 }; // Almacena las xor
				uint8_t buffer_lfsr[16]={0};	//Transmitir
				uint8_t band = 1;		//bandera de ciclo max









				//Mensaje de saludo
				Saludo();

				//Etiqueta para reiniciar

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

				HAL_UART_Receive_IT(&huart3, tx_int, 1);


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

				if(prnt == 1){
				itoa(usr, (char*) buffer_lfsr, 16);
				printf("\n\r%s", buffer_lfsr);
				}


				if(buf_int[0] == 0x1b){
					printf("\n\r\n\r***************************************************************");
					printf("\n\r\t*\t DETENER LA SECUENCIA POR EL USUARIO\t*\n\r");
					printf("***************************************************************");
					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
					goto last;
				}

				if(buf_int[0] != 0x1b){
					HAL_UART_Receive_IT(&huart3, tx_int, 1);
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




			}


void Temp(void){
	uint8_t bufe_tmp[] = "error\r\n";

	   uint8_t buff_rx_tmp[2] = {0};
	   uint8_t buff_tx_tmp[2] = {0};
	   static const uint8_t ADDR_W = 0x90;
	   static const uint8_t POINTER_Temp = 0x00;
	   uint16_t val = 0;
	   uint16_t a1 = 0;
	   uint16_t a0 = 0;
	   float temp;
	   HAL_StatusTypeDef ret;

	   buff_tx_tmp[0]= POINTER_Temp;


		uint8_t buff_temp[4]={0};	//Transmitir

		ret = HAL_I2C_Master_Transmit(&hi2c1, ADDR_W, buff_tx_tmp, 1, HAL_MAX_DELAY);

					  if (ret == HAL_OK){

						  ret = HAL_I2C_Master_Receive(&hi2c1, ADDR_W, buff_rx_tmp, 2, HAL_MAX_DELAY);

						  if(ret == HAL_OK){

							  a1 = buff_rx_tmp[1];
							  a1 = (a1 >> 5);

							  a0 = buff_rx_tmp[0];
							  a0 = (a0 << 3);

							  val = (a0 | a1);

							  temp = val*0.125;


							  itoa(val, (char*) buff_temp, 10);


							  printf("%.6f\r\n", temp);
							  HAL_Delay(500);
						  }
					  }

					  if (ret != HAL_OK){
						  HAL_UART_Transmit(&huart3, bufe_tmp, sizeof(bufe_tmp), HAL_MAX_DELAY);
						  HAL_Delay(300);
					  }

}




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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

	RetargetInit(&huart3);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */




	uint8_t rx[2]={0};
	uint8_t buffin[100]={0};

	char saludo[] = "jhan";
	char help[] = "help";
	char temp[] = "temp";
	char ledc[] = "ledc";
	char lfsr[] = "lfsr";
	char time[] = "time";
	char rege[] = "rege";
	char prin[] = "prin";

	uint8_t i = 0;

	while (1)
	{

//////////////////////////RECIBIMOS EL TECLADO/////////////////////////
				while(rx[0] != 0x0A){
					  HAL_UART_Receive(&huart3, rx, 1, HAL_MAX_DELAY);
					  buffin[i]=rx[0];
					  i++;
				  }
//////////////////////////TRANSMITIMOS LO QUE RECIBIMOS DEL TECLADO, SOLO PARA PROBAR, LUEGO SE QUITA//////
				  HAL_UART_Transmit(&huart3, buffin, i, HAL_MAX_DELAY);
				  i=0;
				  rx[0]=0;
//////////////////////DETERMINAMOS QUÉ COMANDO RECIBIMOS////////////////
				  /////FALTA PONER LA PARTE DE PROCESAR EL PAR�?METRO
				  ///// ES SOLO PARA TENER LISTA LA PARTE DE TERMINAR COMANDOS
				  if(!memcmp(buffin,saludo,strlen(saludo))){

					  printf("es saludo\n\r");
					  printf(" %d\n",strlen(saludo));
					  printf(" %d\n",strlen((char*)buffin));

					  for(int w = 0; w<sizeof(buffin); w++){
					 				  		  			  buffin[w]=0;}
				  }


				  else if(!memcmp(buffin,help,strlen(help))){
					  printf("es help\n\r");
					  printf(" %d\n",strlen(help));
					  printf(" %d\n",strlen((char*)buffin));


					  if((buffin[5]==0)&&(buffin[6]==0)){
						  Help();
					  }

					  if((buffin[5]=='t')&&(buffin[6]==0x65)&&(buffin[7]==0x6d)&&(buffin[8]==0x70)){
						  H_Temp();
					  }

					  if((buffin[5]=='l')&&(buffin[6]=='e')&&(buffin[7]=='d')&&(buffin[8]=='c')){
						  H_Ledc();
					  }

					  if((buffin[5]=='l')&&(buffin[6]=='f')&&(buffin[7]=='s')&&(buffin[8]=='r')){
						  H_Lfsr();
					  }

					  if((buffin[5]==0x74)&&(buffin[6]==0x69)&&(buffin[7]==0x6d)&&(buffin[8]==0x65)){
						  H_Time();
					  }

					  if((buffin[5]==0x72)&&(buffin[6]==0x65)&&(buffin[7]==0x67)&&(buffin[8]==0x65)){
						  H_Rege();
					  }

					  if((buffin[5]==0x70)&&(buffin[6]==0x72)&&(buffin[7]==0x69)&&(buffin[8]==0x6e)){
						  H_Prin();
					  }





					  for(int w = 0; w<sizeof(buffin); w++){
					  					 			buffin[w]=0;}

				  }

				  else if(!memcmp(buffin,temp,strlen(temp))){
					  printf("es temp\n\r");
					  printf(" %d\n",strlen(temp));
					  printf(" %d\n",strlen((char*)buffin));

					  //PONER LA FUNCION PARA LEER TEMPERATURA, YA QUE AC�? NO SE RECIBE PAR�?METRO//
					  Temp();

					  for(int w = 0; w<sizeof(buffin); w++){
													buffin[w]=0;

					  }

				  }

				  else if(!memcmp(buffin,ledc,strlen(ledc))){
					  printf("es led\n\r");
					  printf(" %d\n",strlen(ledc));
					  printf(" %d\n",strlen((char*)buffin));

					  //PONER LA FUNCIÓN PARA CONFIGURAR LA FRECUANCIA DEL LED//


					  if((buffin[5]== 'o') && (buffin[6]== 'n')){
						  HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
					  }

					  if((buffin[5] == 'o') && (buffin[6]=='f')){
						  HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
					  }


					  for(int w = 0; w<sizeof(buffin); w++){
												buffin[w]=0;}

				  }




				  else if(!memcmp(buffin,lfsr,strlen(lfsr))){
					  printf("es lfsr\n\r");
					  printf(" %d\n",strlen(lfsr));
					  printf(" %d\n",strlen((char*)buffin));

					  if(buffin[5]=='x'){
						  buf_int[0] = 0;

						  Lfsr();


					  }

					  if(buffin[5]=='p'){
						  printf("es lfsr con pagina\n\r");
					  }



					  for(int w = 0; w<sizeof(buffin); w++){
					  							buffin[w]=0;}

				  }



				  else if(!memcmp(buffin,time,strlen(time))){
					  	  uint64_t r =0;
					  	  r = pow(2,32);
				 		printf("es time\n\r");
				 		printf(" %d\n",strlen(time));
				 		printf(" %d\n",strlen((char*)buffin));
				 		printf(" %llu",r);



				 		for(int w = 0; w<sizeof(buffin); w++){
				 					  			buffin[w]=0;}

				  }


				  else if(!memcmp(buffin,rege,strlen(rege))){
				  	printf("es rege\n\r");
				  	printf(" %d\n",strlen(rege));
				  	printf(" %d\n",strlen((char*)buffin));



				  	for(int w = 0; w<sizeof(buffin); w++){
				  				 			buffin[w]=0;}

				  }



				  else if(!memcmp(buffin,prin,strlen(prin))){
				  	printf("es prin\n\r");
				  	printf(" %d\n",strlen(prin));
				  	printf(" %d\n",strlen((char*)buffin));

				  	if(buffin[5]=='e'){
				  	prnt = 1;
				  	printf("Mostrar secuencia Habilitado\n\r");
				  	}

				  	if(buffin[5]=='d'){
					prnt = 0;
					printf("Mostrar secuencia Deshabilitado\n\r");
					}

				  	for(int w = 0; w<sizeof(buffin); w++){
				  				 			buffin[w]=0;}

				  }

				  else{
					  printf("ningun comando\n\r");
					  for(int w = 0; w<sizeof(buffin); w++){
					 				  		  			  buffin[w]=0;}
				  }




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
  hi2c1.Init.Timing = 0x10805D88;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  huart3.Init.BaudRate = 921600;
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    buf_int[0]=tx_int[0];


}
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
