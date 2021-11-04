#include "Arduino.h"

#include "board.hpp"
#include "settings.hpp"

#define SENDER
//#define RECEIVER
//#define PASSTHROUGH
#ifdef SENDER

HardwareSerial Serial2(USART2);

uint8_t input[CHANNEL_COUNT];

void setup() {
    Serial2.setRx(HC12_RX);
    Serial2.setTx(HC12_TX);
    Serial2.begin(9600);
}

void loop() {
    for (size_t i = 0; i < CHANNEL_COUNT; i += 1) {
        uint16_t val = analogRead(ANALOG_INPUTS[i]);
        // map an ADC reading to a byte.
        input[i] = map(val, 0, 1024, 0, 255);
    }
    for (size_t i = 0; i < PAYLOAD_SIZE; i += 1) { Serial2.write(input[i]); }
    Serial2.write('\n');
    delay(LOOP_DELAY_MS);
}

#elif defined(RECEIVER)

#include "Servo.h"

Servo servo[CHANNEL_COUNT] = {};

HardwareSerial Serial2(USART2);

uint8_t message[PAYLOAD_SIZE];
size_t  packet_index = 0;

void setup() {
    Serial2.setRx(HC12_RX);
    Serial2.setTx(HC12_TX);
    Serial2.begin(9600);

    for (size_t i = 0; i < CHANNEL_COUNT; i += 1) { servo[i].attach(SERVO_OUTPUTS[i]); }

    // Blue LED.
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    if (Serial2.available() > 0) {
        uint8_t incoming = Serial2.read();
        if (incoming == '\r' || incoming == '\n') {
            packet_index = 0;
        } else {
            message[packet_index % PAYLOAD_SIZE] = incoming;
            packet_index += 1;
        }
    }

    if (packet_index == PAYLOAD_SIZE) {
        packet_index = 0;
        for (size_t i = 0; i < PAYLOAD_SIZE; i += 1) {
            // map a byte to an angle.
            uint8_t angle = map(message[i], 0, 255, 0, 180);
            servo[i].write(angle);
        }
    }
}

#elif defined(PASSTHROUGH)

#include "Servo.h"

HardwareSerial Serial2(USART2);
uint8_t        input[CHANNEL_COUNT];

Servo servo[CHANNEL_COUNT] = {};

void setup() {
    Serial2.setRx(HC12_RX);
    Serial2.setTx(HC12_TX);
    Serial2.begin(9600);
    for (size_t i = 0; i < CHANNEL_COUNT; i += 1) { servo[i].attach(SERVO_OUTPUTS[i]); }

    // Blue LED.
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    for (size_t i = 0; i < CHANNEL_COUNT; i += 1) {
        uint16_t val = analogRead(ANALOG_INPUTS[i]);
        // map an ADC reading to a byte.
        input[i]      = map(val, 0, 1024, 0, 255);
        uint8_t angle = map(input[i], 0, 255, 0, 180);
        servo[i].write(angle);
    }

    delay(LOOP_DELAY_MS);
}

#endif
