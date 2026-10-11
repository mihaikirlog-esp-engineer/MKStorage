
#include "MKStorage.h"
#include <string.h>

MKStorage::MKStorage()
    : _ready(false), _readOnly(false) {}

bool MKStorage::begin(const char* name, bool readOnly) {
    if (_ready || name == nullptr ||
        strlen(name) == 0 || strlen(name) > 15) {
        return false;
    }

    _readOnly = readOnly;
    _ready = _prefs.begin(name, readOnly);
    return _ready;
}

void MKStorage::end() {
    if (_ready) {
        _prefs.end();
        _ready = false;
    }
}

bool MKStorage::isReady() const {
    return _ready;
}

bool MKStorage::putString(const char* key, const String& value) {
    if (!_ready || _readOnly || key == nullptr) {
        return false;
    }
    return _prefs.putString(key, value) > 0;
}

String MKStorage::getString(
    const char* key, const String& defaultValue) {
    if (!_ready || key == nullptr) return defaultValue;
    return _prefs.getString(key, defaultValue);
}

bool MKStorage::putInt(const char* key, int32_t value) {
    if (!_ready || _readOnly || key == nullptr) return false;
    return _prefs.putInt(key, value) > 0;
}

int32_t MKStorage::getInt(const char* key, int32_t defaultValue) {
    if (!_ready || key == nullptr) return defaultValue;
    return _prefs.getInt(key, defaultValue);
}

bool MKStorage::putBool(const char* key, bool value) {
    if (!_ready || _readOnly || key == nullptr) return false;
    return _prefs.putBool(key, value);
}

bool MKStorage::getBool(const char* key, bool defaultValue) {
    if (!_ready || key == nullptr) return defaultValue;
    return _prefs.getBool(key, defaultValue);
}

bool MKStorage::exists(const char* key) {
    return _ready && key != nullptr && _prefs.isKey(key);
}

bool MKStorage::remove(const char* key) {
    return _ready && !_readOnly &&
           key != nullptr && _prefs.remove(key);
}

bool MKStorage::clear() {
    return _ready && !_readOnly && _prefs.clear();
}

