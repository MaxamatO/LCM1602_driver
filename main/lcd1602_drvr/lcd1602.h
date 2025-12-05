#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "stdint.h"
#include "rom/ets_sys.h"


typedef struct {
	i2c_master_dev_handle_t dev;
    uint8_t bl;
}lcd1602_t;



// TODO: Implement constant shifting display for long sentences

void lcd1602_init(lcd1602_t *lcd);
void clearDisplay(lcd1602_t *lcd); // Clears display - puts 0x20 (space characters) into all DDRAM addresses
void returnHome(lcd1602_t *lcd); // Sets cursor or blinking to left edge; Returns display to original status if shifted.
void displayOn(lcd1602_t *lcd); // Displays back exisitng data
void displayOff(lcd1602_t *lcd); // Data still remains in DDRAM
void set_cursor(lcd1602_t *lcd, uint8_t row, uint8_t col); // TODO: Implement set_cursor
void write_string(lcd1602_t *lcd, const char *str);
void write_char(lcd1602_t *lcd, char c);
void cursorOn(lcd1602_t *lcd);
void cursorOff(lcd1602_t *lcd);
void entryModeSet(lcd1602_t *lcd);
void displayShiftLeft(lcd1602_t *lcd);
void displayShiftRight(lcd1602_t *lcd);