void LCD_STR_DELAY(char *s)
{
    while(*s)
    {
        LCD_DATA(*s++);
        delay_msec(100);   // Delay between characters
    }
}

void display_title(void){
LCD_CMD(0x01);

LCD_CMD(0x80);   // Line 1
LCD_STR_DELAY("SMART CART : RFID");

LCD_CMD(0xC0);   // Line 2
LCD_STR_DELAY("BASED ANTI THEFT ");

LCD_CMD(0x94);   // Line 3
LCD_STR_DELAY("INTELLIGENT SHOPPING");

LCD_CMD(0xD4);   // Line 4
LCD_STR_DELAY("and BILLING SYSTEM");
delay_sec(1);	
}
