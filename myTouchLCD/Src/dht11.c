#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "dht11.h"
#include "delay.h"


//温湿度定义

	uint8_t ucharT_data_H=0,ucharT_data_L=0,ucharRH_data_H=0,ucharRH_data_L=0,ucharcheckdata=0;

void DHT11_TEST(void)   //温湿传感启动
{
  uint8_t ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_humidity,ucharRH_data_L_humidity,ucharcheckdata_temp;
  uint8_t ucharFLAG = 0,uchartemp=0;
  uint8_t ucharcomdata;
  uint8_t i;    
  D2_OUT_GPIO_Init();  
  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_RESET);
  delay_ms(25);
  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET);
  D2_IN_GPIO_Init();	
  delay_us(40);
    if(!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1)) 
         {
					    while ((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<10)//DHT11会拉低40~80us
								{
									ucharFLAG++;
									delay_us(10);								
								};						
								if(ucharFLAG>=10)ucharFLAG=0;
								else ucharFLAG=0;
							while ((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<10)//DHT11拉低后会再次拉高40~80us
								{
									ucharFLAG++;
									delay_us(10);
								};
								if(ucharFLAG>=10)ucharFLAG=0;	    
								else ucharFLAG=0;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//
								{
									ucharFLAG++;
									delay_us(1);								
								};
                 while((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//DHT11会拉低
								{
									ucharFLAG++;
									delay_us(1);								
								};	 
                 delay_us(28);           						
								 ucharcomdata<<=1;
                 if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))ucharcomdata|=0x01;			
               }
            ucharRH_data_H_humidity = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//
								{
									ucharFLAG++;
									delay_us(1);								
								};
                 while((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//DHT11会拉低
								{
									ucharFLAG++;
									delay_us(1);								
								};	 
                 delay_us(28);           						
								 ucharcomdata<<=1;
                 if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))ucharcomdata|=0x01;			
               }
            ucharRH_data_L_humidity = ucharcomdata;
             for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//
								{
									ucharFLAG++;
									delay_us(1);								
								};
                 while((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//DHT11会拉低
								{
									ucharFLAG++;
									delay_us(1);								
								};	 
                 delay_us(28);           						
								 ucharcomdata<<=1;
                 if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))ucharcomdata|=0x01;			
               }
            ucharT_data_H_temp      = ucharcomdata;						 
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//
								{
									ucharFLAG++;
									delay_us(1);								
								};
                 while((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)//DHT11会拉低
								{
									ucharFLAG++;
									delay_us(1);								
								};	 
                 delay_us(28);           					
								 ucharcomdata<<=1;
                 if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))ucharcomdata|=0x01;			
               }
            ucharT_data_L_temp      = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)
								{
									ucharFLAG++;
									delay_us(1);								
								};
                 while((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))&&ucharFLAG<100)
								{
									ucharFLAG++;
									delay_us(1);								
								};	 
                 delay_us(28);           							
								 ucharcomdata<<=1;
                 if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1))ucharcomdata|=0x01;			
               }
            ucharcheckdata_temp     = ucharcomdata;
            uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_humidity+ucharRH_data_L_humidity);
							 
          if(1	)
          {          
              ucharT_data_H  = ucharT_data_H_temp;
              ucharT_data_L  = ucharT_data_L_temp;
              ucharRH_data_H = ucharRH_data_H_humidity;
              ucharRH_data_L = ucharRH_data_L_humidity;
              ucharcheckdata = ucharcheckdata_temp; 					
          } 
				
       } 
    else //没用成功读取，返回0
       {
          ucharT_data_H  = 0;
          ucharT_data_L  = 0;
          ucharRH_data_H = 0;
          ucharRH_data_L = 0; 	
       } 		 
}




