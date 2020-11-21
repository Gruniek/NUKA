//The Game of Life, also known simply as Life, is a cellular automaton
//devised by the British mathematician John Horton Conway in 1970.
// https://en.wikipedia.org/wiki/Conway's_Game_of_Life

// See license at end of file.

// Adapted by Bodmer

#include "config.h"
#include <Wire.h>
#include <RTC.h>

#include "objects.h"



bool irq = false;

static PCF8563 RTC;

//TTGOClass *ttgo;
AXP20X_Class *power;


bool SCREEN_ON = true;
uint8_t hh , mm , ss ; 

byte omm = 99;
boolean initial = 1;
byte xcolon = 0;
unsigned int colour = 0;


int cpt = 0;


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;




void setup()
{
    Serial.begin(115200);

    SerialBT.begin("TTGO"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");

  
    RTC.begin();

    Serial.println();



    //Set up the display
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    // ttgo->tft->setRotation(3);
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setTextFont(2);
    ttgo->tft->setTextSize(1);
    ttgo->tft->setTextColor(TFT_WHITE);
    ttgo->tft->setCursor(0, 0);


    pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(AXP202_INT, [] 
    {
        irq = true;
    }, FALLING);

    //!Clear IRQ unprocessed  first
    ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
    ttgo->power->clearIRQ();

    //GET POWER INFO
    power = ttgo->power;
    power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);


}

void loop()
{
    // IRQ DATA
    if (irq) 
    {
        irq = false;
        ttgo->power->readIRQ();
        if (ttgo->power->isVbusPlugInIRQ())    // If in charge
        {
          Serial.println("IN CHARGE");
        }
        if (ttgo->power->isVbusRemoveIRQ())    // If On battery
        {
          Serial.println("ON BATTERY");
        }
        if (ttgo->power->isPEKShortPressIRQ()) // If key is pressed
        {
          if(SCREEN_ON == true) SCREEN_ON = false;
          else 
          {
            SCREEN_ON = true;
            cpt = 0;
          }
        }
        ttgo->power->clearIRQ();
    }
    
    // sleep 
    if(SCREEN_ON == true) { ttgo->openBL(); }
    else { ttgo->closeBL(); }
    if(cpt == 5) SCREEN_ON = false;
    cpt++;




    if(SCREEN_ON)
    {
      Serial.print(RTC.getHours());
      Serial.print(":");
      Serial.print(RTC.getMinutes());
      Serial.print(":");
      Serial.print(RTC.getSeconds());
      Serial.println(" ");


      ttgo->tft->drawRect(0, 0, 240, 240, TFT_GREEN);
      ttgo->tft->drawRect(0, 0, 240, 60, TFT_GREEN);

      battery_level(power->getBattPercentage(), true, 205, 5);

        // Update digital time
        byte xpos = 51;
        byte ypos = 6;
        hh = RTC.getHours();
        mm = RTC.getMinutes();
        ss = RTC.getSeconds();
        if (omm != mm) { // Only redraw every minute to minimise flicker
            // Uncomment ONE of the next 2 lines, using the ghost image demonstrates text overlay as time is drawn over it
            ttgo->tft->setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
            //ttgo->tft->setTextColor(TFT_BLACK, TFT_BLACK); // Set font colour to black to wipe image
            // Font 7 is to show a pseudo 7 segment display.
            // Font 7 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .
            ttgo->tft->drawString("88:88", xpos, ypos, 7); // Overwrite the text to clear it
            ttgo->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange
            omm = mm;

            if (hh < 10) xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
            xpos += ttgo->tft->drawNumber(hh, xpos, ypos, 7);
            xcolon = xpos;
            xpos += ttgo->tft->drawChar(':', xpos, ypos, 7);
            if (mm < 10) xpos += ttgo->tft->drawChar('0', xpos, ypos, 7);
            ttgo->tft->drawNumber(mm, xpos, ypos, 7);
        }



        Serial.println("VBUS");
        Serial.println("---------");
        Serial.print("VBUS VOLTAGE : ");
        Serial.println(power->getVbusVoltage());
        Serial.print("VBUS CURRENT : ");
        Serial.println(power->getVbusCurrent());
        Serial.println(" ");
        Serial.println("BATTERY");
        Serial.println("---------");
        Serial.print("BAT VOLTAGE : ");
        Serial.println(power->getBattVoltage());
        Serial.print("BAT CHARGE : ");
        Serial.println(power->getBattChargeCurrent());
        Serial.print("BAT DISCHARGE CURRENT : ");
        Serial.println(power->getBattDischargeCurrent());
        Serial.print("BAT % : ");
        Serial.println(power->getBattPercentage());
        
     }
    delay(1000);

    SerialBT.print("BAT mA : ");
    SerialBT.println(power->getBattDischargeCurrent());
    SerialBT.print("BAT % : ");
    SerialBT.println(power->getBattPercentage());


}
   
