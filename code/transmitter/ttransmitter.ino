#include <SPI.h>
#include <LoRa.h>

#define ss 10
#define rst 9
#define dio0 2

void setup() {
Serial.begin(9600);
while (!Serial);

LoRa.setPins(ss, rst, dio0);

if (!LoRa.begin(433E6)) {
Serial.println("LoRa init failed!");
while (1);
}

Serial.println("LoRa Transmitter Ready");
}

void loop() {
int sensorValue = analogRead(A0); // Simulated sensor

Serial.print("Sending: ");
Serial.println(sensorValue);

LoRa.beginPacket();
LoRa.print("Sensor: ");
LoRa.print(sensorValue);
LoRa.endPacket();

delay(2000);
}
