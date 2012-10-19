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

void mx_util()
{
	switch(fn_util) {
	case 0: pin_generate(); break;
	case 1: sx_rf(); break;
	case 2: sx_sync(); break;
	case 3: sx_rfbsl(); break;
	}
}

void pin_generate()
{
	pin_gen = (u16)(log((float)(sBatt.voltage ^ sTime.seconds)) * 155337.0F);
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

       	display_chars(LCD_SEG_L1_3_0, int_to_array(pin_gen, 4, 0), SEG_ON);
    }

    // Clear button flags
    button.all_flags = 0;
}

void sx_util()
{
    	fn_calc = (++fn_calc)&3;//fixed
    	display_util(0);
}

void display_util(u8 update)
{
	switch(fn_util) {
	case 0: display_battery_V(); break;
	case 1: display_rf(); break;
	case 2: display_sync(); break;
	case 3: display_rfbsl(); break;
	}
}

void update_util()
{
	if(fn_util == 0) {
		update_battery_voltage();
		return;
	}
	update_time();
}
