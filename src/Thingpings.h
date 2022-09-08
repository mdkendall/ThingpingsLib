#ifndef THINGPINGS_H
#define THINGPINGS_H

namespace Thingpings {

    void ping(const char* vendor, const char* product);
    void ping(const char* vendor, const char* product, const char* path);
    void ping(const char* vendor, const char* product, const char* path, unsigned int port);
}

#endif
