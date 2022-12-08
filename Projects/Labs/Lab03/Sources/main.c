

/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: Lab03- LCD Control Functions
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

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
unsigned char dispon = 1;
unsigned char curson = 1;
unsigned char blinkon = 0;
unsigned int oldState = 0;
unsigned int leftOldState = 0;
unsigned int downOldState = 0;
unsigned int upOldState = 0;
unsigned int ctrOldState = 0;
char addrx = 0;
char addry = 0;
unsigned int counter = 0;
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
  (void)PIT_Init(20000000ul, PITTF_Ch1, 50);

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    lcd_AddrXY(addrx, addry);
    lcd_DispControl(dispon, curson, blinkon);
    {
      int curState = SWL_Pushed(SWL_RIGHT);
      if ((curState != oldState) && curState)
      {

        if ((++addrx == 20))
        {
          SWL_ON(SWL_RED);
          addrx = 19;
        }
      }

      oldState = curState;
    }

    {
      int curState = SWL_Pushed(SWL_LEFT);
      if ((curState != leftOldState) && curState)
      {

        if ((--addrx) < 0)
        {
          SWL_ON(SWL_RED);
          addrx = 0;
        }
      }

      leftOldState = curState;
    }

    // push swled down
    {
      int curState = SWL_Pushed(SWL_DOWN);
      if ((curState != downOldState) && curState)
      {
        if (++addry > 3)
        {
          SWL_ON(SWL_RED);
          addry = 3;
        }
      }

      downOldState = curState;
    }
    // push swled up
    {
      int curState = SWL_Pushed(SWL_UP);
      if ((curState != upOldState) && curState)
      {
        if (--addry < 0)
        {
          SWL_ON(SWL_RED);
          addry = 0;
        }
      }

      upOldState = curState;
    }

    // center swled button pressed
    {
      int curState = SWL_Pushed(SWL_CTR);
      if ((curState != ctrOldState) && curState)
      {
        lcd_Data(rand() % 26 + 'A'); // picks random letters A-Z

        Segs_16D(++counter, Segs_LineTop);
        if (counter == 15)
        {
          lcd_Home();
          lcd_Clear();
          addrx=0;
          addry=0;
          counter=0;
          
        }
      }
      ctrOldState = curState;
    }
    PIT_Sleep(20000000ul, PITTF_Ch1, 50);
    SWL_OFF(SWL_RED);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
