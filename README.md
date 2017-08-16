# jsn-sr04t-arduino

## A simple driver to control and read data from up to 4 JSN-SR04T on Arduino.

This driver works as an abstraction layer fot the weather-proof ultrasonic sensor SKU (SEN0207).
More info [here](https://www.dfrobot.com/wiki/index.php/Weather-proof_Ultrasonic_Sensor_SKU_:_SEN0207).

### Using with Arduino
Copy both .cpp and .h files to your sketch folder. Add ```#include "jsn_sr04t.h"``` to any file which will call the driver functions, including your main .ino file. This should do it.

### Hardware configuration
Edit ```//---- Pins ----//``` section in the header file in order to match ECHO and TRIGGER pins used on your Arduino.

### Important notes
* This driver was written as part of a quick-and-drity prototyping at Bosch and it is supposed to read up to 4 sensores only. More sensors can be easily added by referring their pins in the correct section in the header file and creating additional variables and initializing routines in the source file.
* The ```init_ultrasound_sensors``` function could use an improvement. Initially I'd rather do each step at a time for one of each sensor, but code can can certainly be optimized to initialize any number of sensors without copying code around.
