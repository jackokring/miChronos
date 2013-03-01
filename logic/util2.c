// (C) Jacko utility menu LINE2
// *************************************************************************************************
//
// *************************************************************************************************
// Include section

// system
#include "project.h"

// logic
#include "menu.h"
#include "util2.h"
#include "clock.h"
#include "rfbsl.h"
#include "rfsimpliciti.h"
#include "battery.h"
#include "slide.h"
#include "display.h"

// *************************************************************************************************
// Prototypes section
void mx_util2();
void sx_util2();

//main stuff
u8 fn_util2 = 0;
u16 pin_gen2 = 0;
float pin_temp2;

//a four digit random number generator on the sx function of the battery
void pin_generate()
{
	pin_temp2 = irt((float)(((sBatt.voltage + pin_gen2) & 63) ^ sTime.second)) * 655377.0F;
	pin_gen2 += *((u16 *)&pin_temp2);
	fn_util2 = 4;
}

void restore_util2() {
	fn_util2 = 0;
	display_battery_V(DISPLAY_LINE_UPDATE_FULL);
}

void (* const util_sxfn2[])() = { pin_generate, sx_rf, sx_sync, sx_rfbsl, restore_util };

void sx_util2()
{
	util_sxfn2[fn_util2]();
}

//well hidden
void mx_util2()
{
	display_util2(DISPLAY_LINE_CLEAR);
    fn_util2 = (++fn_util2)&3;//fixed
    display_util2(DISPLAY_LINE_UPDATE_FULL);
}

void display_pin2(u8 update) {
	display_battery_V(DISPLAY_LINE_CLEAR);
	display_chars(LCD_SEG_L2_3_0, int_to_array(pin_gen, 4, 0), SEG_ON);
}

void (* const util_dispfn2[])(u8 update) = { display_battery_V, display_rf, display_sync, display_rfbsl, display_pin2 };

void display_util2(u8 update)
{
	util_dispfn[fn_util2](update);
}

u8 (* const util_upfn[])() = { update_battery_voltage, update_date, update_date, update_date, update_date };

u8 update_util2()
{
	return util_upfn2[fn_util2]();
}
