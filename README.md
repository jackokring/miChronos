miChronos
=========
Edited source of the eZ430-Chronos development kit. Some changes for smaller space, and a calculation slide rule application. Designed with the 16KB limit of CCS in mind. Things to note:
It is impossible to remove the drivers library, as this contains 4 symbols to use the radio (appears so).
It is impossible to lose the float support, as the function update_pressure_table remains linked (appears so).
With this in mind the calculation became floating point.

Slide Rule
----------
(v2) So the latest is to have a 4 digit in float based slide calc. This gives better inverse conversion for say antilogs.
The slide rule is placed just after the date on the bottom line. Pressing DOWN selects the function. Pressing and holding # selects the entry mode. Using UP and DOWN (HOLD for fast) set the input. Press # to calculate. Press STAR to EXIT.
Important points are the atan function is 9999 (full scale) at 45 degrees. The bend function is not scaled as it's use needs THE result, and not an abstract angle ratio. The functions are scaled for maximum possible resolution as appropriate. Calculation of inverse functions is somewhat involved repeated use and estimation.

Temperature and Altitude
------------------------
(v3) Pressing the UP button will switch from imperial to metric units. This does not alter the settings internal to the watch, and a different choice for temperature and altitude is possible. This allows then 12H or 24H format with any units. The changing of the time format will change all units to the opposite of those set. This then would need a few extra button pushes to restore your favourite units.

Stopwatch Reminder
------------------
(v3) If the alarm is set to ON, then every five minutes the stopwatch will trigger the alarm. If the alarm is off, this will not happen. This allows an egg timer flexibility for the smallest code size. A more featured countdown timer will not be provided.

Utility Menu
------------
(v3) The bottom line now has less items. The ACC/SYNC/RFBSL functions have not disappeared. Go to the battery function, and press #HOLD. Each time the function in this menu slot will change. A little added bonus is the DOWN button on the battery display generates a random 4 digit number. This number generator is the suggested location for custom application entry.

Bytes
-----
The bytes left in version 2 is 3733. The intent is to make some custom software in these bytes. There are still some further size savings possible, but they would increase power consuption in standby time display, due to an extra function call overhead. As time display is the main use a watch is put, this is somewhat important. Reclaiming some byte space in the setting routines, is however useful, even though this takes a fraction more power, as the setting modes are infrequently used, even though utility is perhaps the focus of this project. Everyone sleeps.

(Untested)
----------
The word untested in brackets occurs in some commits. This implies the source has not been compiled or tested, and so any binary directory, has all the .o files from the last tested commit. If you can operate the linker manually, then you should be able to build any RF frequency version of the latest tested build.
