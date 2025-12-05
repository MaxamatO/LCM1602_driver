# LCD1602 / HD44780 I²C Driver for ESP32

Sterownik do obsługi wyświetlaczy **LCD1602 / HD44780** poprzez magistralę **I²C**, wykorzystujący API **ESP-IDF** (`i2c_master_bus`, `i2c_master_device`).  
Sterownik działa w trybie 4-bitowym zgodnie z dokumentacją HD44780.
---

## ✨ Funkcje
- pełna obsługa LCD w trybie 4-bitowym  
- kompatybilny z HD44780  
- konfiguracja HD44780 zgodna z dokumentacją  
- obsługa:
  - wyświetlania tekstu i pojedynczych znaków
  - czyszczenia ekranu i powrotu kursora
  - włączania / wyłączania wyświetlacza
  - sterowania podświetleniem
  - „entry mode set”

Sterownik działa wyłącznie na API ESP-IDF, bez zewnętrznych bibliotek.

---

