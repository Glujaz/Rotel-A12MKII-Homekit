#include "HomeSpan.h"
#include <HardwareSerial.h>

bool power = 0;  //power status
bool comPower = 0; //stores new requested power
int input = 1;  //stores active input
int comInput = 1;  //stores new requested input
bool receiving = 0; //used for the communication function
bool sending = 0; //used for the communication function
int volume = 25; //stores active volume
int comVolume = 25;  //stores new requested volume

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
String statusVolumeMute="mute_on";
String statusVolumeUnmute="mute_off";


void rs232send() {

  if(sending == 1){

      //sending input request
      if (comInput == 1) {Serial2.print(statusAction+"cd"+statusAction);}
      if (comInput == 2) {Serial2.print(statusAction+"coax1"+statusAction);}
      if (comInput == 3) {Serial2.print(statusAction+"coax2"+statusAction);}
      if (comInput == 4) {Serial2.print(statusAction+"opt1"+statusAction);}
      if (comInput == 5) {Serial2.print(statusAction+"opt2"+statusAction);}
      if (comInput == 6) {Serial2.print(statusAction+"aux1"+statusAction);}
      if (comInput == 7) {Serial2.print(statusAction+"aux2"+statusAction);}
      if (comInput == 8) {Serial2.print(statusAction+"tuner"+statusAction);}
      if (comInput == 9) {Serial2.print(statusAction+"phono"+statusAction);}
      if (comInput == 10) {Serial2.print(statusAction+"usb"+statusAction);}
      if (comInput == 11) {Serial2.print(statusAction+"bluetooth"+statusAction);}
      if (comInput == 12) {Serial2.print(statusAction+"pcusb"+statusAction);}

      if (comInput == 100) {Serial2.print(statusAction+statusPowerSet+statusAction);Serial.println("sent command turning Amp On");}
      if (comInput == 101) {Serial2.print(statusAction+statusPowerUnset+statusAction);Serial.println("sent command turning Amp Off");}

      if (comInput == 150) {Serial2.print(statusAction+statusVolume+comVolume+statusAction);Serial.print("Applied volume is ");Serial.print(comVolume);Serial.println("%");}
      if (comInput == 151) {Serial2.print(statusAction+statusVolumeUnmute+statusAction);Serial.println("Unmuted Amp");}
      if (comInput == 152) {Serial2.print(statusAction+statusVolumeMute+statusAction);Serial.println("Muted Amp");}


      sending == 0;
  }
    else if (receiving == 1) {

      //asking power status
      Serial2.print(statusAction+statusPower+statusAsk);

      //asking input status
      Serial2.print(statusAction+statusSource+statusAsk);

      //asking Volume status
      Serial2.print(statusAction+statusVolumeGet+statusAsk);


      receiving = 0;
  }
}

void rs232receive(){

  String receivedType;
  String receivedData;

  while (Serial2.available()) {
    char c = Serial2.read();
    if (c == '$') { //detected end of transmission

    int separatorIndex = receivedData.indexOf('=');
    if (separatorIndex != -1) {
      receivedType = receivedData.substring(0, separatorIndex);
      receivedData = receivedData.substring(separatorIndex + 1);

      if (receivedType == statusPowerDetect) {
        LOG1("\ndetected power status\n");

        if (receivedData == statusPowerOnGet){comPower=1;}
        if (receivedData == statusPowerOffGet){comPower=0;}

      } else if (receivedType == statusSourceDetect) {
          LOG1("\ndetected input source\n");


          if(receivedData == "cd") {comInput=1;}
          if(receivedData == "coax1") {comInput=2;} 
          if(receivedData == "coax2") {comInput=3;} 
          if(receivedData == "opt1") {comInput=4;} 
          if(receivedData == "opt2") {comInput=5;} 
          if(receivedData == "aux1") {comInput=6;} 
          if(receivedData == "aux2") {comInput=7;} 
          if(receivedData == "tuner") {comInput=8;} 
          if(receivedData == "phono") {comInput=9;} 
          if(receivedData == "usb") {comInput=10;} 
          if(receivedData == "bluetooth") {comInput=11;} 
          if(receivedData == "pc_usb") {comInput=12;} 


      }
      // Clear receivedData for the next message
      LOG1("\n");
      LOG1("received full message ");
      LOG1("\n");
      LOG1(receivedType);
      LOG1(" = ");
      LOG1(receivedData);
      LOG1("\ncomInput is now :");
      LOG1(comInput);
      ;receivedData = "";
    }

    } else {
      // Append character to received data
      receivedData += c;
    }
  }

}

struct HomeSpanTV : Service::Television {

  SpanCharacteristic *active = new Characteristic::Active(0);              // TV On/Off (set to Off at start-up)
  SpanCharacteristic *activeID = new Characteristic::ActiveIdentifier(1);  // Sets HDMI 1 on start-up
  //SpanCharacteristic *remoteKey = new Characteristic::RemoteKey();                // Used to receive button presses from the Remote Control widget
  SpanCharacteristic *settingsKey = new Characteristic::PowerModeSelection();  // Adds "View TV Setting" option to Selection Screen

  HomeSpanTV(const char *name)
    : Service::Television() {
    new Characteristic::ConfiguredName(name);  // Name of TV
    Serial.printf("Configured TV: %s\n", name);
    Serial2.print("!rs232_update_on!");
    Serial.println(Serial2.readStringUntil('$'));
  }

  boolean update() override {

    if (active->updated()) {
      Serial.printf("Set TV Power to: %s\n", active->getNewVal() ? "ON" : "OFF");
      LOG1("Updating AMP Power");
      LOG1(":  Current Power=");
      LOG1(active->getVal() ? "ON" : "OFF");
      LOG1("  New Power=");
      LOG1(active->getNewVal() ? "ON" : "OFF");
      LOG1("\n");

      if (active->getNewVal()) {
        {comInput=100;sending=1;power=1;rs232send();}
      } else {
        {comInput=101;sending=1;power=0;rs232send();}
      }
    }

    if (activeID->updated()) {  //Applying input selection switch
      Serial.printf("Set Input Source to HDMI-%d\n", activeID->getNewVal());
      Serial2.print("!");  //to ensure cleaning any previous commands

      //////////////////////////////
      if (activeID->getNewVal() == 1) {comInput=1;sending=1;rs232send();}
      if (activeID->getNewVal() == 2) {comInput=2;sending=1;rs232send();}
      if (activeID->getNewVal() == 3) {comInput=3;sending=1;rs232send();}
      if (activeID->getNewVal() == 4) {comInput=4;sending=1;rs232send();}
      if (activeID->getNewVal() == 5) {comInput=5;sending=1;rs232send();}
      if (activeID->getNewVal() == 6) {comInput=6;sending=1;rs232send();}
      if (activeID->getNewVal() == 7) {comInput=7;sending=1;rs232send();}
      if (activeID->getNewVal() == 8) {comInput=8;sending=1;rs232send();}
      if (activeID->getNewVal() == 9) {comInput=9;sending=1;rs232send();}
      if (activeID->getNewVal() == 10) {comInput=10;sending=1;rs232send();}
      if (activeID->getNewVal() == 11) {comInput=11;sending=1;rs232send();}
      if (activeID->getNewVal() == 12) {comInput=12;sending=1;rs232send();}
    }
    return (true);
  }



void loop() { //for updating status

  if((comPower != power ) || (active->timeVal()>60000)){                               // check time elapsed since last update and proceed only if greater than 5 seconds
    receiving = 1;
    rs232receive();
    active->setVal(comPower); // Set power state
    LOG1("Reading and applying new power state");
    LOG1("\n");
    power = comPower;
  }
  if((comInput != input ) || (activeID->timeVal()>60000)){                               // check time elapsed since last update and proceed only if greater than 5 seconds
    receiving = 1;
    rs232receive();
    activeID->setVal(comInput); // Set power state
    LOG1("\n");
    LOG1("Reading and applying new source");
    LOG1("\n");
    input = comInput;
  }

}

};

struct Volume : Service::LightBulb {       // Volume

  //SpanCharacteristic *power;
  SpanCharacteristic *level;
  
  Volume(int pin) : Service::LightBulb(){

    //power=new Characteristic::On();     
                
    level=new Characteristic::Brightness(25);
    level->setRange(0,100,1);

    
  }

  boolean update(){                              // update() method
    if (level->updated()) {  //Applying Volume
      if (comVolume>0) {
        comInput=151;
        rs232send();
        comInput=150;
        rs232send;
      } else {
      comInput=152;
      rs232send();
      }   
    return(true);                               // return true
    } // update
  };

void loop() { //for updating status

  if((comVolume != volume ) || (level->timeVal()>60000)){                               // check time elapsed since last update and proceed only if greater than 5 seconds
    receiving = 1;
    rs232receive();
    level->setVal(comVolume); // Set power state
    LOG1("\n");
    LOG1("Reading and applying new Volume");
    LOG1("\n");
    volume = comVolume;
  }


}


};




///////////////////////////////

void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1);  // start Serial2 at 115200 8N1


  homeSpan.enableOTA();
  homeSpan.begin(Category::Television, "Rotel A12MKII Ampplifier");

  SPAN_ACCESSORY();

  // Below we define 10 different InputSource Services using different combinations
  // of Characteristics to demonstrate how they interact and appear to the user in the Home App

  SpanService *hdmi1 = new Service::InputSource();
  new Characteristic::ConfiguredName("CD");
  new Characteristic::Identifier(1);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi2 = new Service::InputSource();
  new Characteristic::ConfiguredName("Coaxial 1");
  new Characteristic::Identifier(2);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi3 = new Service::InputSource();
  new Characteristic::ConfiguredName("Coaxial 2");
  new Characteristic::Identifier(3);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi4 = new Service::InputSource();
  new Characteristic::ConfiguredName("Optical 1");
  new Characteristic::Identifier(4);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi5 = new Service::InputSource();
  new Characteristic::ConfiguredName("Optical 2");
  new Characteristic::Identifier(5);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi6 = new Service::InputSource();
  new Characteristic::ConfiguredName("Auxiliary 1");
  new Characteristic::Identifier(6);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi7 = new Service::InputSource();
  new Characteristic::ConfiguredName("Auxiliary 2");
  new Characteristic::Identifier(7);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi8 = new Service::InputSource();
  new Characteristic::ConfiguredName("Tuner");
  new Characteristic::Identifier(8);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi9 = new Service::InputSource();
  new Characteristic::ConfiguredName("Phonograph");
  new Characteristic::Identifier(9);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi10 = new Service::InputSource();
  new Characteristic::ConfiguredName("USB");
  new Characteristic::Identifier(10);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi11 = new Service::InputSource();
  new Characteristic::ConfiguredName("Bluetooth");
  new Characteristic::Identifier(11);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi12 = new Service::InputSource();
  new Characteristic::ConfiguredName("PC External DAC");
  new Characteristic::Identifier(12);
  new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()



  (new HomeSpanTV("Rotel A12MKII Amplifier"))  // Define a Television Service.  Must link in InputSources!
    ->addLink(hdmi1)
    ->addLink(hdmi2)
    ->addLink(hdmi3)
    ->addLink(hdmi4)
    ->addLink(hdmi5)
    ->addLink(hdmi6)
    ->addLink(hdmi7)
    ->addLink(hdmi8)
    ->addLink(hdmi9)
    ->addLink(hdmi10)
    ->addLink(hdmi11)
    ->addLink(hdmi12);
}

///////////////////////////////

void loop() {
  homeSpan.poll();

  rs232receive();

}

