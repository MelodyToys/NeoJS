# Getting Started

### Hardware
You'll need a ESP8266 or ESP32 microcontroller developer board or module.

### Install the Arduino Desktop IDE
To get step-by-step instructions select one of the following link accordingly to your operating system.

[Windows](https://www.arduino.cc/en/Guide/Windows)

[Mac OS X](https://www.arduino.cc/en/Guide/MacOSX)

[Linux](https://www.arduino.cc/en/Guide/Linux)

### Install ESP Arduino Core 
To get step-by-step instructions select one of the following links accordingly to your microcontroller board.

[ESP8266](https://arduino-esp8266.readthedocs.io/en/2.6.3/installing.html#instructions)

[ESP32](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

### Install Arduino spiffs filesystem uploader
You'll need to download and install the spiffs upload tool. See [here](https://github.com/esp8266/arduino-esp8266fs-plugin/blob/master/README.md) for the ESP8266. Or [here](https://github.com/me-no-dev/arduino-esp32fs-plugin) fpr the ESP32.
### Installing Additional Arduino Libraries

> ### Import using the Library Manager

Using the Library Manager 'search' and 'install' the following libraries. See [here](https://www.arduino.cc/en/Guide/Libraries) for more information.

**ArduinoJson (v5.x)** important to use version 5.x

**Adafruit_NeoPixel**

**elk**

> ### Importing a .zip Library

The next libraries can't be installed using the Library Manager and you'll have to download and install them from zip files. See [here]() for more information.

[ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip)

select one of the following links accordingly to your microcontroller board.

ESP32   - [AsyncTCP](https://github.com/me-no-dev/AsyncTCP/archive/master.zip)

ESP8266 - [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip)

### Installing NEOJS Files
Download and install the NEOJS project files. The latest release can be download from [here](https://github.com/MelodyToys/NEOJS/releases). Extract the archive into you Arduino home folder or somewhere within your local filesystem. Open NEOJS.ino file within the Arduino IDE. For more information on using the Arduino IDE can be found [here](https://www.arduino.cc/en/Tutorial/Foundations) and [here](https://www.arduino.cc/en/Guide/Environment) You'll need to change the board and board options within the IDE before uploading the firware *make sure you selected an appropriate spiffs size* Upload the Sketch using the menu (Sketch->Upload) or keyboard shortcut (Ctrl+U). After uploading the firmware you next need to upload the filesystem. Select Tools > ESP8266 Sketch Data Upload menu item. See [here](https://github.com/esp8266/arduino-esp8266fs-plugin/blob/master/README.md#usage) for more information. If eveything was successful continue on to ["Using NEOJS"](https://github.com/MelodyToys/NEOJS/blob/master/UsingNEOJS.md)





