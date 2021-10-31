#include "Arduino.h"

#include "settings.hpp"

#define SENDER
#ifdef SENDER

HardwareSerial Serial2(USART2);

char input[INPUT_NUM];

void setup() {
    Serial1.setRx(PB7);
    Serial1.setTx(PB6);
    Serial1.begin(9600);

    Serial2.setRx(PA3);
    Serial2.setTx(PA2);
    Serial2.begin(9600);
}

void loop() {
    uint16_t tmp[MAX_JOYSTICK_INPUTS];
    for (size_t i = 0; i < INPUT_NUM; i += 1) {
        uint16_t val = analogRead(input_pin[i]);
        input[i]     = map(val, 0, 1024, 0, 255);
    }
    for (size_t i = 0; i < MSG_SIZE; i += 1) { Serial2.write(input[i]); }
    Serial2.write('\n');
    delay(50);
}

#else

#include "Servo.h"

Servo servo[MAX_SERVO_CHANNELS] = {};

HardwareSerial Serial2(USART2);

char   message[MSG_SIZE];
size_t packet_index = 0;

void setup() {
    Serial1.setRx(PB7);
    Serial1.setTx(PB6);
    Serial1.begin(9600);

    Serial2.setRx(PA3);
    Serial2.setTx(PA2);
    Serial2.begin(9600);

    servo[0].attach(PB10);
    servo[1].attach(PB13);
    servo[2].attach(PB14);
    servo[3].attach(PB15);

    // Blue LED.
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    if (Serial2.available() > 0) {
        char incoming = Serial2.read();
        if (incoming == '\r' || incoming == '\n') {
            packet_index = 0;
        } else {
            message[packet_index % MSG_SIZE] = incoming;
            packet_index += 1;
        }
    }

    if (packet_index == MSG_SIZE) {
        for (size_t i = 0; i < MSG_SIZE; i += 1) {
            char angle = map(message[i], 0, 255, 0, 180);
            servo[i].write(angle);
        }
        packet_index = 0;
    }
}

#endif
