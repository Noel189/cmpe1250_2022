/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Simon Walker
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void RED(uint bOn);
void GREEN(uint bOn);
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
 static uint uiMainLoopCount = 0;
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

  PT1AD1 &= 0x1F;
  DDR1AD1 = 0xE0;
  ATD1DIEN1 |= 0x1F;

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
   
    ++uiMainLoopCount;
    RED(uiMainLoopCount < 0x1000);

    GREEN(uiMainLoopCount >= 0x1000);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void RED(uint bOn)
{
  if (bOn && !!bOn)
  {
    PT1AD1 |= (0b00000001 << (7));
  }
  else
  {
    PT1AD1 &= 0x7F;
  }
}

void GREEN(uint bOn)
{
  if (bOn)
  {
    PT1AD1 |= 0x20;
  }
  else
  {
    PT1AD1 &= 0b11011111;
  }
}
/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
