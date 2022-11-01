/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: LED and Switch Library, makes use of a library to operate on the led's and push buttons
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Noel Tesfe
// Details:       A more detailed explanation of the program is entered here
// Date:          26-09-2022
// Revision History :
//  each revision will have a date + desc. of changes

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>
#include "sw_led.h"

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
 unsigned int pushCount = 0;
unsigned int leftButton = 0, midButton = 0, rightButton = 0;
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
  SWL_Init();

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {

    // Tier-1
    // if (SWL_Pushed(SWL_LEFT))
    // {
    //   SWL_ON(SWL_RED);
    // }
    // else
    // {
    //   SWL_OFF(SWL_RED);
    // }
    // if (SWL_Pushed(SWL_CTR))
    // {
    //   SWL_ON(SWL_YELLOW);
    // }
    // else
    // {
    //   SWL_OFF(SWL_YELLOW);
    // }
    // if (SWL_Pushed(SWL_RIGHT))
    // {
    //   SWL_ON(SWL_GREEN);
    // }
    // else
    // {
    //   SWL_OFF(SWL_GREEN);
    // }

    // Tier - 2
    // if (SWL_Pushed(SWL_LEFT))
    // {
    //   SWL_ON(SWL_RED);
    // }
    // if (SWL_Pushed(SWL_CTR))
    // {
    //   SWL_ON(SWL_YELLOW);
    // }
    // if (SWL_Pushed(SWL_RIGHT))
    // {
    //   SWL_ON(SWL_GREEN);
    // }
    // if (SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_DOWN))
    // {
    //   SWL_OFF(SWL_RED);
    //   SWL_OFF(SWL_YELLOW);
    //   SWL_OFF(SWL_GREEN);
    // }

    // Tier - 3

    if (pushCount < 2)
    {

      if (SWL_Pushed(SWL_LEFT))
      {
        SWL_ON(SWL_RED);
        if (!leftButton)
        {
          ++pushCount;
          leftButton = 1;
        }
      }
    }

    if (pushCount < 2)
    {
      if (SWL_Pushed(SWL_CTR))
      {
        SWL_ON(SWL_YELLOW);
        if (!midButton)
        {
          ++pushCount;
          midButton = 1;
        }
      }
    }

    if (pushCount < 2)
    {
      if (SWL_Pushed(SWL_RIGHT))
      {
        SWL_ON(SWL_GREEN);
        if (!rightButton)
        {
          ++pushCount;
          rightButton = 1;
        }
      }
    }

    if (SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_DOWN))
    {
      SWL_OFF(SWL_RED);
      SWL_OFF(SWL_YELLOW);
      SWL_OFF(SWL_GREEN);
      pushCount = 0;
      leftButton = 0;
      midButton = 0;
      rightButton = 0;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
