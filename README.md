# Using the PIC Watchdog timer as a timer tick

The watchdog timer (WDT) can be used as a timer tick.

During normal operation, a WDT time-out
generates a device RESET. If the device is in SLEEP
mode, a WDT wake-up causes the device to wake-up
and continue with normal operation.

