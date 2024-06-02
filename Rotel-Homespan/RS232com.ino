void rs232send() {

  if(sending == 1){
      
    LOG1("\nRS232 is TX\n");

    //sending input request
    if (comInput!=input){
      if (comInput == 1) {Serial2.print(statusAction+"cd"+statusAction);Serial.println("CD set");}
      if (comInput == 2) {Serial2.print(statusAction+"coax1"+statusAction);Serial.println("coax1 set");}
      if (comInput == 3) {Serial2.print(statusAction+"coax2"+statusAction);Serial.println("coax2 set");}
      if (comInput == 4) {Serial2.print(statusAction+"opt1"+statusAction);Serial.println("opt1 set");}
      if (comInput == 5) {Serial2.print(statusAction+"opt2"+statusAction);Serial.println("opt2 set");}
      if (comInput == 6) {Serial2.print(statusAction+"aux1"+statusAction);Serial.println("aux1 set");}
      if (comInput == 7) {Serial2.print(statusAction+"aux2"+statusAction);Serial.println("aux2 set");}
      if (comInput == 8) {Serial2.print(statusAction+"tuner"+statusAction);Serial.println("tuner set");}
      if (comInput == 9) {Serial2.print(statusAction+"phono"+statusAction);Serial.println("phono set");}
      if (comInput == 10) {Serial2.print(statusAction+"usb"+statusAction);Serial.println("usb set");}
      if (comInput == 11) {Serial2.print(statusAction+"bluetooth"+statusAction);Serial.println("bluetooth set");}
      if (comInput == 12) {Serial2.print(statusAction+"pcusb"+statusAction);Serial.println("pcusb set");}
      Serial.println("Set input source to "+comInput);
    }

    //sending power request
    if ((comPower != power) && (comPower==1)) {Serial2.print(statusAction+statusPowerSet+statusAction);Serial.println("sent command turning Amp On");}
    if ((comPower != power) && (comPower==0)) {Serial2.print(statusAction+statusPowerUnset+statusAction);Serial.println("sent command turning Amp Off");}

    //sending volume request
    if (comVolume != volume) {
      if (comVolume==0){
        Serial2.print(statusAction+statusVolume+comVolume+statusAction+statusMuteSet+statusAction);
      } else {
        Serial2.print(statusAction+statusVolume+comVolume+statusAction);
      }
      Serial.print("Applied volume is ");Serial.print(comVolume);Serial.println("%");
    }

    //Speaker switching
    if (comSpeakerA != speakerA){
      if (comSpeakerA==1){
        Serial2.print(statusAction+statusSpeakerSet+"a_on"+statusAction);Serial.println("Speaker A Enabled");LOG1(statusAction+statusSpeakerSet+"a_on"+statusAction+"\n");
      } else {
        Serial2.print(statusAction+statusSpeakerSet+"a_off"+statusAction);Serial.println("Speaker A Disabled");LOG1(statusAction+statusSpeakerSet+"a_off"+statusAction+"\n");
        }
    }
    if (comSpeakerB != speakerB){
      if (comSpeakerB==1){
        Serial2.print(statusAction+statusSpeakerSet+"b_on"+statusAction);Serial.println("Speaker B Enabled");LOG1(statusAction+statusSpeakerSet+"b_on"+statusAction+"\n");
      } else {
        Serial2.print(statusAction+statusSpeakerSet+"b_off"+statusAction);Serial.println("Speaker B Disabled");LOG1(statusAction+statusSpeakerSet+"b_off"+statusAction+"\n");
      }
    }

    //Display Brightness
    if (comBrightness != brightness){
      Serial2.print(statusAction+statusBrightnessSet+(6-comBrightness)+statusAction);Serial.print("Brightness set to : ");Serial.println(comBrightness);LOG1(statusAction+statusBrightnessSet+(6-comBrightness)+statusAction+"\n");

    }

    //Applying Balance
    if (comBalance != balance) {
      if (comBalance == 50) {
        Serial2.print(statusAction+statusBalanceSet+"000"+statusAction);Serial.print("Balance Centered");
      } else if (comBalance < 50) {
      sprintf(formatBuffer, "%02d", ((50-comBalance)/3));
      Serial2.print(statusAction+statusBalanceSet+"l"+formatBuffer+statusAction);Serial.print("Balance set to : L");Serial.println(formatBuffer);LOG1(statusAction+statusBalanceSet+"l"+formatBuffer+statusAction+"\n");
      } else if (comBalance > 50) {
      sprintf(formatBuffer, "%02d", ((comBalance-50)/3));
      Serial2.print(statusAction+statusBalanceSet+"r"+formatBuffer+statusAction);Serial.print("Balance set to : R");Serial.println(formatBuffer);LOG1(statusAction+statusBalanceSet+"r"+formatBuffer+statusAction+"\n");
      }
    }

    //Applying ByPass
    if (comBypass != bypass){
      if (comBypass == 1){
        Serial2.print(statusAction+statusBypassSet+"on"+statusAction);Serial.println("ByPass Enabled");LOG1(statusAction+statusBypassSet+"on"+statusAction+"\n");
      } else {
        Serial2.print(statusAction+statusBypassSet+"off"+statusAction);Serial.println("ByPass Disabled");LOG1(statusAction+statusBypassSet+"off"+statusAction+"\n");
      }
    }

    //Applying Treble
    if (comTreble != treble) {
      if (comTreble == 0) {
        Serial2.print(statusAction+statusTrebleSet+"000"+statusAction);Serial.println("Changed Treble to neutral");LOG1(statusAction+statusTrebleSet+"000"+statusAction+"\n");
      } else {
        sprintf(formatBuffer, "%+03d", comTreble);
        Serial2.print(statusAction+statusTrebleSet+formatBuffer+statusAction);Serial.println("Changed Treble");LOG1(statusAction+statusTrebleSet+formatBuffer+statusAction+"\n");
      }
    }

    //Applying Bass
    if (comBass != bass) {
      if (comBass == 0) {
        Serial2.print(statusAction+statusBassSet+"000"+statusAction);Serial.println("Changed Bass to neutral");LOG1(statusAction+statusBassSet+"000"+statusAction+"\n");
      } else {
        sprintf(formatBuffer, "%+03d", comBass);
        Serial2.print(statusAction+statusBassSet+formatBuffer+statusAction);Serial.println("Changed Bass");LOG1(statusAction+statusBassSet+formatBuffer+statusAction+"\n");
      }
    }


    sending = 0;
    //input=comInput;
    //power=comPower;
    //volume=comVolume;
    //speakerA=comSpeakerA;
    //speakerB=comSpeakerB;
    //brightness=comBrightness;
    //balance=comBalance;

  }

    //status request actions
    if ((receiving == 1) || (receiving == 3)){

      //asking power status
      Serial2.print(statusAction+statusPower+statusAsk);

      //asking input status
      Serial2.print(statusAction+statusSource+statusAsk);

      //asking Volume status
      Serial2.print(statusAction+statusVolumeGet+statusAsk);

      Serial.println("requested status");

      //asking Speaker status
      Serial2.print(statusAction+statusSpeakerGet+statusAsk);

      //asking Brightness status
      Serial2.print(statusAction+statusBrightnessGet+statusAsk);

      //asking Balance status
      Serial2.print(statusAction+statusBalanceGet+statusAsk);

      //asking ByPass status
      Serial2.print(statusAction+statusBypassGet+statusAsk);

      //asking Bass status
      Serial2.print(statusAction+statusBassGet+statusAsk);
      
      //asking Treble status
      Serial2.print(statusAction+statusTrebleGet+statusAsk);

      Serial.println("requested advanced status");

      receiving=0;
  }


}

void rs232receive(){

  String recievedType;
  String recievedData;
  //LOG2("\nreading\n");
  while (Serial2.available()) {
    LOG2("\nreading\n");
    char c = Serial2.read();
    if (c == '$') { //detected end of transmission

    int separatorIndex = recievedData.indexOf('=');
    if (separatorIndex != -1) {
      recievedType = recievedData.substring(0, separatorIndex);
      recievedData = recievedData.substring(separatorIndex + 1);


      //Power extraction
      if (recievedType == statusPowerDetect) {
        LOG0("\ndetected power status\n");

        if (recievedData == statusPowerOnGet){comPower=1;}
        if (recievedData == statusPowerOffGet){comPower=0;}

      }

      //Input extraction
      if (recievedType == statusSourceDetect) {
        LOG0("\ndetected input source\n");

        if(recievedData == "cd") {comInput=1;}
        if(recievedData == "coax1") {comInput=2;} 
        if(recievedData == "coax2") {comInput=3;} 
        if(recievedData == "opt1") {comInput=4;} 
        if(recievedData == "opt2") {comInput=5;} 
        if(recievedData == "aux1") {comInput=6;} 
        if(recievedData == "aux2") {comInput=7;} 
        if(recievedData == "tuner") {comInput=8;} 
        if(recievedData == "phono") {comInput=9;} 
        if(recievedData == "usb") {comInput=10;} 
        if(recievedData == "bluetooth") {comInput=11;} 
        if(recievedData == "pc_usb") {comInput=12;}

        if (comInput != input) {receiving=1;}
      }

      //Volume extraction
      if (recievedType == statusVolumeGet) {
        LOG0("\nDetected Volume Change\n");
        
        comVolume = recievedData.toInt();  // will be looked later
      }

      //Active Speaker extraction
      if (recievedType == statusSpeakerGet) {
        LOG0("\nDetected Speaker activation\n");
        if (recievedData.indexOf('a') != -1) {
          LOG0("Speaker A is on\n");
          comSpeakerA=1;
        } else {
          LOG0("Speaker A is off\n");
          comSpeakerA=0;
        }
        if (recievedData.indexOf('b') != -1) {
          LOG0("Speaker B is on\n");
          comSpeakerB=1;
        } else {
          LOG0("Speaker B is off\n");
          comSpeakerB=0;
        }
      }

      //Display Brightness extraction
      if (recievedType == statusBrightnessGet) {
        LOG0("detected brightness/n");
        comBrightness=6-recievedData.toInt();
      }

      //Detect Speaker Balance
      if (recievedType == statusBalanceGet){
        if (recievedData == "000"){
          comBalance = 50;
        }
        if (recievedData.indexOf('L') != -1) {
          LOG1("detected Left Balance\n");
          separatorIndex = recievedData.indexOf('L');
          int balanceData = recievedData.substring(separatorIndex + 1).toInt();
          comBalance = 50-(balanceData*3);
        }
        if (recievedData.indexOf('R') != -1) {
          LOG1("detected Right Balance\n");
          separatorIndex = recievedData.indexOf('R');
          int balanceData = recievedData.substring(separatorIndex + 1).toInt();
          comBalance = (balanceData*3)+50;
        }
      }

      //Detect ByPass mode
      if (recievedType == statusBypassGet){
        LOG0("\ndetected Bypass status\n");

        if (recievedData == "on"){comBypass=1;}
        if (recievedData == "off"){comBypass=0;}
      }

      //Detect Treble level
      if (recievedType == statusTrebleGet) {
        LOG0("\nDetected Treble Change\n");
        
        comTreble = recievedData.toInt();  // will be looked later
      }

      //Detect Bass level
      if (recievedType == statusBassGet) {
        LOG0("\nDetected Bass Change\n");
        
        comBass = recievedData.toInt();  // will be looked later
      }


      // Clear recievedData for the next message
      LOG1("\n");
      LOG1("<--received full message-->");
      LOG1("\n     ->");
      LOG1(recievedType);
      LOG1(" = ");
      LOG1(recievedData);
      ;recievedData = "";
    }

    } else {
      // Append character to received data
      recievedData += c;
      LOG2("\n");
      LOG2(c);
      LOG2("\n");
    }
  }

}
