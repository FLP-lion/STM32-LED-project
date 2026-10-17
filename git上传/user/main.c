#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint8_t led_mode=0;

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
			{
				led_mode=!led_mode;
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
			}
		}
		
		if(led_mode==0)
			
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			Delay_ms(500);
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			Delay_ms(500);
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}
	}
}
