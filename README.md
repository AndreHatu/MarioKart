# Mario Kart with RC cars and ESP32s
This project aims at developing a real-life Mario Kart with RC cars and ESP32s.
The boards used utilize a single-core MCU (ESP-MINI-1 and ESP-SOLO-1). 
Schematics and wiring will be posted in the near future.

ECE477 Senior Design at Purdue University.


## How it works
We control RC cars with electronics replaced by our own ESP32. All communications are made using ESP-NOW, which is a Wi-Fi like wireless communication protocol. It enables low latency and long distance transmission of packets, with the only restriction they must be less than 250 bytes long.
Then, we place checkpoint towers and power-up blocks along the desired track and when cars run over them, a NFC tag is read and its information is sent to a central tower, which either updates records of checkpoints or determines what modifier to give the cars. Modifiers are randomly chosen using ESP's ```esp_random()``` function. Checkpoints are stored in two-dimensional arrays initialized upon race creation.


## Cloning
When cloning this repo, make sure to use ```git clone --recursive git@github.com:AndreHatu/MarioKart.git``` or run ```git submodule update --init --recursive``` after doing a standard clone. 
This ensures all dependencies are downloaded.

## Config, Build and Flash
To build, you will need to have installed Espressif's idf from their website.
Then run the following commands from a terminal.

```
idf.py set-target esp32
idf.py menuconfig
```
Inside the menuconfig, you might need to set the ```Components->freeRTOS->Run only on first core``` option in case your ESP32 only has one core (like the ones we are using for the project)
Then you can build and flash with
```
idf.py build
idf.py -p (PORT) flash
```