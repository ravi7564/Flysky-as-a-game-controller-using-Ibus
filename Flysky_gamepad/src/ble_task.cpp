#include "ble_task.h"
#include "main.h"

int16_t processRC(uint16_t raw) {
    // Strict range 1000-2000
    if (raw < 1000) raw = 1000;
    if (raw > 2000) raw = 2000;

    // 1500 ko 0 maan kar linear scaling
    // (raw - 1500) gives -500 to 500
    // Multiply by 65.534 to get -32767 to 32767
    float result = (float)((int16_t)raw - 1500) * 65.534f;

    // Deadzone check
    if (abs(raw - 1500) < 10) return 0;

    return (int16_t)result;
}

void bleTask(void* pvParameters) {
    bleGamepad.begin();
    while (true) {
        if (bleGamepad.isConnected()) {
            uint16_t ch[6];
            if (xSemaphoreTake(channelMutex, portMAX_DELAY) == pdTRUE) {
                for (int i = 0; i < 6; i++) ch[i] = channels[i];
                xSemaphoreGive(channelMutex);
            }

            // Sirf analog data bhejein, koi Serial print nahi (Garbage rokne ke liye)
            bleGamepad.setX(processRC(ch[0]));
            bleGamepad.setY(processRC(ch[1]));
            bleGamepad.setZ(processRC(ch[2]));
            bleGamepad.setRX(processRC(ch[3]));
            bleGamepad.setSlider1(processRC(ch[4]));
            bleGamepad.setSlider2(processRC(ch[5]));
            bleGamepad.sendReport();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}