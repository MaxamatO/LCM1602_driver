#include "lcd1602.h"
#include "freertos/FreeRTOS.h"


#define BIT_RS (1 << 0)         // 1 = Data Register, 0 = Instruction Register
#define BIT_RW (1 << 1)         // 1 = Read, 0 = Write
#define BIT_E  (1 << 2)         // Starts data read/write

static esp_err_t lcd1602_write_byte(lcd1602_t *lcd, uint8_t *data);
static esp_err_t lcd1602_write_4bits(lcd1602_t *lcd, uint8_t *data);


static esp_err_t lcd1602_write_byte(lcd1602_t *lcd, uint8_t *data){

}

static esp_err_t lcd1602_write_4bits(lcd1602_t *lcd, uint8_t *data){
    
}

esp_err_t lcd1602_clear_display(lcd1602_t *lcd){

}