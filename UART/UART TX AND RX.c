/*UART TX AND RX
 * uart_lcd program::
 * taking data from mincom terminal or port and print into a LCD
 *
 */

#include<stm32f4xx.h>

char buf[100];
int i;
void uart2_init()
{
	RCC->AHB1ENR |=0x1;			//peripheral clock enable of GPIOA
	RCC->APB1ENR |= 0x20000;	//USART2 clock enable
	GPIOA->MODER &= ~0xf0;
	GPIOA->MODER |=0xA0;		//set Alternate function mode of PA2 =TX; PA3 =RX;
	GPIOA->AFR[0] &= ~0xFF00;			//clear bit
	GPIOA->AFR[0] |=0x7700;		//configure USART2 alternate function

	/*set buadrate 9600 =16000000/9600 = 1666.666 eqals to 16667 convert hex is 0x683;	*/
	USART2->BRR =0x683;

	USART2->CR1 |= 0x8;			//TE :Transmitter enable
	USART2->CR1 |= 0x4;			//RE: Receiver enable
	USART2->CR1 |= 0x2000;		//UE: USART enable
}
void uart2_write(unsigned char data)
{
	while(!(USART2->SR & 0x80));
	USART2->DR = (data);// & 0xff);

}
char Uart2_recieve()
{
	unsigned char ret_data;

	while(!(USART2->SR & 0x20));	//RXNE bit monitoring
	ret_data = USART2->DR;
	

	return (ret_data);
}

void uart_string_write(char *ptr_str)
{
	for(;*(ptr_str+i)!='\0';i++)
	{
		uart2_write(*(ptr_str+i));
	}
}

void delay(unsigned int sec)
{
	for(;sec>0;sec--)
	{
		for(int i=0;i<300;i++);
	}
}

int main()
{
	unsigned char data;
	uart2_init();

	while(1)
	{
	//	uart2_write('m');
		//delay(100);
	//	uart2_write('i');
	//	delay(100);
		data = Uart2_recieve();
//		delay(2);
		uart2_write(data);
		//uart_string_write();
	}
}
