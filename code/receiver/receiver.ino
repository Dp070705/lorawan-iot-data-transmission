#include <SPI.h>
#include <LoRa.h>

#define ss 10
#define rst 9
#define dio0 2

void setup() {
Serial.begin(9600);

LoRa.setPins(ss, rst, dio0);

if (!LoRa.begin(433E6)) {
Serial.println("LoRa init failed!");
while (1);
}

Serial.println("LoRa Receiver Ready");
}

void loop() {
int packetSize = LoRa.parsePacket();

if (packetSize) {
Serial.print("Received: ");

```
while (LoRa.available()) {
  Serial.print((char)LoRa.read());
}

Serial.println();
```

}
}
