#include <stdio.h>
#include "esp_mac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"

#include "esp_log.h"

#include "driver/i2c_master.h"

#include "lcd1602_drvr/lcd1602.h"

#define I2C_MASTER_TIMEOUT_MS 		1000
#define LCD_ADDRESS					0x27

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

void app_main(void)
{
	i2c_master_init_bus(&bus_handle);
	i2c_dev_init(&bus_handle, &lcd_dev, LCD_ADDRESS);
	lcd1602_t lcd = {
		.dev = lcd_dev,
		.bl = 1
	};
	lcd1602_init(&lcd);
	ESP_LOGI(TAG, "LCD Initialized");
	write_string(&lcd, "Dzien dobry");
	vTaskDelay(pdMS_TO_TICKS(5000));
	write_string(&lcd, "Dzien dobryDzien dobryDzien dobryDzien dobryDzien dobryDzien dobryDzien dobryDzien dobry");
	// while(1){
	// 	displayShiftLeft(&lcd);
	// 	vTaskDelay(pdMS_TO_TICKS(1000));
	// 	displayShiftRight(&lcd);
	// 	vTaskDelay(pdMS_TO_TICKS(1000));
	// }

}
