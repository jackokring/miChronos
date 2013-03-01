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

#ifndef MENU_H_
#define MENU_H_

// *************************************************************************************************
// Include section

// *************************************************************************************************
// Prototypes section
u8 update_time();
u8 update_stopwatch();
u8 update_date();
u8 update_alarm();
u8 update_temperature();
u8 update_battery_voltage();

// *************************************************************************************************
// Defines section

struct menum
{
    // Pointer to direct function (start, stop etc)
    void (*sx_function)();
    // Pointer to sub menu function (change settings, reset counter etc)
    void (*mx_function)();
    // Pointer to display function
    void (*display_function)(u8 update);
    // Display update trigger
    u8 (*display_update)();
    // Pointer to next menu item
    const struct menum *next;
};

// *************************************************************************************************
// Global Variable section

// *************************************************************************************************
// Extern section

// Line1 navigation
extern const struct menum menu_L1_Time;
extern const struct menum menu_L1_Alarm;
extern const struct menum menu_L1_Altitude;
extern const struct menum menu_L1_Temperature;

// Line2 navigation
extern const struct menum menu_L2_Date;
extern const struct menum menu_L2_Slide;
extern const struct menum menu_L2_Stopwatch;
extern const struct menum menu_L2_Util;
extern const struct menum menu_L2_Util2;
//extern const struct menum menu_L2_Battery;
//extern const struct menum menu_L2_Rf;
//extern const struct menum menu_L2_Sync;
//extern const struct menum menu_L2_RFBSL;

extern u8 quick;
extern void (*fptr_lcd_function_line1m)(u8 update);
extern void (*fptr_lcd_function_line2m)(u8 update);
extern void (*fptr_lcd_function_line1)(u8 line, u8 update);
extern void (*fptr_lcd_function_line2)(u8 line, u8 update);

#endif                          /*MENU_H_ */
