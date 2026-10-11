
#include <MKStorage.h>

MKStorage storage;

void setup() {
    Serial.begin(115200);

    if (!storage.begin("MIHAIOS")) {
        Serial.println("MKStorage: INIT FAILED");
        return;
    }

    storage.putString("theme", "MK_NEON");
    storage.putInt("brightness", 80);
    storage.putBool("enabled", true);

    Serial.println(storage.getString("theme", "DEFAULT"));
    Serial.println(storage.getInt("brightness", 50));
    Serial.println(storage.getBool("enabled", false)
                   ? "Enabled" : "Disabled");
}

void loop() {}

