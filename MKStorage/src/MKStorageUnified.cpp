
#include "MKStorageUnified.h"

MKStorageUnified::MKStorageUnified()
    : _backend(MK_STORAGE_ESP), _ready(false) {}

bool MKStorageUnified::begin(
    MKStorageBackend backend,
    const char* nameSpace,
    int cs,
    int sck,
    int miso,
    int mosi
) {
    if (_ready) {
        end();
    }

    _backend = backend;

    if (_backend == MK_STORAGE_ESP) {
        _ready = _esp.begin(nameSpace, false);
    } else if (_backend == MK_STORAGE_SD) {
        _ready = _sd.begin(cs, sck, miso, mosi);
    } else {
        _ready = false;
    }

    return _ready;
}

void MKStorageUnified::end() {
    if (!_ready) {
        return;
    }

    if (_backend == MK_STORAGE_ESP) {
        _esp.end();
    } else {
        _sd.end();
    }

    _ready = false;
}

bool MKStorageUnified::isReady() const {
    return _ready;
}

MKStorageBackend MKStorageUnified::backend() const {
    return _backend;
}

String MKStorageUnified::makeSDPath(const char* key) {
    if (key == nullptr || key[0] == '\0') {
        return String();
    }

    String path = "/";
    path += key;

    if (path.indexOf("..") >= 0) {
        return String();
    }

    return path;
}

bool MKStorageUnified::putString(
    const char* key,
    const String& value
) {
    if (!_ready || key == nullptr || key[0] == '\0') {
        return false;
    }

    if (_backend == MK_STORAGE_ESP) {
        return _esp.putString(key, value);
    }

    String path = makeSDPath(key);
    return path.length() > 1 && _sd.writeText(path.c_str(), value);
}

String MKStorageUnified::getString(
    const char* key,
    const String& defaultValue
) {
    if (!_ready || key == nullptr || key[0] == '\0') {
        return defaultValue;
    }

    if (_backend == MK_STORAGE_ESP) {
        return _esp.getString(key, defaultValue);
    }

    String path = makeSDPath(key);

    if (path.length() <= 1 || !_sd.exists(path.c_str())) {
        return defaultValue;
    }

    return _sd.readText(path.c_str());
}

bool MKStorageUnified::exists(const char* key) {
    if (!_ready || key == nullptr || key[0] == '\0') {
        return false;
    }

    if (_backend == MK_STORAGE_ESP) {
        return _esp.exists(key);
    }

    String path = makeSDPath(key);
    return path.length() > 1 && _sd.exists(path.c_str());
}

bool MKStorageUnified::remove(const char* key) {
    if (!_ready || key == nullptr || key[0] == '\0') {
        return false;
    }

    if (_backend == MK_STORAGE_ESP) {
        return _esp.remove(key);
    }

    String path = makeSDPath(key);
    return path.length() > 1 && _sd.remove(path.c_str());
}

