//LCD_STRING DISPLAY
#include<stm32f4xx.h>


unsigned char p[40]= "WELCOME TO PHYTECH BANGLORE";
unsigned int i;

void delay(int T)
{
	while(T--)
	{
		int i;
		for(i=0;i<3195;i++);
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

	if(command<4)
		delay(2);
	else
		delay(1);

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


int main()
{


	//port initialization
	RCC -> AHB1ENR |= 0x06;//enable clock for port B and C
	GPIOB -> MODER &= ~0x0000FC00;//clear pin
	GPIOB -> MODER |= 0x00005400;//set as output pin
	GPIOB -> ODR &= 0x0000FF1F;// making pin 5  6 7 zero

	GPIOC -> MODER &= ~0x0000FFFF;
	GPIOC -> MODER |= 0x00005555; // port c pin 0-7 configured as output pin


	//LCD init

	LCD_command(0x38);//8 bit data
	delay(200);
    LCD_command(0x80);//cursor right to left
	delay(200);
	LCD_command(0x01);//clear screen
	delay(200);
	//LCD_command(0x01);//clear screen
	//delay(200);
	LCD_command(0x0E);//turn on display
	delay(500);

	while(1)
	{
		for(i=0;p[i]!='\0';i++)
			LCD_data(p[i]);
		    delay(200);

	}
}

