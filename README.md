miChronos
=========

Edited source of the eZ430-Chronos development kit. Some changes for smaller space, and a calculation slide rule application. Designed with the 16KB limit of CCS in mind. Things to note:

It is impossible to remove the drivers library, as this contains 4 symbols to use the radio (appears so).
It is impossible to lose the float support, as the function update_pressure_table remains linked (appears so).

With this in mind the calculation tool although fixed point may be ripe for float. But maybe you don't need altimeters.
