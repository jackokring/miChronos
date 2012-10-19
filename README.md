miChronos
=========
Edited source of the eZ430-Chronos development kit. Some changes for smaller space, and a calculation slide rule application. Designed with the 16KB limit of CCS in mind. Things to note:
It is impossible to remove the drivers library, as this contains 4 symbols to use the radio (appears so).
It is impossible to lose the float support, as the function update_pressure_table remains linked (appears so).
With this in mind the calculation became floating point.

Slide Rule
----------
So the latest is to have a 4 digit in float based slide calc. This gives better inverse conversion for say antilogs.
The slide rule is placed just after the date on the bottom line. Pressing DOWN selects the function. Pressing and holding # selects the entry mode. Using UP and DOWN (HOLD for fast) set the input. Press # to calculate. Press STAR to EXIT.
Important points are the atan function is 9999 (full scale) at 45 degrees. The bend function is not scaled as it's use needs THE result, and not an abstract angle ratio. The functions are scaled for maximum possible resolution as appropriate. Calculation of inverse functions is somewhat involved repeated use and estimation.

Bytes
-----
The bytes left in version 2 is 3733. The intent is to make some custom software in these bytes. There are still some further size savings possible, but they would increase power consuption in standby time display, due to an extra function call overhead. As time display is the main use a watch is put, this is somewhat important. Reclaiming some byte space in the setting routines, is however useful, even though this takes a fraction more power, as the setting modes are infrequently used, even though utility is perhaps the focus of this project. Everyone sleeps.
