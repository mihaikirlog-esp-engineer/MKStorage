
#include <MKStorageSD.h>

// Pinii sunt configurați aici, în sketch-ul ArduinoDroid.
#define SD_CS   35
#define SD_SCK  36
#define SD_MISO 37
#define SD_MOSI 38

MKStorageSD sd;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("MKSTORAGE ESP PROJECT");
    Serial.println("SD SPI test");

    // Modulul SD trebuie conectat pentru testul real.
    if (!sd.begin(SD_CS, SD_SCK, SD_MISO, SD_MOSI)) {
        Serial.println("SD not available");
        return;
    }

    Serial.println("SD mounted");

    if (sd.writeText("/mkstorage_test.txt", "MKStorage V1.0")) {
        Serial.println("Write OK");
    } else {
        Serial.println("Write failed");
    }

    Serial.println(sd.readText("/mkstorage_test.txt"));
    Serial.printf("Total: %llu bytes\n", sd.totalBytes());
    Serial.printf("Used: %llu bytes\n", sd.usedBytes());
}

void loop() {}

