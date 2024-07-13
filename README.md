## BLE MIDI Wrench for ESP32-S3-USB-OTG

This was written quickly to allow passing through BLE MIDI to Windows 11 based DAWs over USB. I just happened to have an ESP32-S3-USB-OTG on hand.

This should pass through all basic midi functionality with the exception of system exclusive (sysex) messages.

The BLE MIDI Wrench currently appears as a "device" on both the USB side and the BLE side, serving my use case of allowing my ipad to be used as a controller for software and hardware synths connected to a Windows 11 PC. I've tested basic single channel midi and MPE in this scenario.
