#include"lcdheader.h"

unsigned char UART0_RX(void);
void UART0_TX(unsigned char nBytes);
void UART0_CONFIG(void);
void UART0_STR(unsigned char *s);
void UART0_INT(int n);
void UART0_float(float f);


void UART0_CONFIG(void)
{
	PINSEL0|=0X5;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;	
}
void UART0_TX(unsigned char nBytes)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=nBytes;

}
unsigned char UART0_RX(void)
{// RDR Is 1 data received 0 empty
	while((U0LSR&0x1)==0);
	return U0RBR;
}
void UART0_STR(unsigned char *s)
{
	while(*s)
	UART0_TX(*s++);	
}
void UART0_INT(int n)
{
	unsigned char a[20];
	int i=0;

	if(n==0)
	UART0_TX('0');
	else
	{
		if(n<0){
		UART0_TX('-');
		n=-n;
		}

		 while(n>0)
		 {
		 	a[i++]=n%10;
			n/=10;
		 }

		 for(--i;i>=0;i--)
		 {
		 	UART0_TX(a[i]+48);
		 }
 	}
}
void UART0_float(float f)
{
	int temp=f;
	UART0_INT(temp);
	UART0_TX('.');
	temp=(f-temp)*1000;
	UART0_INT(temp);
}
