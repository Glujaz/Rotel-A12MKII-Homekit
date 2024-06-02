#include "HomeSpan.h"
#include <HardwareSerial.h>
#include "DEV_RotelService.h"
#include "DEV_RotelSettings.h"


//User Settings :
const long interval = 5 * 60 * 1000;  // Time between asking for status of the amp. Default value is 5min
bool ShowSettings = true; //set Show Settings to 'false' if you don't want to see the additional settings accessory

//Homespan Variables used by code
unsigned long previousMillis = 0;
bool power = 1;  //power status
bool comPower = 0; //stores new requested power
int input = 0;  //stores active input
int comInput = 1;  //stores new requested input
bool receiving = 3; //used for the communication function
bool sending = 0; //used for the communication function
int volume = 25; //stores active volume
int comVolume = 25;  //stores new requested volume
bool speakerA = 0;
bool comSpeakerA = 1;
bool speakerB = 0;
bool comSpeakerB = 1;
int brightness = 0;
int comBrightness=1;
int balance = 45;
int comBalance = 50;
bool bypass=0;
bool comBypass=1;
int bass=0;
int comBass=1;
int treble=1;
int comTreble=0;
char formatBuffer[5];


///////////Status Commands/////////////
String statusAction="!";
String statusAsk="?";
String statusPower="power";
String statusPowerDetect="power";
String statusPowerSet="power_on";
String statusPowerUnset="power_off";
String statusPowerOnGet="on";
String statusPowerOffGet="standby";
String statusSourceDetect="source";
String statusSource="source";
String statusVolume="vol_";
String statusVolumeGet="volume";
String statusMuteSet="mute_on";
String statusMuteUnset="mute_off";
String statusSpeakerGet="speaker";
String statusSpeakerSet="speaker_";
String statusBrightnessSet="dimmer_";
String statusBrightnessGet="dimmer";
String statusBalanceSet="balance_";
String statusBalanceGet="balance";
String statusBypassSet="bypass_";
String statusBypassGet="bypass";
String statusBassSet="bass_";
String statusBassGet="bass";
String statusTrebleSet="treble_";
String statusTrebleGet="treble";


void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1);  // start Serial2 at 115200 8N1
  Serial2.print("!rs232_upate_on!");  //to make sure the amp is communicating everytime

  receiving=3;
  Serial.print("starting first status scan. Current receiving option is :");Serial.println(receiving);delay(1000);
  rs232send();
  rs232receive();


  //homeSpan.enableOTA();
  homeSpan.begin(Category::Television, "Rotel A12MKII Amplifier");
  //homeSpan.setSerialInputDisable(false);
  Span& enableAutoStartAP();


    new SpanAccessory(); 
      new Service::AccessoryInformation();
        new Characteristic::Identify(); 
        new Characteristic::ConfiguredName("Audio Amplifier");
        new Characteristic::Manufacturer("Rotel");  
        new Characteristic::Model("A12 MKII");
        new Characteristic::FirmwareRevision("1.0");
        

      new DEV_RotelService();

    new SpanAccessory(5);
        new Service::AccessoryInformation();
        new Characteristic::Identify(); 
        new Characteristic::ConfiguredName("Audio Amplifier Settings");
        new Characteristic::Name("Audio Amplifier Settings");
        new Characteristic::Manufacturer("Rotel");  
        new Characteristic::Model("A12 MKII");
        new Characteristic::FirmwareRevision("1.0");

      new DEV_RotelSettings();
      new DEV_RotelVolume();
      new DEV_RotelBrightness();
      new DEV_RotelByPass();
      new DEV_RotelBalance();
      new DEV_RotelTreble();
      new DEV_RotelBass();
      new DEV_RotelSpeakerA();
      new DEV_RotelSpeakerB();

      if (ShowSettings == false){homeSpan.deleteAccessory(5);}


}

//////////////////////////////////////


void loop() {

  homeSpan.poll();

  rs232send();
  rs232receive();

  unsigned long currentMillis = millis();  // Get the current time

  // Check if 5 minutes have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the last action time

    // Code to be executed every 5 minutes
    receiving=1;
  }




}
