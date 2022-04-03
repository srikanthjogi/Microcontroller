//UART2_TRANSMITTER
#include"stm32f4xx.h"

void USART2_Init(void);
void USART2_write(char data);
void delay(int sec);

int main(void)
{
	USART2_Init();
	while(1)
	{
		USART2_write('H');
		delay(50);
		USART2_write('E');
		delay(50);
		USART2_write('L');
		delay(50);
		USART2_write('L');
		delay(50);
		USART2_write('O');
		delay(50);
		USART2_write(' ');
				delay(50);



		        USART2_write('S');
				delay(50);
				USART2_write('R');
				delay(50);
				USART2_write('I');
				delay(50);
				USART2_write('K');
				delay(50);
				USART2_write('A');
				delay(50);
				USART2_write('N');
				delay(50);
				USART2_write('T');
				delay(50);
				USART2_write('H');
				delay(50);






		USART2_write('\r');
		delay(50);



		USART2_write('\n');
		delay(50);



	}
}
void USART2_Init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB1ENR |= 0x20000;
	GPIOA->MODER |= 0x20;
	GPIOA->AFR[0] |= 0x700;
	USART2->BRR |= 0x683;
	USART2->CR1 |= 0x8;
	USART2->CR1 |= 0x2000;
}
void USART2_write(char data)
{
	while(!(USART2->SR & 0x80)){}
	USART2->DR |= (data);
}
void delay(int sec)
{
	while(sec--)
	{
		int i;
		for(i=0;i<3000;i++);
	}
}
















