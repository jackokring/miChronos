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
// Temperature measurement functions.
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "display.h"
#include "vti_as.h"

// logic
#include "acceleration.h"
#include "simpliciti.h"
#include "user.h"

// *************************************************************************************************
// Global Variable section
struct accel sAccel;

// *************************************************************************************************
// Extern section

// Global flag for proper acceleration sensor operation
extern u8 as_ok;

// *************************************************************************************************
// @fn          reset_acceleration
// @brief       Reset acceleration variables.
// @param       none
// @return      none
// *************************************************************************************************
void reset_acceleration(void)
{
    // Start with Y-axis display
    sAccel.view_style = DISPLAY_ACCEL_Y;

    // Clear timeout counter
    sAccel.timeout = 0;

    // Default mode is off
    sAccel.mode = ACCEL_MODE_OFF;
}

// *************************************************************************************************
// @fn          is_acceleration_measurement
// @brief       Returns 1 if acceleration is currently measured.
// @param       none
// @return      u8              1 = acceleration measurement ongoing
// *************************************************************************************************
u8 is_acceleration_measurement(void)
{
    return ((sAccel.mode == ACCEL_MODE_ON) && (sAccel.timeout > 0));
}

// *************************************************************************************************
// @fn          do_acceleration_measurement
// @brief       Get sensor data and store in sAccel struct
// @param       none
// @return      none
// *************************************************************************************************
void do_acceleration_measurement(void)
{
    // Get data from sensor
    as_get_data(sAccel.xyz);

    // Set display update flag
    display.flag.update_acceleration = 1;
}
