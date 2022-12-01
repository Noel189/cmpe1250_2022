#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "PLL.h"
#include "PIT.h"
#include "lcd.h"

//macros
//gotta be inputs, set R/W* high
#define lcd_RWUp DDRH=0;PORTK |=2;

//set R/W* low, //gotta be outputs
#define lcd_RWDown PORTK &=(~2);DDRH=0xFF;

#define lcd_EUp PORTK |=1;
#define lcd_EDown PORTK &=(~1);
#define lcd_RSUp PORTK |=4;
#define lcd_RSDown PORTK &=(~4);
#define lcd_MicroDelay {char __x=1;while(--__x);}


//wait for the LCD to be not busy (blocking)
//service function,private
void lcd_Busy(void)
{
   unsigned char inVal=0;
/* macros not functions*/
   lcd_RSDown;//Rs=0 instruction
   lcd_RWUp;//reading 

   do
   {
lcd_EUp;
lcd_MicroDelay;
inVal=PTH;
lcd_EDown;//release device
   }while(inVal & 0x80);//repeat until device is not busy
}

//send a byte to the inst reg of LCD on custom port
void lcd_Inst (unsigned char val)
{
    lcd_Busy();//wait for LCD to be not busy

    lcd_RWDown; //RW=0 writing
    lcd_RSDown;//RS=0 command

    PTH=val; //present data on port

    lcd_EUp;//strobe E   //and ... latch
    lcd_EDown; //idle state

}

void lcd_Init (void)
{
PTH=0b00000000;
DDRH=0b11111111;//data bus as outputs forwrite
PORTK &=0b11111000;//presets RS low, R/W low,EN low
DDRK|=0b00000111;//activate three control lines

PIT_Sleep(200000ul,PITTF_Ch1,100);//delay for 100ms

PTH=0b00111000;
PORTK |=0b00000001;//write a control byte
PORTK &=0b11111000;//resting state

PIT_Sleep(2000000ul,PITTF_Ch1,15);//delay for 15ms

PORTK |=0b00000001;//RS low, R/W low,EN high to write a control
PORTK  &=0b11111000;//resting state

PIT_Sleep(2000000ul,PITTF_Ch1,1); // delay for 1ms

lcd_Inst(0x38);
lcd_Inst(0x0c);
lcd_Inst(0x01);
lcd_Inst(0x06);

}

void lcd_Data (unsigned char val)
{
     lcd_Busy();//wait for LCD to be not busy

    lcd_RWDown; //RW=0 writing
    lcd_RSUp;//RS=1 data register selected

    PTH=val; //present data on port

    lcd_EUp;//strobe E   //and ... latch
    lcd_EDown; //idle state
}

void lcd_Addr (unsigned char addr)
{
    lcd_Inst(0x80|addr);
}

void lcd_AddrXY (unsigned char ix, unsigned char iy)
{
    if(iy==0){
        lcd_Addr(0+ix);
    }
    else if(iy==1){
        lcd_Addr(0x40+ix);
    }
    else if(iy==2){
        lcd_Addr(0x14+ix);
    }
    else if(iy==3){
        lcd_Addr(0x54+ix);
    }
}

void lcd_Clear (void)
{
    lcd_Inst(0x01);
}

void lcd_String (char * straddr)
{
    while(*straddr)
    {
       //call lcd_Data to display the value in the lcd
       lcd_Data(*straddr);
       ++straddr;
    }
}

void lcd_StringXY (unsigned char ix, unsigned char iy, char * straddr)
{
    //call lcd_AddrXY
    lcd_AddrXY(ix,iy);

    //call lcd_string
    lcd_String(straddr);
}

void lcd_DispControl (unsigned char dispon,unsigned char curon, unsigned char blinkon)
{
    unsigned char basecommand = 0b00001000; //display on/off, curson on/off,blink on/off

    if(dispon)
    {
        basecommand |=0b00000100;
    }
    if(curon)
    {
        basecommand |=0b00000010;
    }
    if(blinkon)
    {
       basecommand |=0b00000001;
    }

  //call lcd_inst
  lcd_Inst(basecommand);
}

void lcd_Home (void)
{
    //get the address back to ix=0,iy=0
    lcd_AddrXY(0,0);
}