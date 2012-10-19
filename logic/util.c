// (C) Jacko utility menu LINE2
// *************************************************************************************************
//
// *************************************************************************************************
// Include section

// system
#include "project.h"

// logic
#include "menu.h"
#include "util.h"
#include "user.h"

#include "rfbsl.h"
#include "rfsimpliciti.h"
#include "battery.h"
#include "clock.h"
#include "slide.h"

// *************************************************************************************************
// Prototypes section
void mx_util();
void sx_util();

//main stuff
u8 fn_util = 0;
u16 pin_gen = 0;

void pin_generate()
{
	pin_gen += (u16)(log((float)(sBatt.voltage ^ (sTime.seconds << 9))) * 155337.0F);
    while (!sys.flag.idle_timeout)

    {
       	display_chars(LCD_SEG_L1_3_0, int_to_array(pin_gen, 4, 0), SEG_ON);
	idle_loop();
    }

    // Clear button flags
    button.all_flags = 0;
}

void (*(const util_mxfn[]))() = { pin_generate, sx_rf, sx_sync, sx_rfbsl };

void mx_util()
{
	util_mxfn[fn_util]();
}

void sx_util()
{
    	fn_calc = (++fn_calc)&3;//fixed
    	display_util(0);
}

void (*(const util_dispfn[]))() = { display_battery_V, display_rf, display_syn, display_rfbsl };

void display_util(u8 update)
{
	util_dispfn[fn_util]();
}

void (*(const util_upfn[]))() = { update_battery_voltage, update_time, update_time, update_time };

void update_util()
{
	util_upfn[fn_util]();
}
