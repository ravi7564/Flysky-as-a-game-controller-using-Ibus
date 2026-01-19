#include "main.h"
#include "ibus_task.h"
#include "ble_task.h"

// Initialize 6 channels at neutral (1500)
uint16_t channels[6] = {1500, 1500, 1500, 1500, 1500, 1500};
SemaphoreHandle_t channelMutex;
BleGamepad bleGamepad("FlySky 6CH Analog", "ESP32", 100);

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n--- ESP32 GAMEPAD TEST START ---");
    channelMutex = xSemaphoreCreateMutex();

    // iBUS Serial2 initialization (RX on Pin 16)
    Serial2.begin(115200, SERIAL_8N1, 16, -1);

    xTaskCreate(iBUS_Task, "iBUS_Task", 4096, NULL, 2, NULL);
    xTaskCreate(bleTask, "bleTask", 4096, NULL, 1, NULL);
}

void loop() {
    delay(1000);
}