miChronos
=========
Edited source of the eZ430-Chronos development kit. Some changes for smaller space and less power, and a calculation slide rule application. Designed with the 16KB limit of the free CCS from Texas Instruments in mind. Things to note:
  * It is impossible to remove the drivers library, as this contains 4 symbols to use the radio (appears so).
  * It is impossible to lose the float support, as the function update-pressure-table remains linked (appears so).

Day of Week
-----------
(v3) This simply displays the day of the week and day number in month where the date is in the default source. The calculation is accurate and will not fail in 400 years time, when your antique watch is a family hierloom. This is a bit tougne in cheek, but the millenium bug is past history. I built in this feature as I find it more useful to know the day of the week than the month I'm on. The day names are shown as the first three letters of the english day, but due to the limited display (power efficient though), do not always display well. The actual display font is part of the library, and it can't be changed in the limited edition of CCS.

Slide Rule
----------
(v3) So the latest is to have a 4 digit slide rule calculation aid. This gives better inverse conversion for say antilogs.
The slide rule is placed just after the date on the bottom line. Pressing DOWN selects the function. Pressing #HOLD selects the entry mode. Using UP and DOWN (HOLD for fast) set the input. Press # to calculate. Press STAR to EXIT. The bend function is not scaled as it's use needs the actual result, and not an abstract angle ratio. The other functions are scaled for maximum possible resolution as appropriate. Calculation of inverse functions is somewhat involved repeated use and estimation. The functions are listed below, and should be with knowledge enough to go a long way in maths. The understanding of why this function set was provided is in itself a long lesson in maths.
  * LOGS - logarithm of x scaled
  * ATAN - arc tangent of x scaled such that 45 degrees is 10000
  * AREA - x to the power of 2 scaled for two decimal places input or left hand decimals
  * OVRT - 1 over the square root of x scaled for digits precision
  * OVER - 1 over x scaled for digits precision
  * ROOT - square root of x scaled for digits precision
  * CIRC - square root of 1 minus x squared
  * HALF - x over 1 plus square root of 1 plus x squared (atan half angle formula)

Temperature and Altitude
------------------------
(v3) Pressing the UP button will switch from imperial to metric units. This does not alter the settings internal to the watch, and a different choice for temperature and altitude is possible. This allows then 12H or 24H format with any units. The changing of the time format will change all units to the opposite of those set. This then would need a few extra button pushes to restore your favourite units.

Stopwatch Reminder
------------------
(v3) If the alarm is set to ON, then every five minutes the stopwatch will trigger the alarm. If the alarm is off, this will not happen. This allows an egg timer flexibility for the smallest code size. A more featured countdown timer will not be provided.

Utility Menu
------------
(v3) The bottom line now has less items. The ACC/SYNC/RFBSL functions have not disappeared. Go to the battery function, and press #HOLD. Each time the function in this menu slot will change. A little added bonus is the DOWN button on the battery display generates a random 4 digit number based on time and battery voltage with a little number feedback. It's not a perfect generator, but it is random as it uses environment sampling.

Bytes
-----
The bytes left in version 3 is 3821. The intent is to make some custom software in these bytes. There are still some further size savings possible, but they would increase power consumption in standby time display, due to an extra function call overhead. As time display is the main use a watch is put, this is somewhat important. Reclaiming some byte space in the setting routines, is however useful, even though this takes a fraction more power, as the setting modes are infrequently used, even though utility is perhaps the focus of this project. Everyone sleeps. I now have to think of some brilliant modes for later versions.

Energy
------
An attempt has been made to make the software as practically efficient as possible. The msp430 processor has a good power to work ratio, and so most optimisation has been where both size and power are both improved. Exceptions to this were based around the limit of floating point maths being compiled in, providing both add, subtract, multiply and by extension divide by constant. As integer division was provided, it was decided that all multiplication should be done in floats, and all division potentially translated to inverted floats multiplied, or converted to integer division. This leads to smaller code size, which is ironic on a chip with hardware integer multiplier. Not much can be done with the library code, but I suggest that the source implies a 30% shrinkage could be made with heavy trimming using the full edition of CCS.

(Untested)
----------
The word untested in brackets occurs in some commits. This implies the source has not been compiled or tested, and so any binary directory, has all the .o files from the last tested commit. If you can operate the linker manually, then you should be able to build any RF frequency version of the latest tested build.
