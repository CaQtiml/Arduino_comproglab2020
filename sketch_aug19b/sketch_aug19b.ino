#include <M5Stack.h>

int i=0;
int color[] = {0x00, 0xffff} ;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setBrightness(255);
  M5.Lcd.drawCircle(160,120,100,color[1]);
  M5.Lcd.fillCircleHelper(160,120,100,1,0,color[1]);
  M5.Lcd.fillCircle(110,120,50,color[1]);
  M5.Lcd.fillCircle(210,120,50,color[0]);
  M5.Lcd.fillCircle(110,120,10,color[0]);
  M5.Lcd.fillCircle(210,120,10,color[1]);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  
}
