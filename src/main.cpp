//#include <Arduino.h>
#include <M5StickCPlus.h>
#include <Free_Fonts.h>
#include <assets/CustomImages.h>
#include <applications/temp.h>


int menu_pos = 0;
float b, c = 0;
int battery = 0;


//2d array for storing values 100 in length
char menulist[][100] = { 
  "REMOTE.exe",
  "TEMP.exe",
  "WiSPAM.exe",
  "BT-KBD.exe"
};





int batteryLevel() 
{
    b = M5.Axp.GetVbatData() * 1.1 / 1000;
    //  M5.Lcd.print(b);
    battery = ((b - 3.0) / 1.2) * 100;
    return battery;
};

void ChargeCheck()
{
    c = M5.Axp.GetVapsData() * 1.4 / 1000;
    if (c >= 4.5)
    {
        M5.Lcd.setTextColor(GREEN,BLACK);
        M5.Lcd.setFreeFont(FSS9);
        M5.Lcd.setCursor(150, 130);
        M5.Lcd.printf("CHG: %02d%%", batteryLevel());
        M5.Lcd.setTextColor(BLACK,WHITE);
        M5.Lcd.setFreeFont(FSSB12);
    }
    else 
    {
        M5.Lcd.setTextColor(YELLOW,BLACK);
        M5.Lcd.setFreeFont(FSS9);
        M5.Lcd.setCursor(150, 130);
        M5.Lcd.printf("BAT: %02d%%", batteryLevel());
        M5.Lcd.setTextColor(BLACK,WHITE);
        M5.Lcd.setFreeFont(FSSB12);

    }
};




void menuselector(){
  if(digitalRead(M5_BUTTON_RST) == LOW){
    menu_pos++;
    if(menu_pos+1 > sizeof(menulist)/sizeof(menulist[0])){
      menu_pos = 0;
    }
    M5.Lcd.pushImage(0,0,winimgWidth,winimgHeight,winimage);
    ChargeCheck();
    M5.Lcd.setCursor(65, 70);
    M5.Lcd.print(menulist[menu_pos]);
    delay(300);
  }
}


void setup_mainMenu(){
    M5.Lcd.setRotation(1);
    M5.Axp.ScreenBreath(8);
    //M5.Lcd.fillScreen(BLACK);
    M5.Lcd.pushImage(0,0,winimgWidth,winimgHeight,winimage);
    ChargeCheck();
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
    }
    else if(menu_pos==1){
      //do stuff
      temp_setup();
      temp_loop();
      setup_mainMenu();
    }
    else if(menu_pos==2){
      //do stuff
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
}