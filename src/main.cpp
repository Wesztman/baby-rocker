#include <Arduino.h>

int motorPin1 = 2;
int motorPin2 = 3;
int motorPwmPin = 10;

int encoderBtn = 7; // SW pin
int encoderPinA = 8; // CLK pin
int encoderPinB = 9; // DT pin
int count = 0;
int encoderPinA_prev;
int encoderPinA_value;
bool bool_CW;

void setup() {
    Serial.begin (9600);
    pinMode(encoderBtn, INPUT_PULLUP);
    pinMode (encoderPinA, INPUT);
    pinMode (encoderPinB, INPUT);
    encoderPinA_prev = digitalRead(encoderPinA);

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPwmPin, OUTPUT);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
}

void loop() {
    encoderPinA_value = digitalRead(encoderPinA);

    if (encoderPinA_value != encoderPinA_prev) {
        if (digitalRead(encoderPinB) != encoderPinA_value) {
            bool_CW = false;
            count = count - 5;
            if (count < 0) {
                count = 0;
            }
        } else {
            count = count + 5;
            if (count > 255) {
                count = 255;
            }
            bool_CW = true;
        }
        if (bool_CW) {
            Serial.print("Clockwise | ");
        } else {
            Serial.print("Counter-Clockwise | ");
        }
        Serial.print(count);
        Serial.print(" | ");
    }

    encoderPinA_prev = encoderPinA_value;

    if (digitalRead(encoderBtn) == LOW) {
        Serial.println("Button Pressed");
        count = 0;
        Serial.print("Count: ");
    }

    analogWrite(motorPwmPin, count);
}