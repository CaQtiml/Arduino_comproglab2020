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


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    int key = Serial.read();
    Serial.write(key);
    switch(key)
    {
      case 'c':
        M5.Speaker.tone(nC4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'C':
        M5.Speaker.tone(nC5);
        delay(1000);
        M5.Speaker.mute();
        break;
//================================        
      case 'd':
        M5.Speaker.tone(nD4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'D':
        M5.Speaker.tone(nD5);
        delay(1000);
        M5.Speaker.mute();
        break;
//================================         
      case 'e':
        M5.Speaker.tone(nE4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'E':
        M5.Speaker.tone(nE5);
        delay(1000);
        M5.Speaker.mute();
        break;
//================================         
      case 'f':
        M5.Speaker.tone(nF4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'F':
        M5.Speaker.tone(nF5);
        delay(1000);
        M5.Speaker.mute();
        break;
 //================================        
      case 'g':
        M5.Speaker.tone(nG4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'G':
        M5.Speaker.tone(nG5);
        delay(1000);
        M5.Speaker.mute();
        break;
 //================================        
      case 'a':
        M5.Speaker.tone(nA4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'A':
        M5.Speaker.tone(nA5);
        delay(1000);
        M5.Speaker.mute();
        break;
 //================================        
      case 'b':
        M5.Speaker.tone(nB4);
        delay(1000);
        M5.Speaker.mute();
        break;
      case 'B':
        M5.Speaker.tone(nB5);
        delay(1000);
        M5.Speaker.mute();
        break;
    }
    delay(1300);
    menu();
  }
  M5.update();
}

void menu()
{
  Serial.println("\nExercise 3\nPlease enter note [c..a,C..A]");
  Serial.print(">");
}
