// (C)2012, 2013 Jacko edited to turn into a slide rule LINE2
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

float square(float x) {
	return x * x;
}

/* use initial estimate and y'=y*(3-x*y*y)/2 with iterations */
float irt(float x) {
    	// Watchdog triggers after 16 seconds when not cleared
	// So place here just in case any code uses intense calculaton.
#ifdef USE_WATCHDOG
    	WDTCTL = WDTPW + WDTIS__512K + WDTSSEL__ACLK;
#else
    	WDTCTL = WDTPW + WDTHOLD;
#endif
	u32 i;
        float x2;
        const float threehalfs = 1.5F;
	x2 = x * 0.5F;
        i  = * ( long * ) &x;                       // evil floating point bit level hacking
        i  = 0x5f3759df - ( i >> 1 );
        x  = * ( float * ) &i;
	for(i = 0; i < 4; i++)
        	x  *= ( threehalfs - ( x2 * square(x) ) );   //iteration
        return x;
}

float inv(float x) {
	x = irt(x);
	return square(x);
}

float sqrt(float x) {
	return x * irt(x);
}

float half(float x, float sgn) {		/* x/(1+sqrt(1+x*x)) */
	return x * inv(1.0F + sqrt(1.0F + sgn * square(x) ));
}

float halfa(float x) {
	return half(x, 1.0F);
}

//OSAF FN (flags and function produced)
//0000
//0001 expm1
//0010
//0011 expm1(ix)
//0100
//0101 sinh
//0110
//0111 sin
//1000
//1001 qfn
//1010
//1011 
//1100 log with right input transform (is atanh)
//1101
//1110 atan
//1111

float eq(float x, s8 over, s8 sq, s8 alt, s8 fact) { //base e exponential and Q+
	float acc = 0;
	float lacc;
	float mul = x;
	float harm = 1;
	u16 start = 1;
	if(sq != 0) x = square(x);
	x = (alt != 0 ? -x : x);
	do {
		lacc = acc;
		acc += mul * (over == 0 ? 1.0F : harm);
		start += sq + 1;
		harm = inv((float)start);
		mul *= x * (fact == 0 ? 1.0F : harm * (sq == 0 ? 1.0F : inv(start - 1)));
        } while(lacc != acc && start < 200);//term limit
	return acc;
}

float log(float x) { //base e
	x = irt(irt(irt(x)));//symetry and double triple roots
	return -eq((x-1.0F) * inv(x+1.0F), 1, 1, 0, 0) * 16.0F;
}

float atan(float x) {
	return eq(halfa(halfa(x)), 1, 1, 1, 0) * 4.0F;
}

float circ(float x) {
	return sqrt(1.0F - square(x));
}

float exp(float x) {
	return eq(x, 0, 0, 0, 1) + 1.0F;
}

float qfn(float x) {
	return eq(x, 1, 0, 0, 1);
}

float invw(float x) {
	return x * exp(x);
}

float ein(float x) {
	return qfn(x) + log(x);
}

float lin(float x) {
	return ein(log(x));
}

float split_mod;

float split_num(float x) {
	s16 i = (s32)x;
	split_mod = (float)(i % 100);
	return (float)(i / 100);
}

float mul(float x) {
	return split_num(x) * split_mod;
}

float div(float x) {
	return split_num(x) * inv(split_mod);
}

float harm(float x) {
	float t = split_num(x);
	return t * split_mod * inv(t + split_mod);
}

//extra eight functions
//on root
float halfs(float x) {
	return half(x, -1.0F);
}

float halfc(float x) {
	return circ(x) * inv(x + 1);
}
//on logs
float asin(float x) {
	return 2.0F * atan(halfs(x));
}

float acos(float x) {
	return 2.0F * atan(halfc(x));
}
//on exps
float sin(float x) {
	return eq(x, 0, 1, 1, 1);
}

float cos(float x) {
	return sin(x + 1.57079632679F);
}
//on xtra
float tan(float x) {
	return sin(x) * inv(cos(x));
}

float entropy(float x) {
	return x * log(inv(x)) * 1.44269504089F;//base 2
}

//main module functions
const u8 named_calc[][4] = { 	"ROOT", "LOGS", "EXPS", "XTRA" };


const u8 named_calc2[][2] = { 	"AR", "IR", "IN", "RT", "LG", "HF", "AT", "CC",
					"EX", "CU", "ED", "EI", "LI", "TI", "DI", "HC" };

const u8 idx_scale[] = {		0, 1, 1, 2, 3, 0, 4, 0,
					5, 6, 6, 6, 7, 7, 8, 8,
					0, 0, 4, 4, 9, 9, 9, 0 };

const float pre_scale[] = { 	0.0001F, 1.0F, 1.0F, 1.0F, 0.0001F,
					9.21034037196e-4, 0.0001F, 1.0F, 1.0F, 7.85398163394e-5F };

const float scale[] = { 	10000.0F, 10000.0F, 100.0F, 1.08573620476e+3F, 12732.3954474F,
					1.0F, 1000.0F, 1.0F, 100.0F, 10000.0F };

s8 fn_calc = 0;
s8 fn_calc2 = 0;//minor fix... to v5.1
s32 in_calc = 5000;
u16 out_calc = 0;

float (* const slide_fn[])(float x) = { 	square, irt, inv, sqrt, log, halfa, atan, circ,
						exp, qfn, invw, ein, lin, mul, div, harm,
						halfs, halfc, asin, acos, sin, cos, tan, entropy };

void calc_slide() {
	float out = (float)in_calc;
	out *= pre_scale[idx_scale[fn_calc]];//suitable range
	out = slide_fn[fn_calc](out);
	out *= scale[idx_scale[fn_calc]];// 0 to 10000
	out_calc = (u16)out;
	if(out - (float)out_calc >= 0.5F) out_calc++;
	if(out_calc > 9999) out_calc = 9999;
}

void display_fn_choice() {
	fn_calc = fn_calc2 << 2;
	display_chars(LCD_SEG_L1_3_2, (u8 *)named_calc2[fn_calc], SEG_ON);
	display_chars(LCD_SEG_L1_1_0, (u8 *)named_calc2[fn_calc + 1], SEG_ON);
	display_chars(LCD_SEG_L2_3_2, (u8 *)named_calc2[fn_calc + 2], SEG_ON);
	display_chars(LCD_SEG_L2_1_0, (u8 *)named_calc2[fn_calc + 3], SEG_ON);
}

void mx_slide2()
{
	if(fn_calc == 100) return;//exit code
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

        set_value(&in_calc, 4, 0, 1, 9999, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE +
                          SETVALUE_NEXT_VALUE + SETVALUE_FAST_MODE, LCD_SEG_L2_3_0,
                          display_value);
        calc_slide();
        //and the result
       	display_chars(LCD_SEG_L1_3_0, int_to_array(out_calc, 4, 0), SEG_ON);
    }

    // Clear button flags
    button.all_flags = 0;
}

// *************************************************************************************************
// Extern section
extern void idle_loop(void);

void mx_slide()
{
    clear_display_all();
	display_fn_choice();
    // Loop values until all are set or user breaks set
    while (1)
    {
        // Idle timeout: exit
        if (sys.flag.idle_timeout)
        {	
		fn_calc = 100;//exit code
            break;
        }

        // Button STAR (short)
        if (button.flag.star)
        {
            break;
        }

        if (button.flag.num)
        {
		fn_calc += 2;
            break;
        }

        if (button.flag.up)
        {
		fn_calc += 1;
            break;
        }
	if (button.flag.down)
        {
		fn_calc += 3;
            break;
        }
	if (button.flag.star_long)
	{
		fn_calc = (fn_calc >> 1) + 16;
		break;
	}
	if (button.flag.num_long)
	{
		fn_calc = (fn_calc >> 1) + 17;
		break;
	}
	idle_loop();//idle
        
    }

    // Clear button flags
    button.all_flags = 0;
	mx_slide2();
}

void sx_slide()
{
    fn_calc2 = (++fn_calc2)&3;//fixed
    display_slide(0);
}

void display_slide(u8 update)
{
	display_chars(LCD_SEG_L2_3_0, (u8 *)named_calc[fn_calc2], SEG_ON);
}
