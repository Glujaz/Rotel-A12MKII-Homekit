                  
 
<h1 align="center" style="font-weight: bold;">Rotel-A12MKII-Homekit 📻</h1>

<p align="center">
<a href="#tech">Technologies</a>
<a href="#started">Getting Started</a>

 
</p>


<p align="center">This project is to add the Rotel A12MKII Amplifier to HomeKit using an ESP32 and Homespan over RS232.
Works also for Rotel A14, A14MKII, and A12.</p>


 
<h2 id="layout">🎨 Layout</h2>

<p align="center">

<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Homescreen.PNG?raw=true" alt="Home App Main Page showing the Amp and the Amp Settings accessories" width="400px">
<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Input%20Selection.PNG?raw=true" alt="Input Selection" width="400px">
<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Input%20Settings.PNG?raw=true" alt="Input Selection settings" width="400px">
<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Settings%20all.PNG?raw=true" alt="Additional control accessories" width="400px">
<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Settings%20top.PNG?raw=true" alt="Control accessory with top controls" width="400px">
<img src="https://github.com/Glujaz/Rotel-A12MKII-Homekit/blob/main/Pictures/Settings%20bottom.PNG?raw=true" alt="Control accessory with bottom controls" width="400px">
</p>
 
<h2 id="technologies">💻 Technologies</h2>

It is based on the Homespan library only to make as simple as possible
You will also require an ESP32
 
<h2 id="started">🚀 Getting started</h2>

Download the 4 files located inside the Rotel-Homespan folder and open it inside the Arduino IDE.

Connect the ESP32 to you computer and load it in !

There are 2 optional variables in the code at the top.
- The first is used to determine how often the ESP32 is asking the current state of the amp. Default is 5 minutes as for each actions, the amp is already sending this information
- the second information is to disable the second accessory used for the additional controls of the amp (volume, speakers, etc...)
 
<h3>Prerequisites</h3>

- An [ESP32](https://www.amazon.fr/AZDelivery-NodeMCU-développement-dénergie-successeur/dp/B074RGW2VQ/ref=sr_1_5?__mk_fr_FR=ÅMÅŽÕÑ&crid=24QGNDT517DD0&dib=eyJ2IjoiMSJ9.uHqGnIpXI9uhMmv-IBGAlCEYXHMRMss5w9EtYaSS5P9_rm2ZJSxka8iXhmOG1wf8K-E_MwtgndcVFEDwakiOUpXDkqKOkGC56pynpIWUPAKjtR0noSonpAm5ZvvoqgO1qjisP4bVsbs1UkhF7aCvAy1BMfdffhanRyN2lso3Aeo6_0X_z38002Cu006NbUR4KmJTIQ3wO4tlH7CMRssLn5VEQP_j4sI_SgAh_g9vvBiD7P3eA_3XqR_u3oVbsUPehn_NlP1nKDM5mj0o0QT7aIVwmd4yNGcG8ztncgIbM6Y.ObBM9Yf9RsFkemHEYO50y__9-vg8o78aw-bY-OfS9BY&dib_tag=se&keywords=esp32&qid=1717357011&sprefix=esp32%2Caps%2C76&sr=8-5&th=1) is of course required. You can get one on amazon for less then 20€.

- Follow the instructions install the Homespan library on the Arduino IDE (if you are new to ESP32, the instructions include already everything you need)

- It requires to connect a [MAX3232](https://www.amazon.fr/DollaTek-MAX3232-Serial-Convertisseur-Connecteur/dp/B07DK3874B/ref=sr_1_9?crid=3IVH5H135RCEW&dib=eyJ2IjoiMSJ9.57fLPOGn2pbRDH7sWS9ENUZ2HKE7L1RohiWnwUmc9ufUvNeSxtR0JH_xHxbwmFkGBf4-8GoR3KSEJKlSjMpI4918OJPP-_Ue3tyEeFwdnNN5VMmtAnEevGN43WltNkJt5PnOqcRsrwFMOQ-nKSxYvZZqF9TiFOH3Z3wDcxwEPis4oD8PBkH_rryc1ndhGOfO8z6PsSQg9X6vjcFYbHFprlyH2fkkfpfit7Tn2FPl7X52bhH0-U0YHAzVm1E8I8NqDs165w55bYN7XN7fzWdgv5Z-mm_BM0zig0teIgFEreM._gvNVW_dW758rw49l1p8CZHllvrH9v_lLgF1oLHVMac&dib_tag=se&keywords=max3232&qid=1710891151&sprefix=%2Caps%2C84&sr=8-9) to pins used for TTL2 (typically 16 & 17 for RX & TX respectively), and use a crossed RS232 cable to connect to the amp.
 
<h3>Starting</h3>

Once the ESP32 is booted, follow the instructions to add a new Homespan device to HomeKit.
Two Accessories will show up in your Home app under the TV section. The first one is the Rotel Amplifier, the second one will be a supplemental accessory with multiple switches allowing you to control other elements via HomeKit and it's automations (which speaker is turned on, volume, etc...)
 
<h2 id="contribute">📫 Contribute</h2>

This is probably my first and biggest code in C++. It is very ugly, so if you have other propositions, feel free to contribute !
 
<h3>Documentations that might help</h3>

- 📄[Homespan introduction Manual](https://github.com/HomeSpan/HomeSpan/blob/master/docs/GettingStarted.md)

- 📄[Rotel connectivity Documentation](https://www.rotel.com/sites/default/files/product/rs232/A12-A12MKII-A14-A14MKII%20Protocol.pdf)
