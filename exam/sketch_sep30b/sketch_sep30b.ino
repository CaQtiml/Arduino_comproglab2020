#include <M5Stack.h>

void smile()
{
  M5.Lcd.fillScreen(0);
  M5.Lcd.drawCircle(160,120,90,0xFFFF);
  M5.Lcd.drawCircleHelper(160,145,50,12,0xFFFF);
  M5.Lcd.fillCircle(130,90,20,0xFFFF);
  M5.Lcd.fillCircle(190,90,20,0xFFFF);
}
void bad()
{
  M5.Lcd.fillScreen(0);
  M5.Lcd.drawCircle(160,120,90,0xFFFF);
  M5.Lcd.drawCircleHelper(160,180,50,3,0xFFFF); //3,4
  M5.Lcd.fillCircle(130,90,20,0xFFFF);
  M5.Lcd.fillCircle(190,90,20,0xFFFF);
}
void neutral()
{
  M5.Lcd.fillScreen(0);
  M5.Lcd.drawCircle(160,120,90,0xFFFF);
  M5.Lcd.drawLine(120,150,210,150,0xFFFF);
  M5.Lcd.fillCircle(130,90,20,0xFFFF);
  M5.Lcd.fillCircle(190,90,20,0xFFFF);
}
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
  Serial.println("");
  //smile();
  //bad();
  M5.update();
}


void loop() {
  //bad();
//  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    
    int readData = Serial.read();
    //M5.Lcd.print(readData);
    Serial.write(readData);
    if(readData>=48 && readData<=57)
    {
      bad();
    }
    else if(readData>=65 && readData<=90)
    {
      smile();
    }
    else
    {
      neutral();
    }
  }
  M5.update();
}
