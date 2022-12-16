

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
// #include "pll.h"
// #include <stdlib.h>
// #include <stdio.h>
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
unsigned int eventCount = 0;
unsigned char addr = 3;
unsigned int flagHex = 0;
unsigned int flagDec = 1;

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
  (void)PIT_Init(20000000ul, PITTF_Ch0, 100000);

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {

    if (PITTF_PTF0)
    {
      //    PIT_Sleep(20000000ul,PITTF_Ch1,100);
      // acknowledge the flag
      PITTF = PITTF_PTF0_MASK; // clears the flag
      eventCount++;
      if (eventCount == 10)
      {
        eventCount = 0;
        Segs_Clear_Lower();

        if (upCounter < 9999 && flagDec)
        {
          // count on the upper seg
          Segs_16D(upCounter++, Segs_LineTop);
        }
        if (flagHex)
        {
          Segs_16H(upCounter++, Segs_LineTop);
        }
        if (upCounter > 9999)
        {
          upCounter = 0;
        }
      }
    }

    // if center switch is pushed reset the count back to 0
    if (SWL_Pushed(SWL_CTR))
    {
      upCounter = 0;
    }

    if (SWL_Pushed(SWL_UP))
    {
      flagHex = 1;
      flagDec = 0;
      // yellow led will be on
      SWL_ON(SWL_YELLOW);
      SWL_OFF(SWL_GREEN); // turn of led green
    }

    if (SWL_Pushed(SWL_DOWN))
    {
      flagHex = 0;
      flagDec = 1;
      SWL_ON(SWL_GREEN);   // turn on green led
      SWL_OFF(SWL_YELLOW); // turn off yellow led
    }

    // bottom display, turn on each successive decimal points each 200ms
    if (eventCount == 2)
    {
      Segs_Custom(4, 0b00000000);
    }
    if (eventCount == 4)
    {
      Segs_Custom(5, 0b00000000);
    }
    if (eventCount == 6)
    {
      Segs_Custom(6, 0b00000000);
    }
    if (eventCount == 8)
    {
      Segs_Custom(7, 0b00000000);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
