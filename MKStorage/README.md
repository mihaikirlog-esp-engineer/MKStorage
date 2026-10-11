
# MKStorage

A simple persistent key-value storage library for ESP32.

## Features

- Store and retrieve strings, integers and booleans.
- Check whether a key exists.
- Remove individual keys or clear a namespace.
- Read-only mode.
- Built on the ESP32 Preferences API.

## Requirements

- Arduino framework for ESP32
- ESP32 Preferences library

## Basic usage

```cpp
#include <MKStorage.h>

MKStorage storage;

void setup() {
  Serial.begin(115200);

  if (!storage.begin("MIHAIOS")) {
    Serial.println("MKStorage initialization failed");
    return;
  }

  storage.putString("theme", "MK_NEON");
  storage.putInt("brightness", 80);

  Serial.println(storage.getString("theme", "DEFAULT"));
  Serial.println(storage.getInt("brightness", 50));
}

void loop() {}
```

## Limitations

MKStorage 0.1.0 stores small key-value settings through Preferences.
It is not a general-purpose file system.

## License

Apache-2.0

