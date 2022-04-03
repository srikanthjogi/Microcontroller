#include"stm32f4xx.h"

void USART2_Init(void);
char USART2_read(void);
void blink_led(int);
void delay(int sec);

int main(void)
{
	char c;
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x00000400;
	USART2_Init();
	while(1)
	{
		c=USART2_read();
		blink_led(c);

	}
}
void USART2_Init(void)
{
	RCC->AHB1ENR |= 1;        //Enable GPIOA
	RCC->APB1ENR |= 0x20000;  //Enable USART2
	GPIOA->MODER |= 0x80;     //Enable alternate function
	GPIOA->AFR[0] |= 0x7000;  //Enable alternate function for USART2
	USART2->BRR |= 0x683;      //Baud rate
	USART2->CR1 |= 0x4;        // Enable RX
	USART2->CR2 = 0x0000;      //1 stop bit
	USART2->CR3 = 0x0000;      //no flow

	USART2->CR1 |= 0x2000; // Enable UE

}
char USART2_read(void)
{
	while(!(USART2->SR & 0x20)){}

	return USART2->DR;

}
void blink_led(int value)
{
	value %= 16;
	for( ;value>0;value--)
	{
			GPIOA->BSRR |= 0x00000020;
			delay(500);
			GPIOA->BSRR |= 0x00200000;
			delay(500);
	}



}
void delay(int sec)
{
	while(sec--)
	{
		int i;
		for(i=0;i<3000;i++);
	}
}
















