int TFT_BL = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 1);
  delay(1000);
  digitalWrite(TFT_BL, 0);
  delay(1000);
  
  digitalWrite(TFT_BL, 1);
  delay(1000);
  
  digitalWrite(TFT_BL, 0);
  delay(1000);
  
  digitalWrite(TFT_BL, 1);
  delay(1000);
  
  digitalWrite(TFT_BL, 0);
  delay(1000);
  

  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
