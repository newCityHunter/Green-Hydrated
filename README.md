# Green-Hydrated
The Auto Watering System for Orchids garden
## Introduction
This is a Real Time Embedded System powered by Arduino that can help you to watering your garden automatically.
### Version 1.0.0
The system will auto watering twice a day as long as you wanted.
For me, the times are 07:00:00 && 19:00:00 and last 15 mins each time.
#### Components:
- Arduino Nano V3.
- 9V 1A Power Adapter AC 100-220V to DC 5.5*2.1mm.
- RTC DS3231 (realtime clock module).
- Relay module 5V.
- Normally closed solenoid valve 24V.
- 24V 1A Power Adapter AC 100-220V to DC 5.5*2.1mm.
- Misting Nozzle tees.
#### Little attention - For my clumsiness on this version:
- if your RTC is set date time already, you need to comment the line 21 "setThisDate();" of a_autoWatering.ino file before upload the code to arduino.
- If your RTC not set time or need to reset the local time, you need to upload all source to your hardware (inlcuding the line 21 of a_autowatering.ino file). And then comment line 21 and re upload all source one more time.
