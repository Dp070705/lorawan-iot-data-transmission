#include <SPI.h>
#include <LoRa.h>

#define ss 10
#define rst 9
#define dio0 2

#define trigPin 5
#define echoPin 6

void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

LoRa.setPins(ss, rst, dio0);

if (!LoRa.begin(433E6)) {
Serial.println("LoRa init failed!");
while (1);
}

Serial.println("Ultrasonic LoRa Transmitter Ready");
}

void loop() {
long duration;
float distance;

// Trigger ultrasonic pulse
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance = duration * 0.034 / 2;

Serial.print("Distance: ");
Serial.println(distance);

LoRa.beginPacket();
LoRa.print("Distance: ");
LoRa.print(distance);
LoRa.print(" cm");
LoRa.endPacket();

delay(2000);
}
