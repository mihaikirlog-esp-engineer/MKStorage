
#include <MKStorageUnified.h>

// Alege backend-ul aici:
#define USE_SD_STORAGE 0

#define SD_CS   35
#define SD_SCK  36
#define SD_MISO 37
#define SD_MOSI 38

MKStorageUnified storage;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("MKSTORAGE ESP PROJECT");
    Serial.println("MKStorage 2.0.0");

#if USE_SD_STORAGE
    bool ok = storage.begin(
        MK_STORAGE_SD,
        "MKStorage",
        SD_CS, SD_SCK, SD_MISO, SD_MOSI
    );
#else
    bool ok = storage.begin(MK_STORAGE_ESP, "MKStorage");
#endif

    if (!ok) {
        Serial.println("Storage initialization failed");
        return;
    }

    Serial.println("Storage ready");

    if (storage.putString("message", "MKStorage V2.0")) {
        Serial.println("Write OK");
    } else {
        Serial.println("Write failed");
    }

    Serial.print("Read: ");
    Serial.println(storage.getString("message", "Not found"));

    Serial.print("Exists: ");
    Serial.println(storage.exists("message") ? "YES" : "NO");
}

void loop() {
}

