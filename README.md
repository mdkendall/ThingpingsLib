# Thingpings Library for Arduino

![Lint](https://github.com/mdkendall/ThingpingsLib/actions/workflows/lint.yml/badge.svg)

A library for ESP32 projects using the Arduino framework to use the
[Thingpings](https://www.thingpings.com/) service.

Thingpings solves the problem of finding an Internet of Things device on your network after setting it up.

## Usage

```
#include <Thingpings.h>

// Connect to Wi-Fi ...

Thingpings::ping("ExampleCompany", "ExampleWidget");
```
