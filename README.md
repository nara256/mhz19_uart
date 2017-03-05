# MHZ19_Serial 
Arduino IDE library for operating the MH-Z19 CO2 sensor in ESP-WROOM-02(esp8266) or Arduino  
version 0.2

# Credits and license  
License MIT

# How to use

* Include this library to your Arduino IDE.
* Wiring MH-Z19 sensor to your Arduino or ESP-WROOM-02.

    MH-Z19 Vout to Arduino Vin(5V)  
    MH-Z19 GND  to Arduino GND  
    MH-Z19 Tx   to Arduino Digital Pin (Software Serial Rx pin)  # do not connect Arduino Rx pin.  
    MH-Z19 Rx   to Arduino Digital Pin (Software Serial Tx pin)  # do not connect Arduino Tx pin.  
    other MH-Z19 pins are not used.  

* Read sample source code. It's very simple !

# caution

* MH-Z19 is supporting PWM , but this library is supporting only serial connection. 
* this library is testing only ESP-WROOM-02(esp8266) boards. if you can't execute this library on your arduino (or clone) boards, please contact me.


# MHZ19_Serial library function

## Constractor

* MHZ19_Serial  
  normal constractor. if you use this constractor, you must execute begin() function after this constractor execute.

* MHZ19_Serial(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.

## public function

* void begin(int rx, int tx)  
  setting rx and tx pin, and initialize Software Serial.
  
* void setAutoCalibration(bool autocalib)  
  MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
  The automatic calibration cycle is every 24 hours after powered on.  
  If you use this sensor in door, you execute `setAutoCalibration(false)`.

* void calibrateZero()  
  execute zero point calibration. 
  if you want to execute zero calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)  
  execute span point calibration.
  if you want to execute span calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.
  
* int getPPM()  
  get co2 ppm.
  
* int getTemperature()  
  get temperature (MH-Z10 hiding function?  this function is not support.)

* int getStatus()  
  get ths MH-Z19 sensor status value (but I don't know what this value is. this function is not support, too.)

* bool isWarming()  
  check the MH-Z19 sensor is warming up.

# link
* MH-Z19 Data sheet  
  http://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf

* MH-Z19B Data sheet  
  http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf

