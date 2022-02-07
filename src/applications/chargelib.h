#include <M5StickCPlus.h>

M5StickCPlus chrg;


float b, c = 0;
int battery = 0;
unsigned long chg_timenow = 0;
int period_ms = 1000;


int batteryLevel() 
{
    b = chrg.Axp.GetVbatData() * 1.1 / 1000;
    //  chrg.Lcd.print(b);
    battery = ((b - 3.0) / 1.2) * 100;
    return battery;
};

void ChargeCheck(int chrg_x, int chrg_y, int chrg_colorbg)
{
    if(millis() - chg_timenow > period_ms)
    {
        chg_timenow = millis();
        if (c >= 4.5)
        {
            chrg.Lcd.setTextColor(DARKGREEN,chrg_colorbg);
            chrg.Lcd.setTextSize(1);
            chrg.Lcd.setTextFont(2);
            chrg.Lcd.setCursor(chrg_x, chrg_y);
            chrg.Lcd.printf("CHG: %02d%%", batteryLevel());
        }
        else 
        {
            chrg.Lcd.setTextColor(YELLOW,chrg_colorbg);
            chrg.Lcd.setTextSize(1);
            chrg.Lcd.setTextFont(2);
            chrg.Lcd.setCursor(chrg_x, chrg_y);
            chrg.Lcd.printf("BAT: %02d%%", batteryLevel());

        }

    }
    c = chrg.Axp.GetVapsData() * 1.4 / 1000;

};

void ChargeCheck_print(int chrg_x, int chrg_y, int chrg_colorbg)
{
        if (c >= 4.5)
        {
            chrg.Lcd.setTextColor(DARKGREEN,chrg_colorbg);
            chrg.Lcd.setTextSize(1);
            chrg.Lcd.setTextFont(2);
            chrg.Lcd.setCursor(chrg_x, chrg_y);
            chrg.Lcd.printf("CHG: %02d%%", batteryLevel());
        }
        else 
        {
            chrg.Lcd.setTextColor(YELLOW,chrg_colorbg);
            chrg.Lcd.setTextSize(1);
            chrg.Lcd.setTextFont(2);
            chrg.Lcd.setCursor(chrg_x, chrg_y);
            chrg.Lcd.printf("BAT: %02d%%", batteryLevel());

        }
    c = chrg.Axp.GetVapsData() * 1.4 / 1000;

};