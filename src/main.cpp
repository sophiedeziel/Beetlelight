#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("hello world!");

  delay(3000);
}