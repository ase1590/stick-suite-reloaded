#include <M5StickCPlus.h>
#include <IRremoteESP8266.h>
#include <IRsend.h> 

static int ir_menupos = 1;
bool setup_ir_complete = false;
const uint16_t kIrLed = 9;  // ESP32 GPIO pin to use. M5StickC-Plus uses 9 for IR
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.



// Example Sony TV captured from IRrecvDumpV2.ino
//uint16_t rawData[155] = {2362, 632,  1162, 634,  562, 634,  1162, 632,  564, 636,  1160, 632,  566, 634,  562, 612,  1186, 634,  564, 634,  562, 636,  562, 634,  566, 25856,  2362, 630,  1166, 634,  562, 586,  1212, 634,  562, 628,  1170, 634,  564, 630,  566, 632,  1162, 636,  562, 634,  562, 634,  564, 634,  564, 25852,  2362, 632,  1164, 594,  602, 634,  1164, 636,  562, 634,  1162, 618,  580, 634,  562, 632,  1164, 634,  564, 626,  572, 632,  564, 632,  566, 25850,  2364, 630,  1164, 632,  566, 634,  1162, 634,  564, 634,  1162, 634,  564, 634,  564, 630,  1166, 632,  564, 636,  564, 632,  566, 632,  564, 25854,  2362, 634,  1162, 634,  562, 634,  1162, 634,  562, 634,  1164, 632,  564, 636,  562, 634,  1164, 634,  562, 636,  562, 632,  568, 632,  564, 25854,  2360, 634,  1164, 630,  566, 634,  1162, 632,  566, 632,  1166, 630,  566, 634,  564, 634,  1162, 632,  564, 634,  564, 634,  562, 634,  562};  // SONY A90

void ir_handleScreen(){
//M5.Lcd.fillScreen(0x8631);
//M5.Lcd.pushImage(0, 0, imgWidth, imgHeight, img);
M5.Lcd.setCursor(40, 10);
M5.Lcd.setTextSize(2); //Every newline is 16 px
M5.Lcd.setTextColor(WHITE);
M5.Lcd.setTextColor(RED);
M5.Lcd.println("M5 IR");
M5.Lcd.setTextColor(WHITE);
}

void ir_clearcircles(){
  M5.Lcd.drawCircle(12,48,6,BLACK); //#1
  M5.Lcd.drawCircle(12,48+32,6,BLACK); //#2
  M5.Lcd.drawCircle(12,48+64,6,BLACK); //#3
  M5.Lcd.drawCircle(12,48+96,6,BLACK); //#4
}

// Display the menu options
void ir_setMenu(){
  M5.Lcd.println("");
  M5.Lcd.println("  Power\n");
  M5.Lcd.println("  Vol Up\n");
  M5.Lcd.println("  Vol Down\n");
  M5.Lcd.println("  Exit\n");
}

void ir_selector(){
  switch (ir_menupos)
  {
  case 1: //power
    M5.Lcd.drawCircle(12,48,6,CYAN);
    break;
  
  case 2: //vol up
    ir_clearcircles();
    M5.Lcd.drawCircle(12,48+32,6,CYAN);
    break;
  
  case 3: //vol down
    ir_clearcircles();
    M5.Lcd.drawCircle(12,48+64,6,CYAN);
    break;

  case 4:
    ir_clearcircles();
    M5.Lcd.drawCircle(12,48+96,6,CYAN);
    break;
  
  default:
    break;
  }
}


void sendSignal(){
  switch (ir_menupos)
  {
  case 1: //power
    irsend.sendSony(0xa90, 12, 2);
    delay(3);
    irsend.sendNEC(0x20DF10EF);
    break;

  case 2: //vol up
    irsend.sendSony(0x490,12,1); //sony TV
    delay(3);
    irsend.sendSony(0x24FF,15,1); //soundbar
    break;

  case 3: // vol down
    irsend.sendSony(0xC90,12,1); //sony TV
    delay(3);
    irsend.sendSony(0x64FF,15,1); //soundbar
    break;
    
  case 4:
    setup_ir_complete = !setup_ir_complete;
  
  default:
    break;
  }
}

void setup_irblaster()
{
    if(setup_ir_complete == false)
    {
        //M5.begin();
        M5.IMU.Init();
        M5.Lcd.setTextFont(1);
        M5.Lcd.setTextSize(1);
        M5.Lcd.setRotation(0);
        pinMode(M5_LED, OUTPUT); //give power to LED
        digitalWrite(M5_LED, HIGH); //Turn the LED itself off
        M5.Axp.ScreenBreath(8); //low power display dimming
        irsend.begin();
        digitalWrite(9, HIGH); //fix for IR LED staying on. force it to be off
        Serial.begin(115200, SERIAL_8N1);
        M5.Lcd.fillScreen(0x3186); //set the bg color to match the image's background for *transparent* text
        ir_menupos = 1;
        ir_handleScreen();
        ir_setMenu();
        ir_clearcircles();
        ir_selector();
        setup_ir_complete = !setup_ir_complete;
        //M5.Lcd.setSwapBytes(true); //set to big endian for compatibility
        //M5.Lcd.drawCircle(12,48,6,CYAN); //#1
        //M5.Lcd.drawCircle(12,48+32,6,CYAN); //#2
        //M5.Lcd.drawCircle(12,48+64,6,CYAN); //#3
    }

}


void loop_irblaster()
{
  while(setup_ir_complete == true)
  {
    if(digitalRead(M5_BUTTON_RST) == LOW)
    {
      ir_menupos++;
      if(ir_menupos>4)
      {
        ir_menupos = 1;
        ir_clearcircles();
      }
      ir_selector();
      Serial.println(ir_menupos);
      delay(250);
    }

    if(digitalRead(M5_BUTTON_HOME) == LOW)
    {
      digitalWrite(M5_LED,LOW);
      delay(100);
      digitalWrite(M5_LED,HIGH);
      sendSignal();
      digitalWrite(9,HIGH); //turn off IR led after send
      delay(100);
    }
  //break to main menu here
  //setup=!setup
  }

}