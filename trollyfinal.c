#include <lpc21xx.h>
#include <string.h>
#include "UART0header.h"
#include"title.h"

#define ADD_MODE     1
#define REMOVE_MODE  2
#define BILL_MODE    3

#define SW1 8
#define SW2 9
#define SW3 10
#define SW4	11

struct product
{
    char ID[13];
    char name[20];
    int price;
    int qty;
};

struct product p[] =
{
    {"060067836E8C","SOAP",35,0},
    {"0600676AD5DE","MILK",60,0},
    {"060002498FC2","BISCUIT",20,0},
    {"0600680E1D7D","CHOCOLATE",40,0}
};

char payment_card[]="060067882CC5";
char gate_card[]="05005351C6C1";

volatile char rfid[13];
volatile int pos = 0;
volatile int flag = 0;
volatile int OP = 1;
volatile int item=0;
volatile int total = 0;
volatile char mode = 0;
volatile int payment_done=0;

int search_tag(char *tag);
void gateopen(void);

void UART0_ISR(void) __irq
{
    char ch;
	ch = U0RBR;
	rfid[pos++] = ch;
	if(pos == 12)
    {
       rfid[12] = '\0';
       pos = 0;
       flag = 1;
    }
	VICVectAddr = 0;
}

int main()
{
	int i;int cart_items=0;
	int index;
	
	UART0_CONFIG();
    LCD_INIT();
	
	IODIR0 |= 1<<7;
	IOSET0 = 1<<7;
    IODIR0 &= ~((1<<SW1)|(1<<SW2)|(1<<SW3));

    VICIntSelect = 0;
    VICVectCntl0 = (1<<5) | 6;
    VICVectAddr0 = (unsigned long)UART0_ISR;

    U0IER = 0x01;
    VICIntEnable = (1<<6);

    LCD_CMD(0x01);
	display_title();

while(1)
{
		
		if(((IOPIN0>>SW4)&1)==0)
		{
			OP=0;
			gateopen();
		}
		if(((IOPIN0>>SW1)&1)==0)
    	{
			OP=1;
		}	
		if(OP)
		{
			mode = ADD_MODE;
			LCD_CMD(0X01);
			LCD_CMD(0x80);
			LCD_STR(" READY TO SCAN.....");
			delay_msec(100);
		}	
		if((((IOPIN0>>SW2)&1)==0)&&(item>0))
    	{
			OP=0;
			mode = REMOVE_MODE;
		    LCD_CMD(0x01);
		    LCD_STR("REMOVE MODE");
		    delay_msec(500);
		}
	  	if(((IOPIN0>>SW3)&1)==0)
    	{
			OP=0;cart_items=0;
      		mode = BILL_MODE;
		  	LCD_CMD(0x01);
			for(i=0;i<4;i++)
			{
				cart_items += p[i].qty;
				if(p[i].qty)
				{
					LCD_CMD(0x01);
					LCD_CMD(0x80);LCD_STR("PRODUCT :");
					LCD_CMD(0x89);LCD_STR(p[i].name);
					LCD_CMD(0xC0);LCD_STR("PRICE   :");
					LCD_CMD(0xC9);LCD_INT(p[i].price);
					LCD_CMD(0x94);LCD_STR("QUANTITY:");
					LCD_CMD(0x9d);LCD_INT(p[i].qty);
					LCD_CMD(0XD4);LCD_STR("Rupees  :");
					LCD_INT(p[i].qty * p[i].price);
					delay_sec(2);
				}		   
			}
			if(cart_items)
			{
					LCD_CMD(0x01);
					LCD_STR("TOTAL BILL :");LCD_INT(total);
					delay_sec(2);
					LCD_CMD(0XC0);LCD_STR("PAYMENT PENDING");
					LCD_CMD(0x94);LCD_STR("***READY TO SCAN***");
					LCD_CMD(0XD4);LCD_STR("TAP YOUR CARD");
			}
			else
			{
					LCD_STR("   BUY ATLEAST ONE  ");
					delay_sec(2);
					LCD_CMD(0X94);LCD_STR("PRESS ADDMODE TO BUY");
					delay_sec(5);
			}
		}
		if(flag)
		{
					flag = 0;
					if(mode == BILL_MODE)
					{
						while(1)
						{
							if(strcmp((char *)rfid,payment_card)==0)
							{
								LCD_CMD(0x01);
								LCD_STR("*****PAYMENT OK*****");
								IOSET0=1<<7;
								total = 0;
								for(i=0;i<4;i++)
								p[i].qty = 0;
							
								payment_done=1;
								LCD_CMD(0xd4);LCD_STR("GET YOUR GATE TAG");
								delay_sec(2);
								OP=0;flag=0;
								break;
							}
							else
							{
								LCD_CMD(0x01);LCD_STR("INVALID CARD");
								
								LCD_CMD(0xC0);LCD_STR("NO BALANCE");
								delay_sec(2);
								LCD_CMD(0x01);LCD_STR("TAP YOUR CARD");
								while(flag==0);
								flag=0;
							}				
						}	 
					}
					else
					{					
						index = search_tag((char *)rfid);
						if(index != -1)
						{
							if(mode == ADD_MODE)
							{
								p[index].qty++;
								total += p[index].price;
								item++;
								LCD_CMD(0x01);
								LCD_CMD(0x80);LCD_STR("PRODUCT :");
								LCD_CMD(0x89);LCD_STR(p[index].name);
								LCD_CMD(0xC0);LCD_STR("PRICE   :");
								LCD_CMD(0xC9);LCD_INT(p[index].price);
								LCD_CMD(0x94);LCD_STR("QUANTITY:");
								LCD_CMD(0x9d);LCD_INT(p[index].qty);
								LCD_CMD(0xD4);LCD_STR("   PRODUCT  ADDED   ");
								delay_sec(2);
								LCD_CMD(0xD4);LCD_STR("                    ");
							}
							else if(mode == REMOVE_MODE)
							{
								if(p[index].qty > 0)
								{
									p[index].qty--;
									total -= p[index].price;
									LCD_CMD(0x01);LCD_STR("PRODUCT :");
									LCD_CMD(0x89);LCD_STR(p[index].name);
									LCD_CMD(0xc0);LCD_STR("QUANTITY:");
									LCD_CMD(0xC9);LCD_INT(p[index].qty);
									LCD_CMD(0xD4);LCD_STR("   PRODUCT REMOVED  ");
									delay_sec(1);
									LCD_CMD(0xD4);LCD_STR("                    ");
								}
							}
							else
							{
								LCD_CMD(0x01);
								if(mode==0)
								LCD_STR("PRESS ADD MODE");
								else
								LCD_STR("INVALID TAG");
							}
						}
					}
			  }	
	   }
}
int search_tag(char *tag)
{
    int i;
    for(i=0;i<4;i++)
    {
        if(strcmp(tag,p[i].ID)==0)
        return i;
    }
    return -1;
}
void gateopen(void)
{
		LCD_CMD(0x01);
		OP=0;mode=0;
		LCD_STR("SCAN GATE CARD");
		if(item == 0)
		{		
			OP=0;
			delay_sec(2);
			LCD_CMD(0x01);LCD_STR("GATE OPENED  THANK  ");
			LCD_CMD(0x94);LCD_STR("  YOU FOR VISITING  ");
			LCD_CMD(0XD4);LCD_STR("NEXT TIME TRY TO BUY");
			while(OP==0);
			delay_sec(2);
			return;
		}
	
		while(payment_done==0)
		{
				
			LCD_CMD(0x01);LCD_STR("THEFT ALERT!!!");
			LCD_CMD(0xC0);LCD_STR(" BILL NOT PAID      ");
			LCD_CMD(0XD4);LCD_STR("LED ON AND BUZZER ON");
			IOCLR0 = 1<<7; // buzzer
			if(((IOPIN0>>SW3)&1)==1);
			return;
		}
		flag=0;
		while(flag==0);
		if(strcmp((char *)rfid, gate_card) == 0)
		{
			if(payment_done)
			{		
				flag=0;
				IOSET0=1<<7;
				LCD_CMD(0x01);LCD_STR("     GATE OPENED     ");
				delay_sec(2);
				LCD_CMD(0xC0);LCD_STR("     THANK YOU       ");
				LCD_CMD(0XD4);LCD_STR("  HAVE A NICE DAY    ");
				item = 0;
				payment_done = 0;
				while(flag==0);
			}
			else
			{
				IOSET0 = 1<<7;
				LCD_CMD(0x01);
				LCD_STR("PAY FIRST");
				delay_sec(2);
				IOCLR0=1<<7;
			}
		}
		else
		{		
			delay_sec(3);
			LCD_CMD(0x01);
			LCD_STR("THEFT ALERT!!!!");				
			LCD_CMD(0XD4);LCD_STR("LED ON AND BUZZER ON");
			IOCLR0 = 1<<7; // buzzer
		}
}
