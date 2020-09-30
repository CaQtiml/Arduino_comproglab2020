#include <M5Stack.h>

const int nC4 = 262; //C
const int nD4 = 294; 
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;

const int nC5 = nC4*2; // nC5 = 2(nC4)
const int nD5 = nD4*2;
const int nE5 = nE4*2;
const int nF5 = nF4*2;
const int nG5 = nG4*2;
const int nA5 = nA4*2;
const int nB5 = nB4*2;

int op = 0;

const int note[] = {nE4,nE4,nE4,nE4,nE4,nE4,nE4,nG4,nC4,nD4,nE4,nF4,nF4,nF4,nF4,nF4,nE4,nE4,nE4,nD4,nD4,nE4,nD4,nG4};
int siz = 24;
int spd = 1000;


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  //M5.update();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(op>=24) {op%=24;}
  action();
  delay(spd);
  action();
  M5.Speaker.tone(note[op]);
  action();
  delay(spd);
  action();
  M5.Speaker.mute();
  op++;

  M5.update();
}
void action()
{
  if(M5.BtnB.wasPressed())
  {
    spd*=2;
    M5.update();
  }
  if(M5.BtnA.wasPressed())
  {
    spd/=2;
    M5.update();
  }
  if(M5.BtnC.wasPressed())
  {
    spd=1000;
    M5.update();
  }
}
