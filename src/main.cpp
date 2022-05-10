#include <Arduino.h>

void setup() {
// write your initialization code here
    Serial.begin(115200);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
}

void loop() {
// write your code here
    Serial.println("Loop");
//    digitalWrite(18, HIGH);
    for(uint8_t i = 0; i < 255; i++) {
        analogWrite(19, i);
        delay(8);
    }
//    delay(500);
    for(uint8_t i = 255; i > 0; i--) {
        analogWrite(19, i);
        delay(8);
    }
//    digitalWrite(18, LOW);
//    delay(500);

}