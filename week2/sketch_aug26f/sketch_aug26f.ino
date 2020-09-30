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
     //Serial.write(readData);
     //Serial.print("NUM:");
     //Serial.println(readData);
     if(readData==49)
     {
        Serial.println("Sivakorn 6338212621");
     }
     else if(readData==50)
     {
        Serial.println("Wirachapong 63382000621");
     }
     else if(readData==51)
     {
        Serial.println("Sivakorn 6338212621");
        Serial.println("Wirachapong 63382000621");
     }
  }
  M5.update();
}
