idf_component_register(SRCS "blink-led.c" "lcd1602_drvr/lcd1602.c"
                    INCLUDE_DIRS "." "lcd1602_drvr"
                    REQUIRES esp_driver_i2c freertos)
