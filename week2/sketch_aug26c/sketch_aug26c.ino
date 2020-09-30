#include <M5Stack.h>

int count=0;
void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println(" ");
  M5.update();
}

void loop() {
  //Serial.print("The button is ");
  if (M5.BtnA.wasPressed()) {
    count= count+1;
    Serial.print("click: ");
    Serial.println(count);
  } 
  M5.update();
}
