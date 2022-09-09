#include "Thingpings.h"

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP32)
    #include <WiFi.h>
    #include <WiFiClient.h>
    #include <HTTPClient.h>
#elif defined(ARDUINO_ARCH_ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266HTTPClient.h>
#endif

namespace Thingpings {

    String urlEncode(const char* s) {
        const char* hex = "0123456789ABCDEF";
        String enc = "";
        char c;
        while ((c = *s++) != '\0') {
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') enc += c;
            else {
                enc += '%';
                enc += hex[c >> 4];
                enc += hex[c & 0x0F];
            }
        }
        return enc;
    }

    void ping(const char* vendor, const char* product) {
        ping(vendor, product, "/", 80);
    }

    void ping(const char* vendor, const char* product, const char* path) {
        ping(vendor, product, path, 80);
    }

    void ping(const char* vendor, const char* product, const char* path, unsigned int port) {

        WiFiClient client;
        HTTPClient http;
        char url[256];

#if defined(ARDUINO_ARCH_ESP32)
        snprintf(url, sizeof(url), "http://www.thingpings.com/api/ping?l=%s&v=%s&p=%s&s=%012llX&t=%s&r=%u",
            WiFi.localIP().toString().c_str(),
            urlEncode(vendor).c_str(), urlEncode(product).c_str(),
            ESP.getEfuseMac(), path, port);
#elif defined(ARDUINO_ARCH_ESP8266)
        snprintf(url, sizeof(url), "http://www.thingpings.com/api/ping?l=%s&v=%s&p=%s&s=%06X&t=%s&r=%u",
            WiFi.localIP().toString().c_str(),
            urlEncode(vendor).c_str(), urlEncode(product).c_str(),
            ESP.getChipId(), path, port);
#endif
        http.begin(client, url);
        http.GET();
        http.end();
    }
}
