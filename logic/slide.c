// (C) Jacko edited to turn into a slide rule LINE2
// *************************************************************************************************
//
//      Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
//
//
//        Redistribution and use in source and binary forms, with or without
//        modification, are permitted provided that the following conditions
//        are met:
//
//          Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//
//          Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the
//          distribution.
//
//          Neither the name of Texas Instruments Incorporated nor the names of
//          its contributors may be used to endorse or promote products derived
//          from this software without specific prior written permission.
//
//        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//        OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//        SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//        LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//        DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//        THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//        OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Time functions.
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "ports.h"
#include "display.h"

// logic
#include "menu.h"
#include "slide.h"
#include "user.h"

// *************************************************************************************************
// Prototypes section
void mx_slide();
void sx_slide();

// *************************************************************************************************
// Defines section

// *************************************************************************************************
#define INV_LOG_E100  3643126
#define FOUR_INV_PI		21361414

/* Functions available, scaled if necessary, and to 4 digits.

IR - Inverse Root 	1/sqrt(x)
SQ - Square			x*x
IV - Inverse 		1/x
RT - Root 		sqrt(x)
RL - Relativity	sqrt(1-x*x)
BD - Bend 		x/(1+sqrt(1+x*x))
LG - Log		log(x)		scaled to provide maximum at 100
AT - Arc Tangent	atan(x)		scaled to provide maximum for 45 degrees

*/

u32 mul16(u16 a, u16 b)
{
	return (u32)a * (u32)b;
}

u8 negative(s32 *x) {
	if(*x < 0) {
		*x = -(*x);
		return 1;
	}
	return 0;
}

/* a 32*32 bit multiply to 32 bit, using 8.24 bit fixed point */
s32 mulfix(s32 x, s32 y) {
	u8 sign = negative(&x) ^ negative(&y);
	s32 t = mul16((u16)(x), (u16)(y))>>24;
	t += mul16((u16)(x>>16), (u16)(y))>>8;
	t += mul16((u16)(x), (u16)(y>>16))>>8;
	t += mul16((u16)(x>>16), (u16)(y>>16))<<8;
	if(sign) t = -t;
#ifdef USE_WATCHDOG
    // Service watchdog
    WDTCTL = WDTPW + WDTIS__512K + WDTSSEL__ACLK + WDTCNTCL;
#endif
	return t;
}

s32 square(s32 x) {
	return mulfix(x, x);
}

/* use initial estimate of y=1/2th and y'=y*(3-x*y*y)/2 with iterations */
s32 irt(s32 x) {
	if(x == 0) return -1;
	s8 shft = 0;
	u8 i;
	s32 a = x;//initial estimate
	u32 t;
	while(a > 0) {
		a <<= 1;
		shft++;
	}
	t = (u32)a;
	t >>= 8;
	if(shft & 1 == 1) t >>= 1;
	shft = ((shft - 8) >> 1);
	if(shft >= 0) t <<= shft; else t >>= -shft;
	a = (s32)t;
	for(i = 0;i < 32;i++) {
        a = mulfix(a, (AS_824(3) - mulfix(x, square(a))) >> 1);
    }
	return a;
}

s32 inv(s32 x) {
	if(x == 0) return -1;
	x = irt(x);
	return square(x);
}

s32 sqrt(s32 x) {
	if(x == 0) return 0;
	return mulfix(x, irt(x));
}

s32 bend(s32 x) {		/* x/(1+sqrt(1+x*x)) */
	return mulfix(x, inv(ONE+sqrt(ONE+square(x))));
}

s32 atanh(s32 x, s8 i2) {
	s32 acc = x;
	s32 mul = x;
	x = square(x);
	x = i2 < 0 ? -x : x;
	u8 i;
	for(i = 3;i < 64;i+=2) {
			mul = mulfix(mul, x);//overflow?
            acc += mulfix(mul, inv(AS_824(i)));
        }
	return acc;
}

s32 log(s32 x) { //base e
	if(x == 0) return -1;
	x = irt(x);//make between 0 and 1 for this code now
	return -atanh(mulfix((x-ONE), inv(x+ONE)), 1) << 2;
}

s32 atan(s32 x) {
	return atanh(bend(x), -1) << 1;
}

s32 rel(s32 x) {
	return sqrt(ONE-square(x));
}

const u8 named_calc[][2] = { 	"SQ", "IR", "IV", "RT",
								"RL", "BD", "LG", "AT" };

const s32 pre_scale[] = { 		ONE / 100, ONE, ONE, ONE,
								ONE / 100, ONE, ONE, ONE / 100};

const s32 scale[] = { 			ONE, ONE, ONE, ONE / 10,
								ONE, ONE, INV_LOG_E100, FOUR_INV_PI };

u8 fn_calc = 6;
s32 in_calc = 50;
s16 out_calc = 0;

void calc_slide() {
	s32 out = AS_824(in_calc);
	s16 tst;
	out = mulfix(out, pre_scale[fn_calc]);//suitable range
	switch(fn_calc) {
	case 0: out = square(out); break;
	case 1: out = irt(out); break;
	case 2: out = inv(out); break;
	case 3: out = sqrt(out); break;
	case 4: out = rel(out); break;
	case 5: out = bend(out); break;
	case 6: out = log(out); break;
	case 7: out = atan(out); break;
	default: break;
	}
	out = mulfix(out, scale[fn_calc]);// 0 to 1
	out = mulfix(out, AS_824(100));
	out >>= 8;
	out = mulfix(out, AS_824(100));
	tst = ((s16)out);
	out >>= 16;
	if(tst < 0) out++;//round
	out_calc = out;
}

void mx_slide()
{
    clear_display_all();
    display_slide(0);//fill in
    // Loop values until all are set or user breaks set
    while (1)
    {
        // Idle timeout: exit
        if (sys.flag.idle_timeout)
        {
            break;
        }

        // Button STAR (short): exit
        if (button.flag.star)
        {
            break;
        }

        set_value(&in_calc, 2, 0, 1, 100, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE +
                          SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0,
                          display_value);
        calc_slide();
        //and the result
       	display_chars(LCD_SEG_L1_3_0, int_to_array(out_calc, 4, 0), SEG_ON);
    }

    // Clear button flags
    button.all_flags = 0;
}

void sx_slide()
{
    fn_calc = (++fn_calc)&7;//fixed
    display_slide(0);
}

void display_slide(u8 update)
{
	display_chars(LCD_SEG_L2_3_2, (u8 *)named_calc[fn_calc], SEG_ON);
	display_chars(LCD_SEG_L2_1_0, int_to_array(in_calc, 2, 0), SEG_ON);
}
