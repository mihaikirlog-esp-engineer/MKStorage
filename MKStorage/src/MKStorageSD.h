
#ifndef MKSTORAGE_SD_H
#define MKSTORAGE_SD_H

#include <Arduino.h>
#include <FS.h>
#include <SPI.h>
#include <SD.h>

class MKStorageSD {
public:
    MKStorageSD();

    bool begin(int cs, int sck, int miso, int mosi,
               uint32_t frequency = 4000000);
    void end();

    bool isReady() const;
    bool exists(const char* path);
    bool remove(const char* path);

    bool writeText(const char* path, const String& text);
    String readText(const char* path);

    uint64_t totalBytes();
    uint64_t usedBytes();

private:
    SPIClass _spi;
    bool _ready;
};

#endif

