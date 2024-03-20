#include "HomeSpan.h"
bool power = 0;  //will be used in a later version
int input = 1;      //will be used in a later version
unsigned long previousMillis = 0; // Stores the last time an action was performed
const long interval = 5000;       // Interval at which to perform the action (5 seconds)



struct HomeSpanTV : Service::Television {

  SpanCharacteristic *active = new Characteristic::Active(0);              // TV On/Off (set to Off at start-up)
  SpanCharacteristic *activeID = new Characteristic::ActiveIdentifier(1);  // Sets HDMI 1 on start-up
  //SpanCharacteristic *remoteKey = new Characteristic::RemoteKey();                // Used to receive button presses from the Remote Control widget
  SpanCharacteristic *settingsKey = new Characteristic::PowerModeSelection();  // Adds "View TV Setting" option to Selection Screen

  HomeSpanTV(const char *name)
    : Service::Television() {
    new Characteristic::ConfiguredName(name);  // Name of TV
    Serial.printf("Configured TV: %s\n", name);
    Serial2.print("!rs232_update_off!");
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
        LOG0("Turning Amp ON.");      // Debugging statement
        delay(1000); // Adjust delay as needed to ensure the command is sent
        Serial2.print("!power_on!");   // send power on command
        LOG0("sent command to turn on");
        delay(1000); // Adjust delay as needed to ensure the command is sent
      } else {
        LOG0("Turning Amp OFF.");      // Debugging statement
        delay(1000);
        Serial2.print("!power_off!");  // send power off command
        delay(1000); // Adjust delay as needed to ensure the command is sent
      }
    }

    if (activeID->updated()) {  //Applying input selection switch
      Serial.printf("Set Input Source to HDMI-%d\n", activeID->getNewVal());
      Serial2.print("!");  //to ensure cleaning any previous commands

      //////////////////////////////
      if (activeID->getNewVal() == 1) {
        Serial2.print("cd");
      }
      if (activeID->getNewVal() == 2) {
        Serial2.print("coax1");
      }
      if (activeID->getNewVal() == 3) {
        Serial2.print("coax2");
      }
      if (activeID->getNewVal() == 4) {
        Serial2.print("opt1");
      }
      if (activeID->getNewVal() == 5) {
        Serial2.print("opt2");
      }
      if (activeID->getNewVal() == 6) {
        Serial2.print("aux1");
      }
      if (activeID->getNewVal() == 7) {
        Serial2.print("aux2");
      }
      if (activeID->getNewVal() == 8) {
        Serial2.print("tuner");
      }
      if (activeID->getNewVal() == 9) {
        Serial2.print("phono");
      }
      if (activeID->getNewVal() == 10) {
        Serial2.print("usb");
      }
      if (activeID->getNewVal() == 11) {
        Serial2.print("bluetooth");
      }
      if (activeID->getNewVal() == 12) {
        Serial2.print("pcusb");
      }
      //////////////////////////////////////////////////////

      Serial2.print("!");  //Applying command with termination mark
    }
    return (true);
  }

void loop() { //for updating status
  if (millis() - previousMillis >= interval) {
    previousMillis = millis(); // Update the last action time
    Serial.println("past 5s");
    Serial2.print("!power?!");
    delay(100);
    if (Serial2.available() > 0) {
      String responsePower = Serial2.readStringUntil('$'); // Read the RS232 response until the terminating "$" character
      if (responsePower.length() > 0) {
        Serial.println("Received RS232 power update: " + responsePower);

        if (responsePower.indexOf("power=") != -1) {
          bool newPower = (responsePower.indexOf("power=on") != -1); // Check if the response contains "power=on"
          if (newPower != power) { //detecting a change
            power = newPower;
            active->setVal(power ? 1 : 0); // Set the value to 1 for ON and 0 for OFF
          }
        }
      }
    }
    delay(100);
    Serial2.print("!source?!");
    delay(100);
    if (Serial2.available() > 0) {
      String responseSource = Serial2.readStringUntil('$'); // Read the RS232 response until the terminating "$" character
      if (responseSource.length() > 0) {
        Serial.println("Received RS232 source update: " + responseSource);
        int newInput = 0;
        if (responseSource.indexOf("source=") != -1) {

          //////////////List of inputs
          if(responseSource == "source=cd") {newInput=1;}
          if(responseSource == "source=coax1") {newInput=2;} 
          if(responseSource == "source=coax2") {newInput=3;} 
          if(responseSource == "source=opt1") {newInput=4;} 
          if(responseSource == "source=opt2") {newInput=5;} 
          if(responseSource == "source=aux1") {newInput=6;} 
          if(responseSource == "source=aux2") {newInput=7;} 
          if(responseSource == "source=tuner") {newInput=8;} 
          if(responseSource == "source=phono") {newInput=9;} 
          if(responseSource == "source=usb") {newInput=10;} 
          if(responseSource == "source=bluetooth") {newInput=11;} 
          if(responseSource == "source=pc_usb") {newInput=12;} 
          //////////////


          if (newInput != input) {
            input = newInput;
            activeID->setVal(input); // Set the new input
          }
        }
      }
    }
  }
}

};



///////////////////////////////

void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1);  // start Serial2 at 115200 8N1

  //homeSpan.enableOTA();
  homeSpan.begin(Category::Television, "Rotel A12MKII Ampplifier");

  SPAN_ACCESSORY();

  // Below we define 10 different InputSource Services using different combinations
  // of Characteristics to demonstrate how they interact and appear to the user in the Home App

  SpanService *hdmi1 = new Service::InputSource();
  new Characteristic::ConfiguredName("CD");
  new Characteristic::Identifier(1);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi2 = new Service::InputSource();
  new Characteristic::ConfiguredName("Coaxial 1");
  new Characteristic::Identifier(2);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi3 = new Service::InputSource();
  new Characteristic::ConfiguredName("Coaxial 2");
  new Characteristic::Identifier(3);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi4 = new Service::InputSource();
  new Characteristic::ConfiguredName("Optical 1");
  new Characteristic::Identifier(4);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi5 = new Service::InputSource();
  new Characteristic::ConfiguredName("Optical 2");
  new Characteristic::Identifier(5);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi6 = new Service::InputSource();
  new Characteristic::ConfiguredName("Auxiliary 1");
  new Characteristic::Identifier(6);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi7 = new Service::InputSource();
  new Characteristic::ConfiguredName("Auxiliary 2");
  new Characteristic::Identifier(7);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi8 = new Service::InputSource();
  new Characteristic::ConfiguredName("Tuner");
  new Characteristic::Identifier(8);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi9 = new Service::InputSource();
  new Characteristic::ConfiguredName("Phonograph");
  new Characteristic::Identifier(9);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi10 = new Service::InputSource();
  new Characteristic::ConfiguredName("USB");
  new Characteristic::Identifier(10);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi11 = new Service::InputSource();
  new Characteristic::ConfiguredName("Bluetooth");
  new Characteristic::Identifier(11);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

  SpanService *hdmi12 = new Service::InputSource();
  new Characteristic::ConfiguredName("PC External DAC");
  new Characteristic::Identifier(12);
  new Characteristic::IsConfigured(1);            // Source included in the Settings Screen...
  new Characteristic::CurrentVisibilityState(0);  // ...and included in the Selection List...
  new Characteristic::TargetVisibilityState(0);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()



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

}