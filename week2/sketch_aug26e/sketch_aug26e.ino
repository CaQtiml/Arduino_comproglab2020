#include <M5Stack.h>


int ledPin = 21;
int ledState = LOW;

void setup() {
      M5.begin();
      Serial.begin(9600);
      pinMode(ledPin, OUTPUT);
      digitalWrite(ledPin, ledState);
      M5.update();
}
int readData=0;
void loop() {
  if (Serial.available()>0) 
  {
     readData = Serial.read();
     Serial.write(readData);
     //Serial.print("NUM:");
     //Serial.println(readData);
     if(readData<=57 && readData>=48)
     {
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
     }
     else
     {
        digitalWrite(ledPin, LOW);
     }
  }
  M5.update();
}
