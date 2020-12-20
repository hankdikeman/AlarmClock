# AlarmClock

This is a project to make an intuitive and functional alarm clock using a real time clock and RGB backlit LCD screen. 

# Features:
The Alarm Clock programmed in this library monitors time and date using the highly accurate DS3231 temperature-compensated RTC with I2C breakout and the 20x4 RGB backlit LCD screen from Adafruit. The clock gives you the ability to set 2 separate alarms and choose which ones (if any) are active. When an alarm is triggered it may be shut off by button 1 or will auto shutoff after 2 minutes, following which the alarm is changed to _inactive_

# Display:
**Line 1)** Time in the format "hr:min:sec"
**Line 2)** Date in the format "DoW month-day-year"
**Line 3)** Alarm 1 in the format "hr:min ON/OFF"
**Line 4)** Alarm 2 in the format "hr:min ON/OFF"

# Button functionality:
**Button 1)** Controls which alarms are currently active (options: 1, 2, both, neither)
**Button 2)** Controls which alarm is currently being set (options: 1, 2, neither)
**Button 3)** Sets the hour of the alarm designated by **2** (options: 0-23 inclusive)
**Button 4)** Sets the minute of the alarm designated by **2** (options: 0-59 inclusive)

# Attributions: 
Credit to the programmers of Adafruit for the wonderful RTClib.h DS3231 RTC library and Arduino for the LiquidCrystal.h library, which were both used in this sketch. 
