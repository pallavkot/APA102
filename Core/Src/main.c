/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define LED_NO 120

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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define LED_BUFFER_LENGTH (LED_NO*12)
const uint8_t leddata[256*4] = { // size = 256 * 3
0X44 , 0X44 , 0X44 , 0X44 , // 0
0X44 , 0X44 , 0X44 , 0X47 , // 1
0X44 , 0X44 , 0X44 , 0X74 , 
0X44 , 0X44 , 0X44 , 0X77 , 
0X44 , 0X44 , 0X47 , 0X44 , 
0X44 , 0X44 , 0X47 , 0X47 , 
0X44 , 0X44 , 0X47 , 0X74 , 
0X44 , 0X44 , 0X47 , 0X77 , 
0X44 , 0X44 , 0X74 , 0X44 , 
0X44 , 0X44 , 0X74 , 0X47 , 
0X44 , 0X44 , 0X74 , 0X74 , 
0X44 , 0X44 , 0X74 , 0X77 , 
0X44 , 0X44 , 0X77 , 0X44 , 
0X44 , 0X44 , 0X77 , 0X47 , 
0X44 , 0X44 , 0X77 , 0X74 , 
0X44 , 0X44 , 0X77 , 0X77 , 
0X44 , 0X47 , 0X44 , 0X44 , 
0X44 , 0X47 , 0X44 , 0X47 , 
0X44 , 0X47 , 0X44 , 0X74 , 
0X44 , 0X47 , 0X44 , 0X77 , 
0X44 , 0X47 , 0X47 , 0X44 , 
0X44 , 0X47 , 0X47 , 0X47 , 
0X44 , 0X47 , 0X47 , 0X74 , 
0X44 , 0X47 , 0X47 , 0X77 , 
0X44 , 0X47 , 0X74 , 0X44 , 
0X44 , 0X47 , 0X74 , 0X47 , 
0X44 , 0X47 , 0X74 , 0X74 , 
0X44 , 0X47 , 0X74 , 0X77 , 
0X44 , 0X47 , 0X77 , 0X44 , 
0X44 , 0X47 , 0X77 , 0X47 , 
0X44 , 0X47 , 0X77 , 0X74 , 
0X44 , 0X47 , 0X77 , 0X77 , 
0X44 , 0X74 , 0X44 , 0X44 , 
0X44 , 0X74 , 0X44 , 0X47 , 
0X44 , 0X74 , 0X44 , 0X74 , 
0X44 , 0X74 , 0X44 , 0X77 , 
0X44 , 0X74 , 0X47 , 0X44 , 
0X44 , 0X74 , 0X47 , 0X47 , 
0X44 , 0X74 , 0X47 , 0X74 , 
0X44 , 0X74 , 0X47 , 0X77 , 
0X44 , 0X74 , 0X74 , 0X44 , 
0X44 , 0X74 , 0X74 , 0X47 , 
0X44 , 0X74 , 0X74 , 0X74 , 
0X44 , 0X74 , 0X74 , 0X77 , 
0X44 , 0X74 , 0X77 , 0X44 , 
0X44 , 0X74 , 0X77 , 0X47 , 
0X44 , 0X74 , 0X77 , 0X74 , 
0X44 , 0X74 , 0X77 , 0X77 , 
0X44 , 0X77 , 0X44 , 0X44 , 
0X44 , 0X77 , 0X44 , 0X47 , 
0X44 , 0X77 , 0X44 , 0X74 , 
0X44 , 0X77 , 0X44 , 0X77 , 
0X44 , 0X77 , 0X47 , 0X44 , 
0X44 , 0X77 , 0X47 , 0X47 , 
0X44 , 0X77 , 0X47 , 0X74 , 
0X44 , 0X77 , 0X47 , 0X77 , 
0X44 , 0X77 , 0X74 , 0X44 , 
0X44 , 0X77 , 0X74 , 0X47 , 
0X44 , 0X77 , 0X74 , 0X74 , 
0X44 , 0X77 , 0X74 , 0X77 , 
0X44 , 0X77 , 0X77 , 0X44 , 
0X44 , 0X77 , 0X77 , 0X47 , 
0X44 , 0X77 , 0X77 , 0X74 , 
0X44 , 0X77 , 0X77 , 0X77 , 
0X47 , 0X44 , 0X44 , 0X44 , 
0X47 , 0X44 , 0X44 , 0X47 , 
0X47 , 0X44 , 0X44 , 0X74 , 
0X47 , 0X44 , 0X44 , 0X77 , 
0X47 , 0X44 , 0X47 , 0X44 , 
0X47 , 0X44 , 0X47 , 0X47 , 
0X47 , 0X44 , 0X47 , 0X74 , 
0X47 , 0X44 , 0X47 , 0X77 , 
0X47 , 0X44 , 0X74 , 0X44 , 
0X47 , 0X44 , 0X74 , 0X47 , 
0X47 , 0X44 , 0X74 , 0X74 , 
0X47 , 0X44 , 0X74 , 0X77 , 
0X47 , 0X44 , 0X77 , 0X44 , 
0X47 , 0X44 , 0X77 , 0X47 , 
0X47 , 0X44 , 0X77 , 0X74 , 
0X47 , 0X44 , 0X77 , 0X77 , 
0X47 , 0X47 , 0X44 , 0X44 , 
0X47 , 0X47 , 0X44 , 0X47 , 
0X47 , 0X47 , 0X44 , 0X74 , 
0X47 , 0X47 , 0X44 , 0X77 , 
0X47 , 0X47 , 0X47 , 0X44 , 
0X47 , 0X47 , 0X47 , 0X47 , 
0X47 , 0X47 , 0X47 , 0X74 , 
0X47 , 0X47 , 0X47 , 0X77 , 
0X47 , 0X47 , 0X74 , 0X44 , 
0X47 , 0X47 , 0X74 , 0X47 , 
0X47 , 0X47 , 0X74 , 0X74 , 
0X47 , 0X47 , 0X74 , 0X77 , 
0X47 , 0X47 , 0X77 , 0X44 , 
0X47 , 0X47 , 0X77 , 0X47 , 
0X47 , 0X47 , 0X77 , 0X74 , 
0X47 , 0X47 , 0X77 , 0X77 , 
0X47 , 0X74 , 0X44 , 0X44 , 
0X47 , 0X74 , 0X44 , 0X47 , 
0X47 , 0X74 , 0X44 , 0X74 , 
0X47 , 0X74 , 0X44 , 0X77 , 
0X47 , 0X74 , 0X47 , 0X44 , 
0X47 , 0X74 , 0X47 , 0X47 , 
0X47 , 0X74 , 0X47 , 0X74 , 
0X47 , 0X74 , 0X47 , 0X77 , 
0X47 , 0X74 , 0X74 , 0X44 , 
0X47 , 0X74 , 0X74 , 0X47 , 
0X47 , 0X74 , 0X74 , 0X74 , 
0X47 , 0X74 , 0X74 , 0X77 , 
0X47 , 0X74 , 0X77 , 0X44 , 
0X47 , 0X74 , 0X77 , 0X47 , 
0X47 , 0X74 , 0X77 , 0X74 , 
0X47 , 0X74 , 0X77 , 0X77 , 
0X47 , 0X77 , 0X44 , 0X44 , 
0X47 , 0X77 , 0X44 , 0X47 , 
0X47 , 0X77 , 0X44 , 0X74 , 
0X47 , 0X77 , 0X44 , 0X77 , 
0X47 , 0X77 , 0X47 , 0X44 , 
0X47 , 0X77 , 0X47 , 0X47 , 
0X47 , 0X77 , 0X47 , 0X74 , 
0X47 , 0X77 , 0X47 , 0X77 , 
0X47 , 0X77 , 0X74 , 0X44 , 
0X47 , 0X77 , 0X74 , 0X47 , 
0X47 , 0X77 , 0X74 , 0X74 , 
0X47 , 0X77 , 0X74 , 0X77 , 
0X47 , 0X77 , 0X77 , 0X44 , 
0X47 , 0X77 , 0X77 , 0X47 , 
0X47 , 0X77 , 0X77 , 0X74 , 
0X47 , 0X77 , 0X77 , 0X77 , 
0X74 , 0X44 , 0X44 , 0X44 , 
0X74 , 0X44 , 0X44 , 0X47 , 
0X74 , 0X44 , 0X44 , 0X74 , 
0X74 , 0X44 , 0X44 , 0X77 , 
0X74 , 0X44 , 0X47 , 0X44 , 
0X74 , 0X44 , 0X47 , 0X47 , 
0X74 , 0X44 , 0X47 , 0X74 , 
0X74 , 0X44 , 0X47 , 0X77 , 
0X74 , 0X44 , 0X74 , 0X44 , 
0X74 , 0X44 , 0X74 , 0X47 , 
0X74 , 0X44 , 0X74 , 0X74 , 
0X74 , 0X44 , 0X74 , 0X77 , 
0X74 , 0X44 , 0X77 , 0X44 , 
0X74 , 0X44 , 0X77 , 0X47 , 
0X74 , 0X44 , 0X77 , 0X74 , 
0X74 , 0X44 , 0X77 , 0X77 , 
0X74 , 0X47 , 0X44 , 0X44 , 
0X74 , 0X47 , 0X44 , 0X47 , 
0X74 , 0X47 , 0X44 , 0X74 , 
0X74 , 0X47 , 0X44 , 0X77 , 
0X74 , 0X47 , 0X47 , 0X44 , 
0X74 , 0X47 , 0X47 , 0X47 , 
0X74 , 0X47 , 0X47 , 0X74 , 
0X74 , 0X47 , 0X47 , 0X77 , 
0X74 , 0X47 , 0X74 , 0X44 , 
0X74 , 0X47 , 0X74 , 0X47 , 
0X74 , 0X47 , 0X74 , 0X74 , 
0X74 , 0X47 , 0X74 , 0X77 , 
0X74 , 0X47 , 0X77 , 0X44 , 
0X74 , 0X47 , 0X77 , 0X47 , 
0X74 , 0X47 , 0X77 , 0X74 , 
0X74 , 0X47 , 0X77 , 0X77 , 
0X74 , 0X74 , 0X44 , 0X44 , 
0X74 , 0X74 , 0X44 , 0X47 , 
0X74 , 0X74 , 0X44 , 0X74 , 
0X74 , 0X74 , 0X44 , 0X77 , 
0X74 , 0X74 , 0X47 , 0X44 , 
0X74 , 0X74 , 0X47 , 0X47 , 
0X74 , 0X74 , 0X47 , 0X74 , 
0X74 , 0X74 , 0X47 , 0X77 , 
0X74 , 0X74 , 0X74 , 0X44 , 
0X74 , 0X74 , 0X74 , 0X47 , 
0X74 , 0X74 , 0X74 , 0X74 , 
0X74 , 0X74 , 0X74 , 0X77 , 
0X74 , 0X74 , 0X77 , 0X44 , 
0X74 , 0X74 , 0X77 , 0X47 , 
0X74 , 0X74 , 0X77 , 0X74 , 
0X74 , 0X74 , 0X77 , 0X77 , 
0X74 , 0X77 , 0X44 , 0X44 , 
0X74 , 0X77 , 0X44 , 0X47 , 
0X74 , 0X77 , 0X44 , 0X74 , 
0X74 , 0X77 , 0X44 , 0X77 , 
0X74 , 0X77 , 0X47 , 0X44 , 
0X74 , 0X77 , 0X47 , 0X47 , 
0X74 , 0X77 , 0X47 , 0X74 , 
0X74 , 0X77 , 0X47 , 0X77 , 
0X74 , 0X77 , 0X74 , 0X44 , 
0X74 , 0X77 , 0X74 , 0X47 , 
0X74 , 0X77 , 0X74 , 0X74 , 
0X74 , 0X77 , 0X74 , 0X77 , 
0X74 , 0X77 , 0X77 , 0X44 , 
0X74 , 0X77 , 0X77 , 0X47 , 
0X74 , 0X77 , 0X77 , 0X74 , 
0X74 , 0X77 , 0X77 , 0X77 , 
0X77 , 0X44 , 0X44 , 0X44 , 
0X77 , 0X44 , 0X44 , 0X47 , 
0X77 , 0X44 , 0X44 , 0X74 , 
0X77 , 0X44 , 0X44 , 0X77 , 
0X77 , 0X44 , 0X47 , 0X44 , 
0X77 , 0X44 , 0X47 , 0X47 , 
0X77 , 0X44 , 0X47 , 0X74 , 
0X77 , 0X44 , 0X47 , 0X77 , 
0X77 , 0X44 , 0X74 , 0X44 , 
0X77 , 0X44 , 0X74 , 0X47 , 
0X77 , 0X44 , 0X74 , 0X74 , 
0X77 , 0X44 , 0X74 , 0X77 , 
0X77 , 0X44 , 0X77 , 0X44 , 
0X77 , 0X44 , 0X77 , 0X47 , 
0X77 , 0X44 , 0X77 , 0X74 , 
0X77 , 0X44 , 0X77 , 0X77 , 
0X77 , 0X47 , 0X44 , 0X44 , 
0X77 , 0X47 , 0X44 , 0X47 , 
0X77 , 0X47 , 0X44 , 0X74 , 
0X77 , 0X47 , 0X44 , 0X77 , 
0X77 , 0X47 , 0X47 , 0X44 , 
0X77 , 0X47 , 0X47 , 0X47 , 
0X77 , 0X47 , 0X47 , 0X74 , 
0X77 , 0X47 , 0X47 , 0X77 , 
0X77 , 0X47 , 0X74 , 0X44 , 
0X77 , 0X47 , 0X74 , 0X47 , 
0X77 , 0X47 , 0X74 , 0X74 , 
0X77 , 0X47 , 0X74 , 0X77 , 
0X77 , 0X47 , 0X77 , 0X44 , 
0X77 , 0X47 , 0X77 , 0X47 , 
0X77 , 0X47 , 0X77 , 0X74 , 
0X77 , 0X47 , 0X77 , 0X77 , 
0X77 , 0X74 , 0X44 , 0X44 , 
0X77 , 0X74 , 0X44 , 0X47 , 
0X77 , 0X74 , 0X44 , 0X74 , 
0X77 , 0X74 , 0X44 , 0X77 , 
0X77 , 0X74 , 0X47 , 0X44 , 
0X77 , 0X74 , 0X47 , 0X47 , 
0X77 , 0X74 , 0X47 , 0X74 , 
0X77 , 0X74 , 0X47 , 0X77 , 
0X77 , 0X74 , 0X74 , 0X44 , 
0X77 , 0X74 , 0X74 , 0X47 , 
0X77 , 0X74 , 0X74 , 0X74 , 
0X77 , 0X74 , 0X74 , 0X77 , 
0X77 , 0X74 , 0X77 , 0X44 , 
0X77 , 0X74 , 0X77 , 0X47 , 
0X77 , 0X74 , 0X77 , 0X74 , 
0X77 , 0X74 , 0X77 , 0X77 , 
0X77 , 0X77 , 0X44 , 0X44 , 
0X77 , 0X77 , 0X44 , 0X47 , 
0X77 , 0X77 , 0X44 , 0X74 , 
0X77 , 0X77 , 0X44 , 0X77 , 
0X77 , 0X77 , 0X47 , 0X44 , 
0X77 , 0X77 , 0X47 , 0X47 , 
0X77 , 0X77 , 0X47 , 0X74 , 
0X77 , 0X77 , 0X47 , 0X77 , 
0X77 , 0X77 , 0X74 , 0X44 , 
0X77 , 0X77 , 0X74 , 0X47 , 
0X77 , 0X77 , 0X74 , 0X74 , 
0X77 , 0X77 , 0X74 , 0X77 , 
0X77 , 0X77 , 0X77 , 0X44 , 
0X77 , 0X77 , 0X77 , 0X47 , 
0X77 , 0X77 , 0X77 , 0X74 , 
0X77 , 0X77 , 0X77 , 0X77 ,
};

uint8_t ws_buffer[LED_BUFFER_LENGTH];

void encode_byte( uint8_t data, int16_t buffer_index )
{
   int index = data * 4;
   ws_buffer[buffer_index++ ] = leddata[index++];
   ws_buffer[buffer_index++ ] = leddata[index++];
   ws_buffer[buffer_index++ ] = leddata[index++];
   ws_buffer[buffer_index++ ] = leddata[index++];
}

void generate_ws_buffer( uint8_t RData,uint8_t GData,uint8_t BData, int16_t led_no )
{
	//ws2812b
  //G--R--B
  //MSB first	
  int offset = led_no * 12;
  encode_byte( GData, offset );
  encode_byte( RData, offset+4 );
  encode_byte( BData, offset+8 );   
}
void Send_2812(void)
 {   
#if 1    
    HAL_SPI_Transmit_DMA( &hspi1, ws_buffer, LED_BUFFER_LENGTH ); 
    // wait until finished
    while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY ));
#else
    HAL_SPI_Transmit( &hspi1, ws_buffer, LED_BUFFER_LENGTH, 300 );
#endif
 } 
 
void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b)
{ 
   int i;
   for(i=0;i< LED_NO;i++) {
      generate_ws_buffer( r, g, b, i );
   }
   Send_2812();
}
 void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
 {	 
   generate_ws_buffer( r, g, b, n );
   Send_2812();
}
/**
 * initialize MOSI pin to LOW.  Without this, first time transmit for first LED might be wrong.
 *
 */
void initLEDMOSI(void)
{
   uint8_t buffer0[2] = { 0, 0 };
   HAL_SPI_Transmit(&hspi1, buffer0, 1, 100 );
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
  MX_USB_DEVICE_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  initLEDMOSI();
  while (1)
  {
    int i;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    setAllPixelColor(0,0,0);
    HAL_Delay(200);
    for ( i = 0; i < LED_NO; i++) {
      setPixelColor( i, 250, 0, 0 );
      HAL_Delay(200);
    }
    // green
    for ( i = 0; i < LED_NO; i++) {
      setPixelColor( i, 0, 250, 0 );
      HAL_Delay(200);
    }
    // blue
    for ( i = 0; i < LED_NO; i++) {
      setPixelColor( i, 0, 0, 250 );
      HAL_Delay(200);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV8;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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
