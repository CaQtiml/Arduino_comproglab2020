#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>
#define DHTPIN 5
#define TFT_GREY 0x5AEB
SimpleDHT11 dht;
int temperature, humidity/*, temperatureF*/;
float temperatureF;
int old_t = -1000,old_h=-1000,old_th=-1000;
float temp,humid;
int op = 0;

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}


uint32_t targetTime = 0;
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3); 
uint8_t ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time
byte omm = 99, oss = 99;


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(10);
  targetTime = millis() + 1000;
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

void timeactive()
{
  
}

void loop() {
  if (targetTime < millis()) {
    // Set next update for 1 second later
    targetTime = millis() + 1000;
    // Adjust the time values by adding 1 second
    ss++;              // Advance second
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }
  // put your main code here, to run repeatedly:
//============================================================================================
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
  

  if(M5.BtnA.wasPressed())
  {
    op = (op+1)%2;
    old_t = -1000;
    //old_th = -1000;
  }
  
  M5.update();
}
