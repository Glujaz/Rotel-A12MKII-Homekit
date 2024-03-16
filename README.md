# Rotel-A12MKII-Homekit
Adding Rotel A12MKII Amplifier to HomeKit using an ESP32 and Homespan


This code uses the Homespan library. Install Homepsan according to their manual. Download the ino file in this repository, and apply it to the ESP32.

Requires to connect a MAX3232 to pins used for TTL2 (typically 16 & 17), and use a crossed RS232 cable to connect to the amp.

The code can only send commands to the amp. It is later expected to be able to read at least the power state, and the active input, so that it updates inside homekit when using the physical remote as well.
