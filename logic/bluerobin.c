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
// BlueRobin functions.
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "display.h"
#include "radio.h"
#include "ports.h"
#include "timer.h"
#include "rf1a.h"

// logic
#include "BlueRobin_RX_API.h"
#include "bluerobin.h"
#include "rfsimpliciti.h"
#include "user.h"

// *************************************************************************************************
// Defines section

// Set to TRUE if transmitter ID should be remembered when reconnecting
// Transmitter ID can be cleared by pressing button STAR for more than 3 seconds
#define REMEMBER_TX_ID                  (FALSE)

// *************************************************************************************************
// Global Variable section
struct bluerobin sBlueRobin;

// Display values for user gender selection
//const u8 selection_User_Gender[][4] = { "MALE", "FEMA" };

// *************************************************************************************************
// Extern section

// Stop BlueRobin timer
extern void BRRX__StopTimer_v(void);

// Calibration value for FSCTRL0 register (corrects deviation of 26MHz crystal)
extern u8 rf_frequoffset;

// *************************************************************************************************
// @fn          reset_bluerobin
// @brief       Reset BlueRobin data.
// @param       none
// @return      none
// *************************************************************************************************
void reset_bluerobin(void)
{
    
}

// *************************************************************************************************
// @fn          mx_rfblue
// @brief       BlueRobin sub menu.
//                              Button STAR resets chest strap ID to 0 and searches for next chest
// strap in range.
// @param       u8 line LINE2
// @return      none
// *************************************************************************************************


// *************************************************************************************************
// @fn          sx_bluerobin
// @brief       BlueRobin direct function. Button UP connects/disconnects with sender unit.
// @param       u8 line         LINE1
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_selection_User_Gender
// @brief       Display the configuration for gender in watch
// @param       u8 segments                     LCD segments where value is displayed
//                              u32 value                       Integer value to be displayed
//                              u8 digits                       Number of digits to convert
//                              u8 blanks                       Number of leadings blanks in
// int_to_array result string
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          mx_caldist
// @brief       Calories/Distance sub menu. Mx enables setting of total calories, user sex and
// weight.
// @param       u8 line         LINE2
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          sx_caldist
// @brief       Button DOWN toggles between calories and distance display.
// @param       u8 line         LINE2
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_heartrate
// @brief       Heart rate display routine.
// @param       u8 line LINE1
//                              u8 update       DISPLAY_LINE_UPDATE_FULL,
// DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_speed_kmh
// @brief       Speed display routine. Supports kmh and mph.
// @param       u8 line LINE1
//                              u8 update       DISPLAY_LINE_UPDATE_PARTIAL,
// DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_distance
// @brief       Distance display routine. Supports km and mi.
// @param       u8 line         LINE2
//                              u8 update       DISPLAY_LINE_UPDATE_PARTIAL,
// DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_caldist
// @brief       Shared calories/distance display routine.
// @param       u8 line LINE2
//                              u8 update       DISPLAY_LINE_UPDATE_PARTIAL,
// DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          display_calories
// @brief       Calories display routine.
// @param       u8 line LINE2
//                              u8 update       DISPLAY_LINE_UPDATE_PARTIAL,
// DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************

// *************************************************************************************************
// @fn          is_bluerobin
// @brief       Returns TRUE if BlueRobin transmitter is connected.
// @param       none
// @return      u8
// *************************************************************************************************
u8 is_bluerobin(void)
{
    return (0);
}

// *************************************************************************************************
// @fn          is_bluerobin_searching
// @brief       Returns TRUE if BlueRobin is searching for a transmitter.
// @param       none
// @return      u8
// *************************************************************************************************
u8 is_bluerobin_searching(void)
{
    return (0);
}

// *************************************************************************************************
// @fn          get_bluerobin_data
// @brief       Read BlueRobin packet data from API.
// @param       none
// @return      none
// *************************************************************************************************
void get_bluerobin_data(void)
{
    
}

// *************************************************************************************************
// @fn          stop_bluerobin
// @brief       Stop communication and put peripherals in power-down mode.
// @param       none
// @return      none
// *************************************************************************************************
void stop_bluerobin(void)
{
    
}
