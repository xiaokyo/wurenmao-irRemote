#pragma GCC system_header

#define BLINKER_PRINT Serial
#define BLINKER_WIFI
// #define BLINKER_MIOT_LIGHT
#define BLINKER_MIOT_FAN

#include <Arduino.h>
#include <Blinker.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <assert.h>
#include <IRac.h>
#include <IRtext.h>