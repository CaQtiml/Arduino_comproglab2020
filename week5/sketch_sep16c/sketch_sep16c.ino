#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity/*, temperatureF*/;
float temperatureF;
int old_t = -1000,old_h=-1000,old_th=-1000;
float temp,humid;
int op = 0;
//int changeC=27, changeF=81;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(10);
}

void change()
{
  temperatureF = ((9*temperature)/5)+32;
}

void active()
{
  float cmp=0;
  if(op==0)cmp = 27;
  else if(op==1) cmp=80.6;
  if(temp>cmp)
    {
      M5.Lcd.setTextColor(0xe8e4);
    }
    else
    {
      M5.Lcd.setTextColor(0x2589);
    }
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
//    M5.Lcd.print(temperature);
//    M5.Lcd.print(" C");
    if(op==0)
    {
      M5.Lcd.print(temperature);
      M5.Lcd.print(" C");
    }
    else if(op==1)
    {
      M5.Lcd.print(temperatureF);
      M5.Lcd.print(" F");
    }
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
    change();
  }
  
  if(op==0)
  {
    if(temperature != old_t || humidity != old_h)
    {
      active();
    }
    old_t = temperature;
    old_h = humidity;
  }
  if(op==1)
  {
    if((int)temperatureF != old_t || humidity != old_h)
    {
      active();
    }
    old_t = temperatureF;
    old_h = humidity;
  }
  


//  if(op==0)
//  {
//    old_t = temperature;
//    old_h = humidity;
//  }
//  else if(op==1)
//  {
//    old_th = temperatureF;
//    old_h = humidity;
//  }

  if(M5.BtnA.wasPressed())
  {
    op = (op+1)%2;
    old_t = -1000;
    //old_th = -1000;
  }
  
  M5.update();
}
