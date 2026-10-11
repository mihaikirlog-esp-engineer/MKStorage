
#include "MKStorageSD.h"

MKStorageSD::MKStorageSD()
    : _spi(FSPI), _ready(false) {}

bool MKStorageSD::begin(int cs, int sck, int miso, int mosi,
                        uint32_t frequency) {
    if (_ready) return true;

    _spi.begin(sck, miso, mosi, cs);

    if (!SD.begin(cs, _spi, frequency)) {
        _spi.end();
        return false;
    }

    _ready = true;
    return true;
}

void MKStorageSD::end() {
    if (_ready) {
        SD.end();
        _spi.end();
        _ready = false;
    }
}

bool MKStorageSD::isReady() const {
    return _ready;
}

bool MKStorageSD::exists(const char* path) {
    return _ready && path && SD.exists(path);
}

bool MKStorageSD::remove(const char* path) {
    return _ready && path && SD.remove(path);
}

bool MKStorageSD::writeText(const char* path, const String& text) {
    if (!_ready || !path) return false;

    File file = SD.open(path, FILE_WRITE);
    if (!file) return false;

    size_t written = file.print(text);
    file.close();

    return written == text.length();
}

String MKStorageSD::readText(const char* path) {
    if (!_ready || !path) return String();

    File file = SD.open(path, FILE_READ);
    if (!file) return String();

    String result;
    while (file.available()) {
        result += (char)file.read();
    }

    file.close();
    return result;
}

uint64_t MKStorageSD::totalBytes() {
    return _ready ? SD.totalBytes() : 0;
}

uint64_t MKStorageSD::usedBytes() {
    return _ready ? SD.usedBytes() : 0;
}

