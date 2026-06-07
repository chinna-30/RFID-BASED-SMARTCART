#include"delayheader.h"

#define LCD_D 0XFF<<23
#define RS 1<<21
#define E 1<<22
void LCD_CMD(unsigned char);

void LCD_INIT(void)
{
	IODIR1 |= LCD_D|RS|E;// To select P0.0 to P0.9 configure as output
	LCD_CMD(0X01);// To clear the display
	LCD_CMD(0X02);//To set the cursor to home position
	LCD_CMD(0X0C);//Display ON | Cursor OFF
	LCD_CMD(0X38);//8 bit interface mode
}

void LCD_CMD(unsigned char cmd)
{
	IOCLR1=LCD_D;// Initially clear data in data pins
	IOSET1=cmd<<23;//Assign command byte to data pins
	IOCLR1=RS;//select command register mode RS=0				 
	IOSET1=E;//copy the data from data pins to lcd E=1
	delay_msec(2);// lcd internal operation mode is ON
	IOCLR1=E;//to re-latch next byte data 
}
void LCD_DATA(unsigned char d)
{
	IOCLR1=LCD_D;// Initially clear data in data pins
	IOSET1=d<<23;//Assign Data byte to data pins
	IOSET1=RS;//select Data register mode RS=1
	IOSET1=E;//copy the data from data pins to lcd E=1
	delay_msec(2);// lcd internal operation mode is ON
	IOCLR1=E;//to re-latch next byte data 
}

				 
/*******TO DISPLAY INTEGER ON LCD*******/

void LCD_INT(int n)
{
	unsigned char arr[5];
	signed char i=0;
	if(n==0)
	{
		LCD_DATA('0');
  }
	else
	{
		if(n<0)
		{
			LCD_DATA('-');
		  n=-n;
		}
		while(n>0)
		{
			arr[i++]=n%10;
			n=n/10;
    }
		for(--i;i>=0;i--)
		LCD_DATA(arr[i]+48);
	}
}

/*********TO DISPLAY STRING ON DISPLAY******/

void LCD_STR( char *s)
{
	unsigned char count=0;
	while(*s)
	{
		LCD_DATA(*s++);
		count++;
		if(count==20)
		LCD_CMD(0XC0);
  }
}

/********TO DISPLAY FLOAT ON LCD*******/

void LCD_FLT(float f)
{
	int temp;
	temp=f;
	LCD_INT(temp);
	LCD_DATA('.');
	temp=(f-temp)*1000;
	LCD_INT(temp);
}

/********TO SCROLL THE STRING*********/

void LCD_STRSCROL(unsigned char *s,unsigned char i)
{
	while(*s)
	{
		LCD_DATA(*s++);
		if(i==16)
			LCD_CMD(0Xc0);
		i++;
  }
}


