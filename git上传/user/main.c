#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint8_t led_mode=0;    //0代表闪烁，1代表常亮

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;    //定义结构体变量，存放GPIO配置参数
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;    //选中0号引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);    //把参数写入硬件寄存器
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);    //PA0输出高电平，默认熄灭 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;    //上拉输入，PA1用电阻接成高电平（1）
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)    //按键检测
		{
			Delay_ms(20);  //消抖
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
			{
				led_mode=!led_mode;
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);    //松手检测
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
