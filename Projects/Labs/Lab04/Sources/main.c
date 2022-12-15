

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
void GenerateBits(char *pbuff2);
void GenerateDecimal(char *pbuff3);
/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
float value = 00000.0;
char buff[21] = {0};
unsigned char dispon = 1;
unsigned char curson = 1;
unsigned char blinkon = 1;
unsigned int bitPos = 0;
char buff2[21] = {0};
char buff3[21] = {0};
unsigned char ix = 2;
unsigned char iy = 3;
// char buff3[21] = {0};
// char buff4[21] = {0};
unsigned int oldState = 0;
unsigned int leftOldState = 0;
unsigned int ctrOldState = 0;

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
    (void)PIT_Init(20000000ul, PITTF_Ch0, 100000ul);

    GenerateBits(buff2);
    lcd_StringXY(2, 3, buff2);
    lcd_DispControl(dispon, curson, blinkon);

    /////////////////////////////////////////////////////////////////////////////
    // main program loop
    /////////////////////////////////////////////////////////////////////////////
    for (;;)
    {
        // lcd_AddrXY(ix,iy);

        //
        if (PITTF_PTF0)
        {
            //    PIT_Sleep(20000000ul,PITTF_Ch1,100);
            // acknowledge the flag
            PITTF = PITTF_PTF0_MASK; // clears the flag
            (void)sprintf(buff, "Count: %07.1f", value += 0.1);
            lcd_StringXY(0, 0, buff);
        }

        // display decimal DEC:
        {
            // GenerateDecimal(buff3);

            (void)sprintf(buff3, "DEC: %05d", 0);
            lcd_StringXY(0, 1, buff3);
        }
        // display decimal HEX:
        {
            // GenerateDecimal(buff3);
            (void)sprintf(buff3, "HEX: %04X", 0);
            lcd_StringXY(0, 2, buff3);
            lcd_AddrXY(ix, iy);
        }

        // when the right switch button is pressed
        {
            int curState = SWL_Pushed(SWL_RIGHT);
            if ((curState != oldState) && curState)
            {

                lcd_AddrXY(++ix, iy);
            }

            oldState = curState;
        }

        // when the left switch button is pressed

        {
            int curState = SWL_Pushed(SWL_LEFT);
            if ((curState != leftOldState) && curState)
            {
                lcd_AddrXY(--ix, iy);
            }
            leftOldState = curState;
        }

        // when the center switch button is pressed
        {
            int curState = SWL_Pushed(SWL_CTR);
            if ((curState != ctrOldState) && curState)
            {
                buff2[ix - 2] = '1';
                lcd_StringXY(2, 3, buff2);
            }

            ctrOldState = curState;
        }

        PIT_Sleep(20000000ul, PITTF_Ch1, 10);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void GenerateBits(char *pbuff2)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        pbuff2[i] = '0';
        pbuff2[16] = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
