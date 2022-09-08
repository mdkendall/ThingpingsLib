#include "Thingpings.h"

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

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

        HTTPClient http;
        char url[256];

        uint64_t chipid = ESP.getEfuseMac();

        snprintf(url, sizeof(url), "http://www.thingpings.com/api/ping?l=%s&v=%s&p=%s&s=%04X%08X&t=%s&r=%u",
            WiFi.localIP().toString().c_str(),
            urlEncode(vendor).c_str(), urlEncode(product).c_str(),
            (uint16_t)(chipid>>32), (uint32_t)chipid,
            path, port);

        http.begin(url);
        http.GET();
        http.end();
    }
}
