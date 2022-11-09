

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
unsigned int downCounter = 9999;
unsigned int addr = 4;
unsigned int flag=0;
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
    // if (SWL_Pushed(SWL_CTR))
    // {

      PIT_Sleep(20000000ul, PITTF_Ch1, 100);
      count++;

      if (count==10)
      {
        Segs_16D(upCounter++, Segs_LineTop);
        count = 0;
      }
  // }
      // if (SWL_Pushed(SWL_DOWN))
      // {
      //  // for(;;){
      // PIT_Sleep(20000000ul, PITTF_Ch0, 100);
      //   Segs_16D(upCounter++, Segs_LineTop);
      //   SWL_ON(SWL_GREEN);
      //   SWL_OFF(SWL_YELLOW);
      // //  }
  
   

      // }
    //   if (SWL_Pushed(SWL_UP))
    //   {
    //  // for(;;){
    //   PIT_Sleep(20000000ul, PITTF_Ch0, 100);
    //    Segs_16H(upCounter++, Segs_LineTop);
    //     SWL_ON(SWL_YELLOW);
    //     SWL_OFF(SWL_GREEN);
    // //  }
     
        
 
    //   }
      // if (SWL_Pushed(SWL_CTR))
      // {
      //      count=0;
      //   downCounter = upCounter;
      //   for (;;)
      //   {

      //     PIT_Sleep(20000000ul, PITTF_Ch0, 100);
      //     count++;

      //     if (count == 10)
      //     {
      //       Segs_16D(downCounter, Segs_LineTop);
      //       downCounter--;
      //       count=0;
      //     }
      //   }
    

    // Segs_16H(downCounter--, Segs_LineBottom);

    // bottom display, turn on each successive decimal points each 200ms
    //   if(count%2==0){
    //       if(addr<=7)
    //   Segs_Custom(addr++, 0b00000000);
    //   }
  }
  // }
}


/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
