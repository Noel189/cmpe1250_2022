

/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: Lab02- Number Entry / HEX Converter
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Noel Tesfe
// Details:       A more detailed explanation of the program is entered here
// Date:         07/12/2022
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
unsigned int value = 0;
unsigned int oldState = 0;
unsigned int rightOldState = 0;
unsigned int downOldState = 0;
unsigned int leftOldState = 0;
unsigned char addr = 0;
unsigned char v;
unsigned char segsDp = 0;
unsigned char addr1 = 0;
unsigned char addr2 = 1;
unsigned char addr3 = 2;
unsigned char addr4 = 3;
unsigned int bCount = 0;
unsigned char dp1 = 0;
unsigned char dp2 = 0;
unsigned char dp3 = 0;
unsigned char dp4 = 0;
unsigned char v1;
unsigned char v2;
unsigned char v3;
unsigned char v4;
unsigned int dCount = 5;
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
  (void)PIT_Init(20000000ul, PITTF_Ch1, 50);

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {

    int value = v1 * 1000 + v2 * 100 + v3 * 10 + v4;
    Segs_Normal(addr1, v1, dp1);
    Segs_Normal(addr2, v2, dp2);
    Segs_Normal(addr3, v3, dp3);
    Segs_Normal(addr4, v4, dp4);
    Segs_16H(value, Segs_LineBottom);

    {
      // get the current state of the switch
      int curState = SWL_Pushed(SWL_UP);

      if ((curState != oldState) && curState)
      {
        if (dp1)
        {
          if (++v1 > 9)
          {
            v1 = 0;
          }
        }
        if (dp2)
        {
          if (++v2 > 9)
          {
            v2 = 0;
          }
        }
        if (dp3)
        {
          if (++v3 > 9)
          {
            v3 = 0;
          }
        }
        if (dp4)
        {
          if (++v4 > 9)
          {
            v4 = 0;
          }
        }
        // if(++value > 9){
        //   value=0;
        // }
      }
      oldState = curState;
    }

    {
      // get the current state of the right switch
      int curState = SWL_Pushed(SWL_RIGHT);

      if ((curState != rightOldState) && curState)
      {
        // get the value
        //  v  = (value / 10) % 10;
        //  Segs_16D(v2,Segs_LineTop);
        //  unsigned int v3 = (value / 100) % 10;
        //  unsigned int v4 = (value / 1000) % 10;
        bCount++;
        if (bCount == 1)
        {
          dp1 = 1;
          dp2 = 0;
          dp3 = 0;
          dp4 = 0;

          Segs_Normal(addr1, v, dp1);
        }
        if (bCount == 2)
        {
          dp1 = 0;
          dp2 = 1;
          dp3 = 0;
          dp4 = 0;

          Segs_Normal(addr2, v, dp2);
        }
        if (bCount == 3)
        {
          dp1 = 0;
          dp2 = 0;
          dp3 = 1;
          dp4 = 0;

          Segs_Normal(addr3, v, dp3);
        }
        if (bCount == 4)
        {
          dp1 = 0;
          dp2 = 0;
          dp3 = 0;
          dp4 = 1;

          Segs_Normal(addr4, v, dp4);
        }

        if (++addr > 3)
        {

          addr = 0;
        }
      }

      rightOldState = curState;
    }

    {
      // get the current state of the switch
      int curState = SWL_Pushed(SWL_DOWN);

      if ((curState != downOldState) && curState)
      {
        if (dp1)
        {
          if (v1-- == 0)
          {
            v1 = 9;
          }
        }
        if (dp2)
        {
          if (v2-- == 0)
          {
            v2 = 9;
          }
        }
        if (dp3)
        {
          if (v3-- == 0)
          {
            v3 = 9;
          }
        }
        if (dp4)
        {
          if (v4-- == 0)
          {
            v4 = 9;
          }
        }
        // if(++value > 9){
        //   value=0;
        // }
      }
      downOldState = curState;
    }

    {
      // get the current state of the right switch
      int curState = SWL_Pushed(SWL_LEFT);

      if ((curState != leftOldState) && curState)
      {
        // get the value
        //  v  = (value / 10) % 10;
        //  Segs_16D(v2,Segs_LineTop);
        //  unsigned int v3 = (value / 100) % 10;
        //  unsigned int v4 = (value / 1000) % 10;
        bCount--;
        if (bCount == 1)
        {
          dp1 = 1;
          dp2 = 0;
          dp3 = 0;
          dp4 = 0;

          Segs_Normal(addr1, v, dp1);
        }
        if (bCount == 2)
        {
          dp1 = 0;
          dp2 = 1;
          dp3 = 0;
          dp4 = 0;

          Segs_Normal(addr2, v, dp2);
        }
        if (bCount == 3)
        {
          dp1 = 0;
          dp2 = 0;
          dp3 = 1;
          dp4 = 0;

          Segs_Normal(addr3, v, dp3);
        }
        if (bCount == 4)
        {
          dp1 = 0;
          dp2 = 0;
          dp3 = 0;
          dp4 = 1;

          Segs_Normal(addr4, v, dp4);
        }

        if (++addr > 3)
        {

          addr = 0;
        }
      }

      leftOldState = curState;
    }

    PIT_Sleep(20000000ul, PITTF_Ch1, 50); // inject some delay
  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
