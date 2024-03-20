# Rotel-A12MKII-Homekit
Adding Rotel A12MKII Amplifier to HomeKit using an ESP32 and Homespan
Works also for Rotel A14, A14MKII, and A12.


This code uses the [Homespan library](https://github.com/HomeSpan/HomeSpan). Install Homepsan according to [their manual](https://github.com/HomeSpan/HomeSpan/blob/master/docs/GettingStarted.md).

Download the [ino file](https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Rotel_Homespan.ino) in this repository, and apply it to the ESP32.

Requires to connect a [MAX3232](https://www.amazon.fr/DollaTek-MAX3232-Serial-Convertisseur-Connecteur/dp/B07DK3874B/ref=sr_1_9?crid=3IVH5H135RCEW&dib=eyJ2IjoiMSJ9.57fLPOGn2pbRDH7sWS9ENUZ2HKE7L1RohiWnwUmc9ufUvNeSxtR0JH_xHxbwmFkGBf4-8GoR3KSEJKlSjMpI4918OJPP-_Ue3tyEeFwdnNN5VMmtAnEevGN43WltNkJt5PnOqcRsrwFMOQ-nKSxYvZZqF9TiFOH3Z3wDcxwEPis4oD8PBkH_rryc1ndhGOfO8z6PsSQg9X6vjcFYbHFprlyH2fkkfpfit7Tn2FPl7X52bhH0-U0YHAzVm1E8I8NqDs165w55bYN7XN7fzWdgv5Z-mm_BM0zig0teIgFEreM._gvNVW_dW758rw49l1p8CZHllvrH9v_lLgF1oLHVMac&dib_tag=se&keywords=max3232&qid=1710891151&sprefix=%2Caps%2C84&sr=8-9) to pins used for TTL2 (typically 16 & 17 or RX & TX respectively), and use a crossed RS232 cable to connect to the amp.


The code makes the ESP32 able to send commands, and also ask the status of the amp like power and input source. IT's not great right now, still learning. I need to find a way to extract elements in the reply that the amplifier sends
