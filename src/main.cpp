//#include <Arduino.h>
#include <M5StickCPlus.h>
#include <Free_Fonts.h>
#include <assets/CustomImages.h>
#include <applications/temp.h>
#include <applications/wifibeacon.h>
#include <applications/irblaster.h>
#include <applications/chargelib.h>
#include <BleKeyboard.h>
#define win_grey 0xC67A



int menu_pos = 0;

//2d array for storing values 100 in length
char menulist[][100] = { 
  "REMOTE.exe",
  "TEMP.exe",
  "WiSPAM.exe",
  "BT-KBD.exe"
};




void menuselector(){
  if(digitalRead(M5_BUTTON_RST) == LOW){
    menu_pos++;
    if(menu_pos+1 > sizeof(menulist)/sizeof(menulist[0])){
      menu_pos = 0;
    }
    M5.Lcd.pushImage(0,0,winimgWidth,winimgHeight,winimage);
    ChargeCheck_print(175,115,win_grey);
    M5.Lcd.setCursor(65, 70);
    M5.Lcd.print(menulist[menu_pos]);
    delay(300);
  }
}


void setup_mainMenu(){
    M5.Lcd.setRotation(1);
    chrg.Lcd.setRotation(1);
    M5.Axp.ScreenBreath(9);
    //M5.Lcd.fillScreen(BLACK);
    M5.Lcd.pushImage(0,0,winimgWidth,winimgHeight,winimage);
    ChargeCheck(175,115,win_grey);
    M5.Lcd.setCursor(65, 70);
    //M5.Lcd.setTextSize(2);
    M5.Lcd.setFreeFont(FSSB12); //FreeSansBold - 9 point
    M5.Lcd.setTextColor(BLACK,WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print(menulist[menu_pos]);
}

void loop_mainMenu(){
  if(digitalRead(M5_BUTTON_HOME) == LOW){
    if(menu_pos==0){
      //do stuff
      setup_irblaster();
      loop_irblaster();
      setup_mainMenu();
      delay(300);
    }
    else if(menu_pos==1){
      //do stuff
      temp_setup();
      temp_loop();
      setup_mainMenu();
      delay(300);
    }
    else if(menu_pos==2){
      //do stuff
      setup_wifispam();
      loop_wifispam();
      setup_mainMenu();
      delay(300);
    }
    else if(menu_pos==3){
      //do stuff
    }
  }
}


void setup() {
  M5.begin();
  setup_mainMenu();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  menuselector();
  loop_mainMenu();
  ChargeCheck(175,115,win_grey);
  //M5.Lcd.setFreeFont(FSSB12);
  //M5.Lcd.setTextColor(BLACK,WHITE);
}