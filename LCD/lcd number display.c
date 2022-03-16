#include<stm32f4xx.h>
	void num(int p);

	unsigned int p=123;

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
		//delay(200);
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
		//LCD_command(0x80);  //Starting the cursur from first line


		//delay(200);


		//LCD_command(0xC0);//Entering the cursur into second line

        //LCD_data('P');

    	//delay(200);
		//LCD_command(0x80);
		//LCD_data(8+48);
		//LCD_data(9+48);
		num(p);
		while(1);
	}
}

