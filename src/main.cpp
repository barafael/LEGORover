#include "Arduino.h"

#define SENDER
#ifdef SENDER

HardwareSerial Serial2(USART2);

void setup() {
    Serial1.setRx(PB7);
    Serial1.setTx(PB6);
    Serial1.begin(9600);

    Serial2.setRx(PA3);
    Serial2.setTx(PA2);
    Serial2.begin(9600);
}

void loop() {
    int value1  = analogRead(PA0);
    int value2  = analogRead(PA1);
    int mapped1 = map(value1, 0, 1024, 0, 255);
    int mapped2 = map(value2, 0, 1024, 0, 255);
    Serial2.write(mapped1);
    Serial2.write(mapped2);
    Serial2.write('\n');
    delay(50);
}

#else

#include "Servo.h"
Servo s1;
Servo s2;

HardwareSerial Serial2(USART2);

void setup() {
    Serial1.setRx(PB7);
    Serial1.setTx(PB6);
    Serial1.begin(9600);

    Serial2.setRx(PA3);
    Serial2.setTx(PA2);
    Serial2.begin(9600);

    s1.attach(PB10);
    s2.attach(PB13);

    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

#define MSG_SIZE 2
char   message[MSG_SIZE];
size_t packet_index = 0;

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
        char angle1 = map(message[0], 0, 255, 0, 180);
        char angle2 = map(message[1], 0, 255, 0, 180);
        s1.write(angle1);
        s2.write(angle2);
        Serial1.println(angle1, DEC);
        packet_index = 0;
    }
}

#endif
