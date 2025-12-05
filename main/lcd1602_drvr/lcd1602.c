#include "lcd1602.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// General bit definitions
#define ENABLE          0x04    // BIT_E

#define COMMAND_MODE    0x00    // RS = 0
#define DATA_MODE       0x01    // RS = 1

#define WRITE_MODE      0x00    // RW = 0
#define READ_MODE       0x02    // RW = 1

#define BACKLIGHT_ON    0x08    // xxxx 1100 | COMM
#define BACKLIGHT_OFF   0x00

// Commands for function use
#define DISPLAY_ON      0x0C    
#define DISPLAY_OFF     0x08
#define CLEAR_DISPLAY   0x01
#define RETURN_HOME     0x02
#define CURSOR_ON       0x0B // 00001011
#define CURSOR_OFF      0x09
//#define ENTRY_MODE_SET  0x06
#define ENTRY_MODE_SET  0x07
#define DISPLAY_CRUSOR  0x0E
#define SHIFT_DISPLAY_R 0x1C
#define SHIFT_DISPLAY_L 0x18
#define SHIFT_CURSOR_R  0x14
#define SHIFT_CURSOR_L  0x10

static void lcd1602_write_byte(lcd1602_t *lcd, uint8_t data, uint8_t mode);
static void lcd1602_write_nibble(lcd1602_t *lcd, uint8_t nibble);
static void lcd1602_write_command(lcd1602_t *lcd, uint8_t cmd);
static void lcd1602_write_data(lcd1602_t *lcd, uint8_t data);
// Initialization sequence for LCD1602 in 4-bit mode
// According to the datasheet, we need to follow a specific sequence
void lcd1602_init(lcd1602_t *lcd){
    lcd->bl = BACKLIGHT_OFF; // Disable backlight during init to not messup init sequence
	vTaskDelay(pdMS_TO_TICKS(50)); // Wait for more than 40ms after VCC rises to 2.7V

    // Steps from documentation - 3 times 0x03
    lcd1602_write_nibble(lcd, (0x03 << 4));
    ets_delay_us(4200);

	lcd1602_write_nibble(lcd, (0x03 << 4));
    ets_delay_us(4200);

    lcd1602_write_nibble(lcd, (0x03 << 4));
    ets_delay_us(110);

    lcd1602_write_nibble(lcd, 0x20);		// 4bit
    clearDisplay(lcd);
    returnHome(lcd);
	lcd1602_write_command(lcd, 0x0C);		// return home
    lcd->bl = BACKLIGHT_ON; // Enable backlight after init
}

void clearDisplay(lcd1602_t *lcd){
    lcd1602_write_command(lcd, CLEAR_DISPLAY);
    ets_delay_us(3000);
}

void returnHome(lcd1602_t *lcd){
    lcd1602_write_command(lcd, RETURN_HOME); 
    ets_delay_us(3000);
}

void displayOn(lcd1602_t *lcd){
    lcd1602_write_command(lcd, DISPLAY_ON);
}

void displayOff(lcd1602_t *lcd){
    lcd1602_write_command(lcd, DISPLAY_OFF);
}

void cursorOn(lcd1602_t *lcd){
    lcd1602_write_command(lcd, CURSOR_ON);
}

void cursorOff(lcd1602_t *lcd){
    lcd1602_write_command(lcd, CURSOR_OFF);
}

void entryModeSet(lcd1602_t *lcd){
    lcd1602_write_command(lcd, ENTRY_MODE_SET);
}

void write_char(lcd1602_t *lcd, char c){
    lcd1602_write_data(lcd, (uint8_t)c);
}

void write_string(lcd1602_t *lcd, const char *str){
    while(*str){
        write_char(lcd, *str);
        str++;
    }
}

void displayShiftLeft(lcd1602_t *lcd){
    lcd1602_write_command(lcd, SHIFT_DISPLAY_L);        
}

void displayShiftRight(lcd1602_t *lcd){
    lcd1602_write_command(lcd, SHIFT_DISPLAY_R);        
}

static void lcd1602_write_byte(lcd1602_t *lcd, uint8_t data, uint8_t mode){
    uint8_t h_nibble = (data & 0xF0) | mode; // 
	uint8_t l_nibble = ((data << 4) & 0xF0) | mode;
	lcd1602_write_nibble(lcd, h_nibble);
	lcd1602_write_nibble(lcd, l_nibble);
}

static void lcd1602_write_nibble(lcd1602_t *lcd, uint8_t nibble){
    uint8_t data;

	nibble = nibble | lcd->bl;

	data = nibble | ENABLE;
	i2c_master_transmit(lcd->dev, &data, sizeof(data), -1);
	ets_delay_us(20);


	data = nibble & ~ENABLE;
	i2c_master_transmit(lcd->dev, &data, sizeof(data), -1);
	ets_delay_us(300);
}

static void lcd1602_write_command(lcd1602_t *lcd, uint8_t cmd){
    lcd1602_write_byte(lcd, cmd, COMMAND_MODE);
}

static void lcd1602_write_data(lcd1602_t *lcd, uint8_t data){
    lcd1602_write_byte(lcd, data, DATA_MODE);
}