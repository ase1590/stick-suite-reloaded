// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <M5StickCPlus.h>
#include "DHT.h"

#define DHTPIN 26     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


bool setup_temp_complete = false;




void temp_setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  M5.Lcd.setRotation(0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE,BLACK);
  M5.Lcd.setCursor(0,20);
  M5.Lcd.println(" Connect Pins");
  M5.Lcd.println(" Format:");
  M5.Lcd.println(" Sensor::Stick");
  M5.Lcd.println(" Pin1::G26");
  M5.Lcd.println(" Pin2::5v+(UP)");
  M5.Lcd.println(" Pin3::GND");
  M5.Lcd.println(" Sensor from kit");
  M5.Lcd.println(" can be directly");
  M5.Lcd.println(" connected to");
  M5.Lcd.println(" M5Stick");
  M5.Lcd.println("\n Click HOME \nwhen ready");
  delay(2000);
  while (digitalRead(M5_BUTTON_HOME) == HIGH)
    {
      delay(300);
    }

  dht.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.setTextSize(3);
  setup_temp_complete = !setup_temp_complete;
}

void temp_loop() {
    while (setup_temp_complete == true)
    {
        // Wait a few seconds between measurements.
        rechecksensor:
        delay(2000);

        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        float h = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();
        // Read temperature as Fahrenheit (isFahrenheit = true)
        float f = dht.readTemperature(true);

        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t) || isnan(f)) {
          Serial.println(F("Read Failed!"));
          M5.Lcd.fillScreen(RED);
          M5.Lcd.setCursor(10,10);
          M5.Lcd.println("FAILED");
          M5.Lcd.println("Retrying...");
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);
          delay(2000);
          M5.Lcd.fillScreen(BLACK);
          goto rechecksensor;
          //return;
        }

        // Compute heat index in Fahrenheit (the default)
        float hif = dht.computeHeatIndex(f, h);
        // Compute heat index in Celsius (isFahreheit = false)
        float hic = dht.computeHeatIndex(t, h, false);

        Serial.print(F("Humidity: "));
        Serial.print(h);
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F("°C "));
        Serial.print(f);
        Serial.print(F("°F  Heat index: "));
        Serial.print(hic);
        Serial.print(F("°C "));
        Serial.print(hif);
        Serial.println(F("°F"));
        
        //Humidity
        M5.Lcd.setCursor(10,10);
        M5.Lcd.print("HUM:");
        M5.Lcd.setCursor(4,32+10);
        M5.Lcd.print(h);
        M5.Lcd.print("%");
        //Temperature
        M5.Lcd.setCursor(10,64+20);
        M5.Lcd.print("TEMP:");
        M5.Lcd.setCursor(4,96+20);
        M5.Lcd.print(f);
        M5.Lcd.print("F");
        // Heat Index
        M5.Lcd.setCursor(10,128+30);
        M5.Lcd.print("H.Ind:");
        M5.Lcd.setCursor(4,160+30);
        M5.Lcd.print(hif);
        M5.Lcd.print("F");



        if(digitalRead(M5_BUTTON_RST) == LOW)
            {
                setup_temp_complete = !setup_temp_complete;
                return;
            }
    }

}