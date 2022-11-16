

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
unsigned int downCounter = 0xFFFF;
char addr=0;
unsigned int loopCount=0;
unsigned int changeCounter=0;
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

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    // Tier-1
    if (SWL_Pushed(SWL_CTR))
    {
      for (;;)
      {
        PIT_Sleep(20000000ul, PITTF_Ch1, 100);
        Segs_16H(upCounter++, Segs_LineTop);
        Segs_16H(downCounter--, Segs_LineBottom);
      }
    }
    else
    {
      // Segs_8H(2, 7);
      // Segs_Custom(1, 0b10001001);
      // Segs_Custom(2, 0b11110000);
      // Segs_Custom(5, 0b10000011);
      // Segs_Custom(6, 0b10110001);
      // Segs_Normal(4, '3', Segs_DP_OFF);
      // Segs_16D(524,Segs_LineBottom);
    }

    //Tier-2
     Segs_Clear_Upper();
     Segs_Custom(addr,0b11111010);
     PIT_Sleep(20000000ul,PITTF_Ch1,100);
     
     //look for loop count
     if(++loopCount>9)
     {
      loopCount=0;
      //look for switch presses
      if(SWL_Pushed(SWL_LEFT))
      {
        if(addr==0)
        {
          addr=4;
          Segs_SayErr(Segs_LineBottom);
        }
        if(addr>0)
        {
          addr--;
          ++changeCounter;
          Segs_16H(changeCounter,Segs_LineBottom);
        }
      }
      if(SWL_Pushed(SWL_RIGHT))
      {
        if(addr==3)
        {
          addr=-1;
        }
        if(addr<4)
        {
          addr++;
             ++changeCounter;
          Segs_16H(changeCounter,Segs_LineBottom);
        }
      }

     }

  }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
