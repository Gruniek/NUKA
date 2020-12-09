#include "setup.h"
#include "test_screen.h"



void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}
