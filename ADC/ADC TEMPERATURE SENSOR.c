//ADC TEMPERATURE SENSOR
#include<stm32f4xx.h>
unsigned int result,x,i;
unsigned char p;
 //volt;// temp;
unsigned int temp,volt;
void LCD_data(char data);


void delay(int T)
{
	while(T--)
	{
		int i;
		for(i=0;i<3195;i++);
	}
}

void string_send(char  *p)
{
	while(*p !='\0')
		{
			LCD_data(*p);
			p++;
		}
	}

void LCD_command(unsigned char command)
{
	GPIOB->ODR &= 0xFF9F;//RS= 0;
	GPIOB->ODR &= 0xFFBF;//R/W = 0;

	GPIOC->ODR = command;
	GPIOB->ODR |= 0x0080;//E = 1
	delay(50);
	GPIOB->ODR &= ~0x0080;//clear E



}

void LCD_data(char data)
{
	GPIOB->ODR |= 0x0020;//RS= 1;
	GPIOB->ODR &= 0xFFBF;//R/W = 0;
	GPIOC->ODR = data;//put data
	GPIOB->ODR |= 0x0080;//E = 1
	delay(50);
	GPIOB->ODR &= ~0x0080;//clear E
	delay(1);
}

void num( int p)
	{
		unsigned int k,w,b=1;
		k=p;
		while(k>=10)
		{
			b=b*10;
			k=k/10;
		}
		while(b>=1)
		{
		w = p/b;
		p=p%b;
		b=b/10;
		LCD_data(w+48);
		}

	}
void USART2_init(void)
{
	RCC->AHB1ENR |= 1;           //ENABLE GPIOA CLOCK
	RCC->APB1ENR |= 0x20000;      //ENABLE USART2 CLOCK

	/* CONFIGURE PA2 FOR USART2_TX */

	GPIOA->AFR[0] &= ~0x0F00;     //CLEAR PIN
	GPIOA->AFR[0] |= 0x700;        // ALT7 FOR USART2
	GPIOA->MODER &= 0x30;          // CLEAR PIN
	GPIOA->MODER |= 0x700;          //SET PIN AS OUTPUT FOR USART2
	USART2->BRR |= 0x683;            // BAUD RATE
	USART2->CR1 |= 0x8;                //TE=1
	USART2->CR1 |= 0x2000;              //UE=1
}

int USART2_write(int ch)           // WRITE A CHARACTER TO USART
{
	while(!(USART2->SR&0x0080)){}    //WAIT UNTIL THE TX BUFFER IS EMPTY
	USART2->DR = ch;
	return ch;

}



int main()
{


	/*PORT INITIALIZATION FOR LCD*/


	RCC -> AHB1ENR |= 0x06;                   //ENABLE CLOCK FOR PORT B AND C
	GPIOB -> MODER &= ~0x0000FC00;           //CLEAR PIN
	GPIOB -> MODER |= 0x00005400;            //SET AS OUTPUT PINS 5 6 AND 7
	GPIOB -> ODR &= 0x0000FF1F;             // MAKING PIN 5  6 7 ZERO

	GPIOC -> MODER &= ~0x0000FFFF;          //CLEAR PIN
	GPIOC -> MODER |= 0x00005555;         // PORT C PIN 0-7 CONFIGURED AS OUTPUT PIN

	/*SET PIN PA1 FOR ANALOG INPUT*/
	RCC->AHB1ENR |= 1;                   //ENABLE GPIOA CLOCK
	GPIOA->MODER |= 0xC;                 // PA1 AS ANALOG INPUT



	/*SET ADC1*/

	RCC->APB2ENR |= 0x00000100; //ENABLE ADC1 CLOCK
	ADC1->CR2 =0;              //  DISABLE THE ADC
	ADC1->SQR3 =1;             //1ST CONVERSION IN REGULAR SEQUENCE
	ADC1->SQR1 =0;              //CONVERSION SEQUENCE LENGTH 1
	ADC1->CR2 |=1;              //ENABLE ADC

	USART2_init();




	//LCD init

	LCD_command(0x38);//8 bit data
	delay(200);
	LCD_command(0x06);//cursor  left to right
	delay(200);

    LCD_command(0x01);//clear screen
	delay(200);

	LCD_command(0x0E);//turn on display
	delay(500);


	LCD_command(0x80);//cursor right to left
	delay(200);

	string_send("TEMPERATURE");

	//	LCD_command(0xC0);
	//	LCD_data(num);

	while(1)
	{
		LCD_command(0xC0);
		ADC1->CR2 |= 0x40000000;                    //START CONVERSION
		while(!(ADC1->SR&2)){}                       //WAIT FOR CONVERSION COMPLETE
		result = ADC1->DR;                           //READ CONVERSION RESULT
		volt = (float)(result/4096.0f)*3300.0f;
		temp = (float)(volt-500)/10;

		num(temp);
		x=USART2_write(temp);

		delay(50);




	}
}

