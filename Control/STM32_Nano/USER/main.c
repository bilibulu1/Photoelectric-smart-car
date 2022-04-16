#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
 #include "usart.h"
/************************************************
 ALIENTEK精英STM32开发板实验12
 OLED显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
	
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
	OLED_Init();			//初始化OLED        
  USART2_Init();
	uart_init(9600); 


	 
	while(1) 
	{		
	delay_ms(500);
		
		LED0=!LED0;
	}	  
	
	
}

