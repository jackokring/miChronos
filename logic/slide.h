//LINE2
// *************************************************************************************************
// (C)Jacko edited to turn into a slide rule
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

#ifndef SLIDE_H_
#define SLIDE_H_

// *************************************************************************************************
// Defines section

// *************************************************************************************************
// Prototypes section
extern void sx_slide();
extern void mx_slide();
extern void display_slide(u8 update);

//fixed point calculation functions exported

//root basis functions
extern float square(float x);
extern float irt(float x);
extern float inv(float x);
extern float sqrt(float x);

//logarithm group of functions
extern float log(float x);
extern float halfa(float x);
extern float atan(float x);
extern float circ(float x);

//exponential group of functions
extern float exp(float x);//exponential function
extern float qfn(float x);//my q function
extern float invw(float x);//inverse lambert W function
extern float ein(float x);//the natural origin Ei function

//other group of functions
extern float lin(float x);//the natural origin Li function (primes less than estimate)
extern float mul(float x);//mul digit pairs
extern float div(float x);//div digit pairs
extern float harm(float x);//parallel digit pairs

//hidden group of functions
extern float halfs(float x);
extern float halfc(float x);
extern float asin(float x);
extern float acos(float x);
extern float sin(float x);
extern float cos(float x);
extern float tan(float x);
extern float entropy(float x);

#endif                          /*SLIDE_H_ */
