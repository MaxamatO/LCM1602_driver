#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "stdint.h"
#include "rom/ets_sys.h"



typedef struct {
	i2c_master_dev_handle_t dev;
    uint8_t bl;
}lcd1602_t;

void lcd1602_init(lcd1602_t *lcd);
void clearDisplay(lcd1602_t *lcd);
void returnHome(lcd1602_t *lcd);
void displayOn(lcd1602_t *lcd);
void displayOff(lcd1602_t *lcd);
void set_cursor(lcd1602_t *lcd, uint8_t row, uint8_t col);
void write_string(lcd1602_t *lcd, const char *str);
void write_char(lcd1602_t *lcd, char c);
void cursorOn(lcd1602_t *lcd);
void cursorOff(lcd1602_t *lcd);
void entryModeSet(lcd1602_t *lcd);
