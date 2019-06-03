/* USER CODE BEGIN Header */
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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "Touch.h"
#include "stdio.h"
#include "dht11.h"
#include "delay.h"

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
/* Private variables ---------------------------------------------------------*/
extern uint8_t CMD_X[3];
extern uint8_t CMD_Y[3];
extern uint8_t SPI_RE[3];
extern uint8_t Cmd_Buf[15];
extern uint8_t Cmdcont;
int btn1=0;
int btn2=0;
int btn3=0;
extern const unsigned char bg[];
uint8_t aaa[16] = {0};
uint8_t recv_end_flag = 0;
uint8_t rx_len = 0;
uint8_t Dowm_flag = 0;  //1 表示已经按下   
uint16_t line_x = 0;       	//存储当前坐标
uint16_t line_y = 0;
uint16_t Date = 0;
uint8_t j = 0;
#define DE_A  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_B  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_C    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_D      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)
#define DE_AB  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_BC  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_CD    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET) 
#define DE_DA     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)
/* USER CODE END PV */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void lcd_init(void);
void Touch_Init(void);
void motor1(void);
void motor2(void);
void hint(void);
void lcd_clear(unsigned short Color);
void LCD_DrawPicture(uint16_t StartX,uint16_t StartY,uint16_t Xend,uint16_t Yend,uint8_t *pic);
void  Lcd_Show();
void btn();
uint16_t Get_Adc_Average(ADC_HandleTypeDef* hadc,uint8_t times);
/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Pen_Holder Pen_Point;	/* 定义笔实体 */
uint16_t Light=0;
uint16_t Get_Adc_Average(ADC_HandleTypeDef* hadc,uint8_t times);
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
  MX_FSMC_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */
	delay_init(160);
	lcd_init();
	printf("=====init======\n");				
	LCD_DrawPicture(0,0,480,282,(uint8_t *)bg);		//480、272为图片的高度和宽度
	uint8_t value[4] ;	
	value[0] = ' ';
	value[1] = ' ';
	value[2] = ' ';
	value[3] = '\0';		
	LCD_ShowString(280, 80,value, Red, Red); 
	LCD_ShowString(280, 140,value, Red, Red); 
	LCD_ShowString(280, 200,value, Red, Red); 
	printf("init ok!!!!!!\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
    uint16_t Light_A;
    uint16_t Light_B;	
	  HAL_ADC_Start(&hadc3);
		HAL_ADC_PollForConversion(&hadc3,10);		
		Light_A=Get_Adc_Average(&hadc3,10);		
		Light_B=Light_A*3300/4096;				
		Light=50000-500/33*Light_B;
		if(btn1)
		printf("Light=%d\n",Light);	
		if(Light<20000&&btn3) 
		motor2();
		else if(Light>30050&&btn3) 
		motor1();
		else 		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET); 
	  HAL_Delay(200);
	  DHT11_TEST();
		if(ucharT_data_H<20&&btn2)
		hint();
		if(ucharT_data_H>27&&btn2)
		hint();
		if(btn1)
	  printf("Temp=%d\n",ucharT_data_H);	
		if(btn1)
	  printf("Humidity=%d\n",ucharRH_data_H);					
	  Lcd_Show();
		HAL_Delay(200);
		if( Pen_Point.Key_Sta==Key_Down )     //触摸屏被按下
		{				
		HAL_Delay(20);
		if(!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7))
		{
		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);	//关闭中断	
		if( Convert_Pos() ) 			 //存放点击的X,Y的坐标值	成功转换 返回1 失败返回0 	
		{
		line_x = Pen_Point.X0;
		line_y = Pen_Point.Y0;
		HAL_Delay(200);
		btn();
		Pen_Point.X0 = 0;
	  Pen_Point.Y0 = 0;
		Pen_Point.Key_Sta=Key_Up;  			//处理数据后, 回复到没有按下的状态							
		}	
		Pen_Point.Key_Sta=Key_Up;  			//处理数据后, 回复到没有按下的状态		
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);				     //开启中断					
		}
		else
		{
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		
		Pen_Point.Key_Sta=Key_Up;  
		continue ;
		}
		} 
		/********MENU HANDLER********/
		
		/****************************/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void hint(){
	for(int j = 0;j<=300;j++){
		
HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);//打开蜂鸣器
		HAL_Delay(1);	
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);//关闭蜂鸣器
		HAL_Delay(1);	
	
	
	}
	
				
}
void motor1(){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET); 
for(int j = 0;j<=30;j++){
//DE_A;
	//HAL_Delay(100);//可进行调速，延时时间不能太短
	DE_AB;
	HAL_Delay(1);
	//DE_B;
	//HAL_Delay(1);
	DE_BC;
	HAL_Delay(1);
	//DE_C;
	//HAL_Delay(1);
	DE_CD;
	HAL_Delay(1);
	//DE_D;
	//HAL_Delay(1);	
	DE_DA;
	HAL_Delay(1);}
}
void motor2(){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET); 
for(int j = 0;j<=30;j++){
	DE_A;
	HAL_Delay(1);
	DE_DA;
	HAL_Delay(1);
	DE_D;
	HAL_Delay(1);
	DE_CD;
	HAL_Delay(1);
		DE_C;
	HAL_Delay(1);
			DE_BC;
	HAL_Delay(1);
				DE_B;
	HAL_Delay(1);
					DE_AB;
	HAL_Delay(1);
						DE_A;
	HAL_Delay(1);
	//
}

}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (uint8_t) ch;      
	return ch;
}


void  Lcd_Show()
{

	uint8_t value[4] ;	

		value[0] = (uint8_t)(Light%100000/10000) + 48;
		value[1] = (uint8_t)(Light%10000/1000) + 48;
		value[2] = (uint8_t)(Light%1000/100) + 48;
		value[3] = '\0';		
		LCD_ShowString(125, 204,value, Black, White); 
		value[0] = ' ';
		value[1] = (uint8_t)(ucharT_data_H%100/10) + 48;
		value[2] = (uint8_t)(ucharT_data_H%10) + 48;
		value[3] = '\0';		
		LCD_ShowString(125, 80,value, Black, White); 
		value[0] = ' ';
		value[1] = (uint8_t)(ucharRH_data_H%100/10) + 48;
		value[2] = (uint8_t)(ucharRH_data_H%10) + 48;
		value[3] = '\0';		
		LCD_ShowString(125, 142,value, Black, White); 		
		
}



void btn(){
uint8_t value[4] ;	
if(line_x <424&&line_x>310){
	if(line_y>67.68 && line_y<112.8){if(btn1==1){btn1=0;
		value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280, 80,value, Red, Red); 
	}
	else {btn1=1;
	value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280, 80,value, Green, Green); 
	}
	}
	if(line_y>126.9 && line_y<172.02){if(btn2==1){btn2=0;
		value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280, 140,value, Red, Red); 
	}
	else {btn2=1;
	value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280, 140,value, Green, Green); 
	}}
	if(line_y>172 && line_y<231.24){if(btn3==1){btn3=0;
		value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280,200,value, Red, Red); 
	}
	else {btn3=1;
	value[0] = ' ';
		value[1] = ' ';
		value[2] = ' ';
		value[3] = '\0';		
		LCD_ShowString(280, 200,value, Green, Green); 
	}}
	printf("btn is down  \n btn1 :%d  btn2:%d  btn3: %d  \n",btn1,btn2,btn3);


}





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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
