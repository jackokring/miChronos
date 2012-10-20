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

//a four digit random number generator on the sx function of the battery
void pin_generate()
{
	pin_gen += (u16)(log((float)(sBatt.voltage ^ (sTime.seconds << 9))) * 155337.0F);
	fn_util = 4;
}

void restore_util() {
	fn_util = 0;
	display_battery(DISPLAY_LINE_UPDATE_FULL);
}

void (*(const util_sxfn[]))() = { pin_generate, sx_rf, sx_sync, sx_rfbsl, restore_util };

void sx_util()
{
	util_sxfn[fn_util]();
}

//well hidden
void mx_util()
{
    	fn_util = (++fn_util)&3;//fixed
    	display_util(0);
}

void display_pin(u8 update) {
	display_battery(DISPLAY_LINE_CLEAR);
	display_chars(LCD_SEG_L2_3_0, int_to_array(pin_gen, 4, 0), SEG_ON);
}

void (*(const util_dispfn[]))(u8 update) = { display_battery_V, display_rf, display_syn, display_rfbsl, display_pin };

void display_util(u8 update)
{
	util_dispfn[fn_util]();
}

void (*(const util_upfn[]))() = { update_battery_voltage, update_time, update_time, update_time, update_date };

void update_util()
{
	util_upfn[fn_util]();
}
