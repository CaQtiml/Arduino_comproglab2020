#include <M5Stack.h>
int show=0;
int oshow=-1;

void setup() {
  // put your setup code here, to run once:
  M5.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(M5.BtnA.wasPressed())
  {
    show+=1;
    //oshow=show;
  }
  else if(M5.BtnB.wasPressed())
  {
    if(show-1<0) show=0;
    else show-=1;
    //oshow=show;
  }
  else if(M5.BtnC.wasPressed())
  {
    show=0;
    //oshow=show;
  }
  if(oshow!=show)
  {
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(show);
    oshow=show;
  }
  M5.update();
}
