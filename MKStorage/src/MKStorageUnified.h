
#ifndef MKSTORAGE_UNIFIED_H
#define MKSTORAGE_UNIFIED_H

#include <Arduino.h>
#include "MKStorage.h"
#include "MKStorageSD.h"

enum MKStorageBackend {
    MK_STORAGE_ESP,
    MK_STORAGE_SD
};

class MKStorageUnified {
public:
    MKStorageUnified();

    bool begin(MKStorageBackend backend,
               const char* nameSpace = "MKStorage",
               int cs = 35,
               int sck = 36,
               int miso = 37,
               int mosi = 38);

    void end();
    bool isReady() const;
    MKStorageBackend backend() const;

    bool putString(const char* key, const String& value);
    String getString(const char* key,
                     const String& defaultValue = "");

    bool exists(const char* key);
    bool remove(const char* key);

private:
    MKStorage _esp;
    MKStorageSD _sd;
    MKStorageBackend _backend;
    bool _ready;

    String makeSDPath(const char* key);
};

#endif

