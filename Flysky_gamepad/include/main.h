#pragma once
#include <Arduino.h>
#include <BleGamepad.h>
#include "freertos/semphr.h"

extern uint16_t channels[6];
extern SemaphoreHandle_t channelMutex;
extern BleGamepad bleGamepad;