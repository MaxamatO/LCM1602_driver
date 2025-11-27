#include <stdio.h>
#include "esp_mac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"

#include "esp_log.h"

#include "driver/i2c_master.h"

#define I2C_MASTER_TIMEOUT_MS 		1000
#define LCD_ADDRESS					0x27

#define BACKLIGHT_ON 				0x08
#define BACKLIGHT_OFF 				0x00

#define DATA_MODE					0x01
#define COMMAND_MODE				0x00

#define BIT_RS						(1 << 0)
#define BIT_RW						(1 << 1)
#define BIT_E						(1 << 2)

static const char* TAG = "blink-led";
 
i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t lcd_dev;


static void i2c_master_init_bus(i2c_master_bus_handle_t *bus_handle){
	i2c_master_bus_config_t bus_config = {
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.glitch_ignore_cnt = 7,
		.i2c_port = I2C_NUM_0,
		.sda_io_num = GPIO_NUM_21,
		.scl_io_num = GPIO_NUM_22,
		.flags.enable_internal_pullup = true,
	};
	ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));
}
static void i2c_dev_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle, uint8_t address){
	i2c_device_config_t dev_cfg = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = address,
		.scl_speed_hz = 100000,
	};
	ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_cfg, dev_handle));
}	

// Nibble with mod already set
esp_err_t lcd1602_write_4bits(i2c_master_dev_handle_t lcd_dev, uint8_t nibble){
	uint8_t data;

	nibble = nibble | BACKLIGHT_ON;

	data = nibble | BIT_E;
	ESP_LOGI(TAG, "Nibble with BIT_E: %x\n", data);
	ESP_ERROR_CHECK(i2c_master_transmit(lcd_dev, &data, sizeof(data), -1));
	ets_delay_us(500);


	data = nibble & ~BIT_E;
	ESP_LOGI(TAG, "Nibble withOUT BIT_E: %x\n", data);
	ESP_ERROR_CHECK(i2c_master_transmit(lcd_dev, &data, sizeof(data), -1));
	ets_delay_us(300);

    return ESP_OK;
	
}

esp_err_t lcd1602_write_init(i2c_master_dev_handle_t lcd_dev, uint8_t nibble){
	uint8_t data;
	data = nibble | BIT_E;
	ESP_LOGI(TAG, "Nibble with BIT_E: %x\n", data);
	ESP_ERROR_CHECK(i2c_master_transmit(lcd_dev, &data, sizeof(data), -1));
	ets_delay_us(500);


	data = nibble & ~BIT_E;
	ESP_LOGI(TAG, "Nibble withOUT BIT_E: %x\n", data);
	ESP_ERROR_CHECK(i2c_master_transmit(lcd_dev, &data, sizeof(data), -1));
	ets_delay_us(300);

    return ESP_OK;
	
}


void lcd1602_write_8bits(i2c_master_dev_handle_t lcd_dev, uint8_t data, uint8_t mode){
	uint8_t h_nibble = (data & 0xF0) | mode;
	uint8_t l_nibble = ((data << 4) & 0xF0) | mode;
	lcd1602_write_4bits(lcd_dev, h_nibble);
	lcd1602_write_4bits(lcd_dev, l_nibble);
}


void lcd1602_write_command(i2c_master_dev_handle_t lcd_dev, uint8_t cmd){
	lcd1602_write_8bits(lcd_dev, cmd, COMMAND_MODE);
}

void lcd1602_write_data(i2c_master_dev_handle_t lcd_dev, uint8_t data){
	lcd1602_write_8bits(lcd_dev, data, DATA_MODE);
}

void app_main(void)
{
	i2c_master_init_bus(&bus_handle);
	i2c_dev_init(&bus_handle, &lcd_dev, LCD_ADDRESS);
	
	vTaskDelay(pdMS_TO_TICKS(100));
	
	lcd1602_write_init(lcd_dev, (0x03 << 4));
	vTaskDelay(pdMS_TO_TICKS(5));

	lcd1602_write_init(lcd_dev, (0x03 << 4));
	vTaskDelay(pdMS_TO_TICKS(5));

	lcd1602_write_init(lcd_dev, (0x03 << 4));
	vTaskDelay(pdMS_TO_TICKS(4.2));

	
	lcd1602_write_init(lcd_dev, 0x20);		// 4bit
	lcd1602_write_command(lcd_dev, 0x01);		// clear Display
	lcd1602_write_command(lcd_dev, 0x02);		// return home
	lcd1602_write_command(lcd_dev, 0x0C);		// return home

	lcd1602_write_data(lcd_dev, 0x6B);
	lcd1602_write_data(lcd_dev, 0x6F);
	lcd1602_write_data(lcd_dev, 0x63);
	lcd1602_write_data(lcd_dev, 0x68);
	lcd1602_write_data(lcd_dev, 0x61);
	lcd1602_write_data(lcd_dev, 0x6D);
	lcd1602_write_data(lcd_dev, 0x20);
	lcd1602_write_data(lcd_dev, 0x6F);
	lcd1602_write_data(lcd_dev, 0x6C);
	lcd1602_write_data(lcd_dev, 0x63);
	lcd1602_write_data(lcd_dev, 0x69);
	lcd1602_write_data(lcd_dev, 0x65);
	lcd1602_write_data(lcd_dev, 0x0A);


	
	//send another message
}
