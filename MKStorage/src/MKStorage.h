
#ifndef MKSTORAGE_H
#define MKSTORAGE_H

#include <Arduino.h>
#include <Preferences.h>

class MKStorage {
public:
    MKStorage();

    bool begin(const char* name = "MKStorage",
               bool readOnly = false);
    void end();

    bool isReady() const;

    bool putString(const char* key, const String& value);
    String getString(const char* key,
                     const String& defaultValue = "");

    bool putInt(const char* key, int32_t value);
    int32_t getInt(const char* key, int32_t defaultValue = 0);

    bool putBool(const char* key, bool value);
    bool getBool(const char* key, bool defaultValue = false);

    bool exists(const char* key);
    bool remove(const char* key);
    bool clear();

private:
    Preferences _prefs;
    bool _ready;
    bool _readOnly;
};

#endif

