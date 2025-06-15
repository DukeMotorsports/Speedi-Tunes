/* 
  ******************** CAN TASK FILE ********************

  - Please for all functions related to twai/CAN

 */

// Variables
  static const twai_filter_config_t   f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();   // We can filter our CAN reception to specific addresses only (later)
  static const twai_timing_config_t   t_config = TWAI_TIMING_CONFIG_1MBITS();       // CAN SPEED (must change to 1000Kbits to work with our MoTeC System)         SPEED... I AM SPEED
  static const twai_general_config_t  g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_GPIO_NUM, (gpio_num_t)RX_GPIO_NUM, TWAI_MODE_NO_ACK);
  static SemaphoreHandle_t tx_sem;
  
  twai_message_t message;         // CAN Message  LL;L;;;/Struct    


// Functions

static void twai_transmit_task(void *arg) {
    xSemaphoreTake(tx_sem, portMAX_DELAY);
    ESP_LOGI(BASE_TAG, "Transmit Thread Started");

    while(1) {
        digitalWrite(LED_BUILTIN, HIGH);

        // Check CAN state before transmitting
        twai_status_info_t status;
        twai_get_status_info(&status);

        // Handle BUS_OFF state (state 2)
        if (status.state == TWAI_STATE_BUS_OFF) {
            ESP_LOGE(BASE_TAG, "BUS OFF detected! Attempting recovery...");
            Serial.println("CAN BUS OFF - Attempting recovery");
            
            // 1. Stop the controller
            twai_stop();
            vTaskDelay(pdMS_TO_TICKS(100));
            
            // 2. Reset error counters
            twai_initiate_recovery();
            vTaskDelay(pdMS_TO_TICKS(100));
            
            // 3. Restart the controller
            esp_err_t restart_err = twai_start();
            if (restart_err != ESP_OK) {
                ESP_LOGE(BASE_TAG, "Restart failed: %s", esp_err_to_name(restart_err));
                Serial.printf("CAN restart failed: %s\n", esp_err_to_name(restart_err));
            } else {
                ESP_LOGI(BASE_TAG, "CAN controller restarted successfully");
                Serial.println("CAN controller restarted");
            }
            
            vTaskDelay(pdMS_TO_TICKS(100));
            // continue;
        }

        // Only proceed if bus is running
        if (status.state == TWAI_STATE_RUNNING) {
            twai_message_t message1 = {
                .identifier = 0x661, 
                .data_length_code = 8,
                .data = {
                    button_status, 
                    modes_status,
                    screen_btns,
                    pot_v_h, 
                    pot_v_l, 
                    0,
                    0,
                    0
                } 
            };

            // [Your existing serial print code here...]

            esp_err_t transmit_err = twai_transmit(&message1, pdMS_TO_TICKS(10));
            if (transmit_err != ESP_OK) {
                ESP_LOGE(BASE_TAG, "Transmit failed: %s", esp_err_to_name(transmit_err));
                Serial.printf("Transmit error: %s\n", esp_err_to_name(transmit_err));
            }
        } else {
            ESP_LOGW(BASE_TAG, "CAN not ready, state: %d", status.state);
            Serial.printf("CAN state: %d\n", status.state);
        }

        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(10));    // Send updates @ 100 Hz
    }

    xSemaphoreGive(tx_sem);
    vTaskDelete(NULL);
}