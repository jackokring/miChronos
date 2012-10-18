miChronos
=========
Edited source of the eZ430-Chronos development kit. Some changes for smaller space, and a calculation slide rule application. Designed with the 16KB limit of CCS in mind. Things to note:
It is impossible to remove the drivers library, as this contains 4 symbols to use the radio (appears so).
It is impossible to lose the float support, as the function update_pressure_table remains linked (appears so).
With this in mind the calculation tool although fixed point may be ripe for float. But maybe you don't need altimeters.

Slide Rule
----------
So the latest is to have a 4 digit in float based slide calc. This gives better inverse conversion for say antilogs.
The slide rule is placed just after the date on the bottom line. Pressing DOWN selects the function. Pressing and holding # selects the entry mode. Using UP and DOWN (HOLD for fast) set the input. Press # to calculate. Press * to EXIT.
