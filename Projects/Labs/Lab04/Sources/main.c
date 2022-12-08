

/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: Lab04-  LCD String Functions, Dynamic Output.
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Noel Tesfe
// Details:       A more detailed explanation of the program is entered here
// Date:          07/12/2022
// Revision History :
//  each revision will have a date + desc. of changes

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "stdio.h"

// other system includes or your includes go here
// #include "pll.h"
// #include <stdlib.h>
// #include <stdio.h>
#include "Segs.h"
#include "sw_led.h"
#include "PLL.h"
#include "PIT.h"
#include "lcd.h"
/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void  GenerateBits(char * pbuff2);
void GenerateDecimal(char * pbuff3);
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
float  value =00000.0;
char buff[21]={0};
unsigned char dispon=1;
unsigned char curson=1;
unsigned char blinkon=1;
unsigned  int bitPos=0;
char buff2[21]={0};
unsigned char ix=2;
unsigned char iy=3;
char buff3[21]={0};
char buff4[21]={0};
/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Main Entry
/////////////////////////////////////////////////////////////////////////////
void main(void)
{
  // main entry point - these two lines must appear first
  _DISABLE_COP();

  EnableInterrupts;

  /////////////////////////////////////////////////////////////////////////////
  // one-time initializations
  /////////////////////////////////////////////////////////////////////////////

  PLL_To20MHz();
  SWL_Init();
  Segs_Init();
  Segs_Clear();
  lcd_Init();

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
        lcd_AddrXY(2,3);
        lcd_DispControl(dispon,curson,blinkon);
    // 
    {
  
    (void)sprintf(buff, "Count: %07.1f", value+=0.1);
    lcd_StringXY(0, 0, buff);
    PIT_Sleep(20000000ul,PITTF_Ch1,100);

    }
//display decimal DEC:
    {
        // GenerateDecimal(buff3);
         (void)sprintf(buff3,"DEC: %d%d%d%d%d",0,0,0,0,0);
         lcd_StringXY(0, 1, buff3);
    }
//display decimal HEX:
    {
        // GenerateDecimal(buff3);
         (void)sprintf(buff4,"HEX: %X%X%X%X",0,0,0,0,0);
         lcd_StringXY(0, 2, buff4);
    }

    {
     //centered at the bottom of the display show a 16bit binary number
     for(bitPos;bitPos<16;bitPos++){
    
      GenerateBits(buff2);
      // (void)sprintf(buff2[bitPos],"%d",0);
      lcd_StringXY(ix, iy, buff2);
   
     }
        
    }

    PIT_Sleep(20000000ul, PITTF_Ch1, 10);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void  GenerateBits(char * pbuff2)
{
 int i;
 for(i=0;i<16;i++){
  pbuff2[i]='0';
  pbuff2[16]=0;
 }
}

// void GenerateDecimal(char * pbuff3){
// int i;
//  for(i=0;i<5;i++){
//   pbuff3[i]='0';
//   pbuff3[5]=0;
//  }
// }
/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
