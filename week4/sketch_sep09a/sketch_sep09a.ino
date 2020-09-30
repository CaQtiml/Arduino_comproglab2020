#include <M5Stack.h>

#define B1 262
#define Cd1 277
#define D1 294
#define Dd1 311
#define E1 330
#define F1 349
#define Fd1 370
#define Gd1 415
#define A1 440
#define Ad1 466
#define H1 494
#define G_1 392

int music[] =
{
  E1,E1,E1,
  E1,E1,E1,
  E1,G_1,Cd1,D1,E1,
  F1,F1,F1,F1,
  F1,E1,E1,
  E1,D1,D1,E1,D1,
  G_1
};

int siz = sizeof(music)/sizeof(int);
int op = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin(); // don't forget this command
}

void loop() {
  // put your main code here, to run repeatedly:
  if(M5.BtnA.wasPressed())
  {
    if(op>=siz){op%=siz;}
    M5.Speaker.tone(music[op]);
  }
  if(M5.BtnA.wasReleased())
  {
    M5.Speaker.mute();
    op+=1;
  }
  M5.update();
}
