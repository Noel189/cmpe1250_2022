

/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: Lab01- 16-bit Segs Functions
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Noel Tesfe
// Details:       A more detailed explanation of the program is entered here
// Date:          10/11/2022
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
    if (flag1 && count == 10)
    {
      Segs_16D(upCounter++, Segs_LineTop);
      if (upCounter == 10000)
      {
        upCounter = 0;
      }
      count = 0;
    }

    if (SWL_Pushed(SWL_UP))
    {
      flag2 = 1; // responds to the UP button press
      flag3 = 0;
      flag1 = 0;
      flag4 = 0;
    }
    if (SWL_Pushed(SWL_DOWN))
    {
      flag2 = 0;
      flag3 = 1; // responds to the DOWN button press
      flag1 = 0;
      flag4 = 0;
    }
    if (SWL_Pushed(SWL_CTR))
    {
      flag2 = 0;
      flag3 = 0;
      flag4 = 1; // responds to the CTR button  press
      flag1 = 0;
    }

    // pressing the UP button will swith the top display to HEX,and only the YELLOW LED will be on
    if (flag2 && count == 10)
    {
      SWL_OFF(SWL_GREEN);
      Segs_16H(upCounter++, Segs_LineTop);
      SWL_ON(SWL_YELLOW);
      if (upCounter == 0x2710)
      {
        upCounter = 0;
      }
      count = 0;
    }

    // pressing the DOWN button will switch the top display to DEC, and only the GREEN LED will be on
    if (flag3 && count == 10)
    {
      SWL_OFF(SWL_YELLOW);
      Segs_16D(upCounter++, Segs_LineTop);
      SWL_ON(SWL_GREEN);
      if (upCounter == 10000)
      {
        upCounter = 0;
      }
      count = 0;
    }

    // pressing the CTR switch,resets the count back to zero
    if (flag4 && count == 10)
    {
      Segs_Clear();
      SWL_OFF(SWL_YELLOW);
      SWL_OFF(SWL_GREEN);
      Segs_16D(upCounter, Segs_LineTop);
      if (upCounter == 0)
      {
        upCounter = 10000;
      }
      upCounter--;
      count = 0;
    }

    // bottom display, turn on each successive decimal points each 200ms
    if (count % 2 == 0)
    {
      if (addr <= 7)
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
