#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "stdint.h"


typedef struct {
	i2c_master_dev_handle_t dev;
    uint8_t bl;
}lcd1602_t;

esp_err_t lcd1602_init(lcd1602_t *lcd);
esp_err_t lcd1602_cursor_reset(lcd1602_t *lcd);
esp_err_t lcd1602_clear_display(lcd1602_t *lcd);
