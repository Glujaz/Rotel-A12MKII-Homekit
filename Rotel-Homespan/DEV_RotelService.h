//////////////////////////////////
//   DEVICE-SPECIFIC SERVICES   //
//////////////////////////////////

extern bool power;
extern bool comPower;
extern int input;
extern int comInput;
extern bool receiving;
extern bool sending;
bool settings=true;


struct DEV_RotelService : Service::Television {

  SpanCharacteristic *active;
  SpanCharacteristic *activeID;
  SpanCharacteristic *PowerModeSelection;
  SpanCharacteristic *ConfiguredName;
  SpanCharacteristic *CTcd;
  SpanCharacteristic *Tcd;
  SpanCharacteristic *CTcoax1;
  SpanCharacteristic *Tcoax1;
  SpanCharacteristic *CTcoax2;
  SpanCharacteristic *Tcoax2;
  SpanCharacteristic *CTopt1;
  SpanCharacteristic *Topt1;
  SpanCharacteristic *CTopt2;
  SpanCharacteristic *Topt2;
  SpanCharacteristic *CTaux1;
  SpanCharacteristic *Taux1;
  SpanCharacteristic *CTaux2;
  SpanCharacteristic *Taux2;
  SpanCharacteristic *CTtuner;
  SpanCharacteristic *Ttuner;
  SpanCharacteristic *CTphono;
  SpanCharacteristic *Tphono;
  SpanCharacteristic *CTusb;
  SpanCharacteristic *Tusb;
  SpanCharacteristic *CTbt;
  SpanCharacteristic *Tbt;
  SpanCharacteristic *CTpcusb;
  SpanCharacteristic *Tpcusb;


    DEV_RotelService() : Service::Television(){
        active = new Characteristic::Active(0);
        PowerModeSelection = new Characteristic::PowerModeSelection();
        activeID = new Characteristic::ActiveIdentifier();
        ConfiguredName= new Characteristic::ConfiguredName("Audio Amplifier");

        
          SpanService *cd = new Service::InputSource();
          new Characteristic::ConfiguredName("CD",true);
          new Characteristic::Identifier(1);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTcd = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tcd = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *coax1 = new Service::InputSource();
          new Characteristic::ConfiguredName("Coaxial 1",true);
          new Characteristic::Identifier(2);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTcoax1 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tcoax1 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *coax2 = new Service::InputSource();
          new Characteristic::ConfiguredName("Coaxial 2",true);
          new Characteristic::Identifier(3);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTcoax2 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tcoax2 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *opt1 = new Service::InputSource();
          new Characteristic::ConfiguredName("Optical 1",true);
          new Characteristic::Identifier(4);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTopt1 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Topt1 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *opt2 = new Service::InputSource();
          new Characteristic::ConfiguredName("Optical 2",true);
          new Characteristic::Identifier(5);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTopt2 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Topt2 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *aux1 = new Service::InputSource();
          new Characteristic::ConfiguredName("Auxiliary 1",true);
          new Characteristic::Identifier(6);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTaux1 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Taux1 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *aux2 = new Service::InputSource();
          new Characteristic::ConfiguredName("Auxiliary 2",true);
          new Characteristic::Identifier(7);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTaux2 = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Taux2 = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *tuner = new Service::InputSource();
          new Characteristic::ConfiguredName("Tuner",true);
          new Characteristic::Identifier(8);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTtuner = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Ttuner = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *phono = new Service::InputSource();
          new Characteristic::ConfiguredName("Phonograph",true);
          new Characteristic::Identifier(9);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTphono = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tphono = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *usb = new Service::InputSource();
          new Characteristic::ConfiguredName("USB",true);
          new Characteristic::Identifier(10);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTusb = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tusb = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *bt = new Service::InputSource();
          new Characteristic::ConfiguredName("Bluetooth",true);
          new Characteristic::Identifier(11);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTbt = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tbt = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()

          SpanService *pcusb = new Service::InputSource();
          new Characteristic::ConfiguredName("PC External DAC",true);
          new Characteristic::Identifier(12);
          new Characteristic::IsConfigured(1,true);            // Source included in the Settings Screen...
          CTpcusb = new Characteristic::CurrentVisibilityState(0,true);  // ...and included in the Selection List...
          Tpcusb = new Characteristic::TargetVisibilityState(0,true);   // ...and a "checked" checkbox is provided on the Settings Screen that can be used to toggle CurrentVisibilityState()


        addLink(cd);
        addLink(coax1);
        addLink(coax2);
        addLink(opt1);
        addLink(opt2);
        addLink(aux1);
        addLink(aux2);
        addLink(tuner);
        addLink(phono);
        addLink(usb);
        addLink(bt);
        addLink(pcusb);


    }


  boolean update() override {

    if (active->updated()){
      if (active->getNewVal()==1){
        LOG0("\nHK Power updated to ON\n");
        comPower=1;
        sending=1;
      } else {
        LOG0("\nHK Power updated to OFF\n");
        comPower=0;
        sending=1;
      }
    }
    if (activeID->updated()){
      Serial.printf("Setting Input Source to input %d\n", activeID->getNewVal());

      //////////////////////////////
      if (activeID->getNewVal() == 1) {comInput=1;sending=1;}
      if (activeID->getNewVal() == 2) {comInput=2;sending=1;}
      if (activeID->getNewVal() == 3) {comInput=3;sending=1;}
      if (activeID->getNewVal() == 4) {comInput=4;sending=1;}
      if (activeID->getNewVal() == 5) {comInput=5;sending=1;}
      if (activeID->getNewVal() == 6) {comInput=6;sending=1;}
      if (activeID->getNewVal() == 7) {comInput=7;sending=1;}
      if (activeID->getNewVal() == 8) {comInput=8;sending=1;}
      if (activeID->getNewVal() == 9) {comInput=9;sending=1;}
      if (activeID->getNewVal() == 10) {comInput=10;sending=1;}
      if (activeID->getNewVal() == 11) {comInput=11;sending=1;}
      if (activeID->getNewVal() == 12) {comInput=12;sending=1;}

    }

    if(PowerModeSelection->updated()){
      Serial.printf("Received request to \"View TV Settings\"\n");
    }

    return (true);

  };


  void loop() {

    if((comPower != power) && (sending !=1)){
      LOG0("\nReading and applying new power state : ");
      LOG0(comPower);
      LOG0("\n");
      active->setVal(comPower); // Set power state
      power = comPower;
    } 


    if((comInput != input) && (sending !=1)){
      LOG0("\nReading and applying new source : ");
      LOG0(comInput);
      LOG0("\n");
      activeID->setVal(comInput); // Set input state
      input = comInput;
    }

    if(Tcd->getVal() != CTcd->getVal()){
      CTcd->setVal(Tcd->getVal());
    }
    if(Tcoax1->getVal() != CTcoax1->getVal()){
      CTcoax1->setVal(Tcoax1->getVal());
    }
    if(Tcoax2->getVal() != CTcoax2->getVal()){
      CTcoax2->setVal(Tcoax2->getVal());
    }
    if(Topt1->getVal() != CTopt1->getVal()){
      CTopt1->setVal(Topt1->getVal());
    }
    if(Topt2->getVal() != CTopt2->getVal()){
      CTopt2->setVal(Topt2->getVal());
    }
    if(Taux1->getVal() != CTaux1->getVal()){
      CTaux1->setVal(Taux1->getVal());
    }
    if(Taux2->getVal() != CTaux2->getVal()){
      CTaux2->setVal(Taux2->getVal());
    }
    if(Ttuner->getVal() != CTtuner->getVal()){
      CTtuner->setVal(Ttuner->getVal());
    }
    if(Tphono->getVal() != CTphono->getVal()){
      CTphono->setVal(Tphono->getVal());
    }
    if(Tusb->getVal() != CTusb->getVal()){
      CTusb->setVal(Tusb->getVal());
    }
    if(Tbt->getVal() != CTbt->getVal()){
      CTbt->setVal(Tbt->getVal());
    }
    if(Tpcusb->getVal() != CTpcusb->getVal()){
      CTpcusb->setVal(Tpcusb->getVal());
    }


  };

};