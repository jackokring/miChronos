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
#include "clock.h"
#include "rfbsl.h"
#include "rfsimpliciti.h"
#include "battery.h"
#include "slide.h"
#include "display.h"

// *************************************************************************************************
// Prototypes section
void mx_util();
void sx_util();

//main stuff
u8 fn_util = 0;
u16 pin_gen = 0;
float pin_temp;

//a four digit random number generator on the sx function of the battery
void pin_generate()
{
	pin_temp = irt((float)(((sBatt.voltage + pin_gen) & 63) ^ sTime.second)) * 655377.0F;
	pin_gen += *((u16 *)&pin_temp);
	fn_util = 4;
}

void restore_util() {
	fn_util = 0;
	display_battery_V(DISPLAY_LINE_UPDATE_FULL);
}

void (* const util_sxfn[])() = { pin_generate, sx_rf, sx_sync, sx_rfbsl, restore_util };

void sx_util()
{
	util_sxfn[fn_util]();
}

//well hidden
void mx_util()
{
	display_util(DISPLAY_LINE_CLEAR);
    fn_util = (++fn_util)&3;//fixed
    display_util(DISPLAY_LINE_UPDATE_FULL);
}

void display_pin(u8 update) {
	display_battery_V(DISPLAY_LINE_CLEAR);
	display_chars(LCD_SEG_L2_3_0, int_to_array(pin_gen, 4, 0), SEG_ON);
}

void (* const util_dispfn[])(u8 update) = { display_battery_V, display_rf, display_sync, display_rfbsl, display_pin };

void display_util(u8 update)
{
	util_dispfn[fn_util](update);
}

u8 (* const util_upfn[])() = { update_battery_voltage, update_time, update_time, update_time, update_date };

u8 update_util()
{
	return util_upfn[fn_util]();
}
