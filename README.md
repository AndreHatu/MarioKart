# Mario Kart with RC cars and ESP32s
This project aims at developing a real-life Mario Kart with RC cars and ESP32s.
The boards used utilize a single-core MCU (ESP-MINI-1 and ESP-SOLO-1). 
Schematics and wiring will be posted in the near future.

ECE477 Senior Design at Purdue University.


## Config, Build and Flash
To build, you will need to have installed Espressif's idf from their website.
Then run the following commands from a terminal.

```
idf.py set-target esp32
idf.py menuconfig
idf.py build
idf.py -p (PORT) flash
```