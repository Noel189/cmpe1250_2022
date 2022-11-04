#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "Segs.h"

#define Segs_WLATCH  \
   PORTA &= (~0x01); \
   PORTA |= 0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0X02;

void Display(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int addr);

// setup ports to speak with 7-segs
void Segs_Init(void)
{
   // ensure port pins high
   PORTA |= 0X03;

   // configure direction of port pins as outputs
   DDRA |= 0X03;

   // configure direction of port pins as outputs
   DDRB = 0Xff;
   Segs_Clear();
}

void Segs_Normal(unsigned char Addr, unsigned char Value, Segs_DPOption dp)
{
   // trim address to range
   Addr &= 0x07;

   // Bank A,Normal op, Decode,Hex,No Data Coming
   Addr |= 0b01011000;

   // suppressing decimal point
   if (dp)
   {
      Value &= (~0x80);
   }
   else
   {
      Value |= 0x80;
   }

   // present control byte
   PORTB = Addr;
   Segs_MH // present comman with mode high

       Segs_WLATCH // latch commmand

           // present data
           PORTB = Value;
   Segs_ML // present data with mode low

       Segs_WLATCH // latch data
}

// control segs manually
void Segs_Custom(unsigned char Addr, unsigned char Value)
{
   // trim address to range
   Addr &= 0x07;

   // Bank A,Normal op, Decode,Hex,No Data Coming
   Addr |= 0b01111000;

   //    //suppressing decimal point
   //    if(dp)
   //    {
   //     Value &=(~0x80);
   //    }
   //    else{
   //      Value |=0x80;
   //    }

   // present control byte
   PORTB = Addr;
   Segs_MH // present comman with mode high

       Segs_WLATCH // latch commmand

           // present data
           PORTB = Value;
   Segs_ML // present data with mode low

       Segs_WLATCH // latch data
}

void Segs_Clear(void)
{
   unsigned char i = 0;
   for (; i < 8; i++)
   {
      Segs_Custom(i, 0b10000000);
   }
}

// show the 8-bit value starting on the digit as addr (0-6)
void Segs_8H(unsigned char Addr, unsigned char Value)
{
   // separate in to two nibbles
   unsigned char vLower = Value & 0x0F;
   unsigned char vUpper = Value >> 4;
   // call segs normal
   Segs_Normal(Addr, vUpper, Segs_DP_OFF);

   // sanitize the address
   if (Addr == 7)
      Addr = 0;
   else
      Addr = Addr + 1;

   Segs_Normal(Addr, vLower, Segs_DP_OFF);
}

// show a 16-bit value on the upper or lower display
void Segs_16H(unsigned int Value, Segs_LineOption Line)
{
   unsigned int v1;
   unsigned int v2;
   unsigned int v3;
   unsigned int v4;
   unsigned int addr;

   v1 = Value & 0x000F;
   Value = Value >> 4;
   v2 = Value & 0x000F;
   Value = Value >> 4;
   v3 = Value & 0x000F;
   Value = Value >> 4;
   v4 = Value;

   if (Line == 0)
   {
      addr = 0;
      Display(v1, v2, v3, v4, addr);
   }
   else if (Line == 1)
   {
      addr = 4;
      Display(v1, v2, v3, v4, addr);
   }
}

void Display(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int addr)
{
   // call segs normal
   Segs_Normal((unsigned char)addr, (unsigned char)v4, Segs_DP_OFF);
   addr += 1;
   Segs_Normal((unsigned char)addr, (unsigned char)v3, Segs_DP_OFF);
   addr += 1;
   Segs_Normal((unsigned char)addr, (unsigned char)v2, Segs_DP_OFF);
   addr += 1;
   Segs_Normal((unsigned char)addr, (unsigned char)v1, Segs_DP_OFF);
}