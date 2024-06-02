//////////////////////////////////
//   DEVICE-SPECIFIC SERVICES   //
//////////////////////////////////


extern int volume;
extern int comVolume;
extern bool speakerA;
extern bool comSpeakerA;
extern bool speakerB;
extern bool comSpeakerB;
extern int brightness;
extern int comBrightness;
extern int balance;
extern int comBalance;
extern bool bypass;
extern bool comBypass;
extern int bass;
extern int comBass;
extern int treble;
extern int comTreble;






struct DEV_RotelSettings : Service::Television {

  SpanCharacteristic *ConfiguredName;
  SpanCharacteristic *Name;
  SpanCharacteristic *active;


    DEV_RotelSettings() : Service::Television(){
    ConfiguredName = new Characteristic::ConfiguredName("Amplifier Settings");
    Name = new Characteristic::Name("Amplifier Settings");
  }
};

struct DEV_RotelVolume : 

  Service::Fan {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *RotationSpeed;

    DEV_RotelVolume() : Service::Fan(){
    ConfiguredName = new Characteristic::ConfiguredName("1-Volume");
    RotationSpeed = (new Characteristic::RotationSpeed(35))->setRange(0,100,1);
  }

  boolean update() override {
  
    if (RotationSpeed->updated()){
      comVolume=RotationSpeed->getNewVal();
      sending=1;
    }

  return (true);
  };

  void loop() {

    if ((comVolume!=volume) && (sending !=1)){
      RotationSpeed->setVal(comVolume); // Set Volume
      volume=comVolume;
    }

  };

};

struct DEV_RotelBrightness :

  Service::LightBulb {

    SpanCharacteristic *Name;
    SpanCharacteristic *Brightness;
    SpanCharacteristic *ConfiguredName;


    DEV_RotelBrightness() : Service::LightBulb(){
    Name = new Characteristic::Name("2-Display Brightness");
    ConfiguredName = new Characteristic::ConfiguredName("2-Display Brightness");
    Brightness = (new Characteristic::Brightness(98))->setRange(0,100,16);
  }

  boolean update() override {
  
    if (Brightness->updated()){
      Serial.println("HK brightness change");
      comBrightness=(Brightness->getNewVal()/16);
      sending=1;
    }

  return (true);
  };

  void loop() {

    if ((comBrightness!=brightness) && (sending !=1)){
      Serial.println("HK brightness update");
      Brightness->setVal(comBrightness*14); // Set Volume
      brightness=comBrightness;
    }

  };

};

struct DEV_RotelByPass :

  Service::Switch {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *On;

    DEV_RotelByPass() : Service::Switch(){
    ConfiguredName = new Characteristic::ConfiguredName("6-ByPass");
    On = new Characteristic::On();
  }
    boolean update() override {
  
    if (On->updated()){
      Serial.println("HK Bypass change");
      comBypass=On->getNewVal();
      sending=1;
    }

  return (true);
  };

  void loop() {

    if ((comBypass!=bypass) && (sending !=1)){
      Serial.println("HK Bypass update");
      On->setVal(comBypass); // Set Bypass
      bypass=comBypass;
    }
  };
};

struct DEV_RotelBalance :

  Service::Fan {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *RotationSpeed;

    DEV_RotelBalance() : Service::Fan(){
    ConfiguredName = new Characteristic::ConfiguredName("5-Balance");
    RotationSpeed = (new Characteristic::RotationSpeed(50))->setRange(5,95,3);
  }

  boolean update() override {
  
    if (RotationSpeed->updated()){
      comBalance=(RotationSpeed->getNewVal());
      sending=1;
      LOG1("HK Balance value is : ");
      LOG1(comBalance);
      LOG1("\n");
    }

  return (true);
  };

  void loop() {

    if ((comBalance!=balance) && (sending !=1)){
      RotationSpeed->setVal(comBalance); // Set Volume
      balance=comBalance;
    }

  };

};

struct DEV_RotelTreble :

  Service::Fan {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *RotationSpeed;

    DEV_RotelTreble() : Service::Fan(){
    ConfiguredName = new Characteristic::ConfiguredName("7-Trebble");
    RotationSpeed = (new Characteristic::RotationSpeed(50))->setRange(0,100,5);
  }
  boolean update() override {
  
    if (RotationSpeed->updated()){
      comTreble=((RotationSpeed->getNewVal()-50)/5);
      sending=1;
      LOG1("HK treble value is : ");
      LOG1(comTreble);
      LOG1("\n");
    }
  return (true);
  };

  void loop() {

    if ((comTreble!=treble) && (sending !=1)){
      RotationSpeed->setVal((comTreble*5)+50); // Set Volume
      treble=comTreble;
    }
  };
};

struct DEV_RotelBass :

  Service::Fan {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *RotationSpeed;

    DEV_RotelBass() : Service::Fan(){
    ConfiguredName = new Characteristic::ConfiguredName("8-Bass");
    RotationSpeed = (new Characteristic::RotationSpeed(50))->setRange(0,100,5);
    }

    boolean update() override {

    if (RotationSpeed->updated()){
      comBass=((RotationSpeed->getNewVal()-50)/5);
      sending=1;
      LOG1("HK bass value is : ");
      LOG1(comBass);
      LOG1("\n");
    }
  return (true);
  };

  void loop() {

    if ((comBass!=bass) && (sending !=1)){
      RotationSpeed->setVal((comBass*5)+50); // Set Volume
      bass=comBass;
    }
  };

};

struct DEV_RotelSpeakerA :

  Service::Switch {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *On;

    DEV_RotelSpeakerA() : Service::Switch(){
    ConfiguredName = new Characteristic::ConfiguredName("3-Speaker A");
    On = new Characteristic::On();
  }

    boolean update() override {
  
    if (On->updated()){
      Serial.println("HK Speaker A change");
      comSpeakerA=On->getNewVal();
      sending=1;
    }

  return (true);
  };

  void loop() {

    if ((comSpeakerA!=speakerA) && (sending !=1)){
      Serial.println("HK Speaker A update");
      On->setVal(comSpeakerA); // Set Volume
      speakerA=comSpeakerA;
    }

  };


};

struct DEV_RotelSpeakerB :

  Service::Switch {

    SpanCharacteristic *ConfiguredName;
    SpanCharacteristic *On;

    DEV_RotelSpeakerB() : Service::Switch(){
    ConfiguredName = new Characteristic::ConfiguredName("4-Speaker B");
    On = new Characteristic::On();
  }
    boolean update() override {
  
    if (On->updated()){
      Serial.println("HK Speaker A change");
      comSpeakerB=On->getNewVal();
      sending=1;
    }

  return (true);
  };

  void loop() {

    if ((comSpeakerB!=speakerB) && (sending !=1)){
      Serial.println("HK Speaker B update");
      On->setVal(comSpeakerB); // Set Volume
      speakerB=comSpeakerB;
    }

  };

};
