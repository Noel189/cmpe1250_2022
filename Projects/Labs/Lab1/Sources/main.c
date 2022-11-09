

/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: ICA10- Seven Segment Display Basic Functions
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Noel Tesfe
// Details:       A more detailed explanation of the program is entered here
// Date:          03/11/2022
// Revision History :
//  each revision will have a date + desc. of changes

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>
#include "Segs.h"
#include "sw_led.h"
#include "PLL.h"
#include "PIT.h"
/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
unsigned int upCounter = 0;
unsigned int count = 0;
// unsigned long downCounter = 9999;
unsigned char addr = 4;
unsigned int flag1 = 1;
unsigned int flag2 = 0;
unsigned int flag3 = 0;
unsigned int flag4 = 0;
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

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {

    PIT_Sleep(20000000ul, PITTF_Ch1, 100);
    count++;
    if (flag1&&count==10)
    {
      Segs_16D(upCounter++, Segs_LineTop);
      if(upCounter==1000)
      {
        upCounter=0;
      }
      count=0;
    }

    if (SWL_Pushed(SWL_UP))
    {
      flag2 = 1;
      flag3 = 0;
      flag1 = 0;
     
    }
    if (SWL_Pushed(SWL_DOWN))
    {
      flag2 = 0;
      flag3 = 1;
      flag1 = 0;
     
    }
    if (SWL_Pushed(SWL_CTR))
    {
      flag2 = 0;
      flag3 = 0;
      flag4 = 1;
      flag1 = 0;
    }

    if (flag2&&count==10)
    {
       SWL_OFF(SWL_GREEN);
      Segs_16H(upCounter++, Segs_LineTop);
      SWL_ON(SWL_YELLOW);
      count=0;
      if(upCounter==0x2710){
        upCounter=0;
      }
    }

    if (flag3&&count==10)
    {
       SWL_OFF(SWL_YELLOW);
      Segs_16D(upCounter++, Segs_LineTop);
       SWL_ON(SWL_GREEN);
      count=0; 
        if(upCounter==1000){
        upCounter=0;
      }
    }

    if (flag4&&count==10)
    {
      Segs_16D(upCounter--, Segs_LineTop);
      if(upCounter==0)
      {
        upCounter=9999;
      }
      count=0;
    }

    // bottom display, turn on each successive decimal points each 200ms
      if(count%2==0){
          if(addr<=7)
         Segs_Custom(addr++, 0b00000000);
      }
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
