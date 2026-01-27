#include "ibus_task.h"
#include "main.h"

void iBUS_Task(void* pvParameters) {
    uint8_t ibusBuf[32];

    while (true) {
        // Step 1: Check if enough data is in the buffer
        if (Serial2.available() >= 32) {
            // Step 2: Read first byte to check header (0x20)
            uint8_t header = Serial2.read();

            if (header == 0x20 && Serial2.peek() == 0x40) {
                ibusBuf[0] = 0x20;
                Serial2.readBytes(&ibusBuf[1], 31);

                if (xSemaphoreTake(channelMutex, 0) == pdTRUE) {
                    for (int i = 0; i < 6; i++) {
                        channels[i] = ibusBuf[2 + i * 2] | (ibusBuf[3 + i * 2] << 8);
                    }
                    xSemaphoreGive(channelMutex);
                }
            }
        }
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
}
