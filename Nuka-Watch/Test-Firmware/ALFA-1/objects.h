#include <Arduino.h>
#define LILYGO_WATCH_2020_V1              // To use T-Watch2020 , please uncomment this line
#include <LilyGoWatch.h>

TTGOClass *ttgo;


void battery_level(int pourcent, bool chargement, int bx, int by)
{
  int tx = 25;
  int ty = 10;
  ttgo->tft->drawLine(bx, by, (bx+tx), by, TFT_WHITE);
  ttgo->tft->drawLine(bx, by, bx, (by+ty), TFT_WHITE);
  ttgo->tft->drawLine(bx, (by+ty), (bx+tx), (by+ty), TFT_WHITE);
  ttgo->tft->drawLine((bx+tx), by, (bx+tx), (by+ty), TFT_WHITE);
  ttgo->tft->drawLine((bx+tx+1), (by+2), (bx+tx+1), (by+ty-2), TFT_WHITE);
  ttgo->tft->drawLine((bx+tx+2), (by+2), (bx+tx+2), (by+ty-2), TFT_WHITE);

 if(pourcent > 80)
 {
  ttgo->tft->drawLine((bx+1), (by+1), (bx+tx), (by+1), TFT_GREEN);
  ttgo->tft->drawLine((bx+2), (by+1), (bx+tx), (by+1), TFT_GREEN);
  ttgo->tft->drawLine((bx+3), (by+1), (bx+tx), (by+1), TFT_GREEN);
  ttgo->tft->drawLine((bx+4), (by+1), (bx+tx), (by+1), TFT_GREEN);
  ttgo->tft->drawLine((bx+5), (by+1), (bx+tx), (by+1), TFT_GREEN);
 }
}
