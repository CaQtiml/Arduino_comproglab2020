#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity;
int old_t = -1000,old_h=-1000;
float temp,humid;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(10);
}

void active()
{
  if(temp>27)
    {
      M5.Lcd.setTextColor(0xe8e4);
    }
    else
    {
      M5.Lcd.setTextColor(0x2589);
    }
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(temperature);
    M5.Lcd.print(" C");
    M5.Lcd.setCursor(0,150);
    M5.Lcd.print(humidity);
    M5.Lcd.print("%");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int status = dht.read2(DHTPIN,&temp,&humid,NULL);
  if(status == SimpleDHTErrSuccess)
  {
    temperature = temp;
    humidity = humid;
  }
  if(temperature != old_t || humidity != old_h)
  {
    active();
  }



  old_t = temperature;
  old_h = humidity;
  M5.update();
}
