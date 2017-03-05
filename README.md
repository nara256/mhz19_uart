# MHZ19_Serial 
Arduino IDE library for operating the MH-Z19 CO2 sensor in ESP-WROOM-02(esp8266) or Arduino
version 0.1

# Credits and license
License MIT

# How to use

+ Include this library to your Arduino IDE.
+ Wireing MH-Z19 sensor to your Arduino or ESP-WROOM-02
++ MH-Z19 Vout to Arduino Vin(5V)
++ MH-Z19 GND  to Arduino GND
++ MH-Z19 Tx   to Arduino Digital Pin (Software Serial Rx pin) # do not connect Arduino Rx pin.
++ MH-Z19 Rx   to Arduino Digital Pin (Software Serial Tx pin) # do not connect Arduino Tx pin.
++ other MH-Z19 pins are not using.
+ Read sample source code. It's very simple !

* MH-Z19 is supporting  PWM , but this library is supporting only serial connection. 


# MHZ19_Serial library function

* Constractor

** MHZ19_Serial
  notmal constractor. if you use this constractor, you must begin() function after this constractor.

** MHZ19_Serial(int rx, int tx)
  setting rx and tx pin, initialize Software Serial. normally, you use this constractor.

* void begin(int rx, int tx)
  setting rx and tx pin, initialize Software Serial.
  
* void setAutoCalibration(boolean autocalib)
  MH-Z19 has automatic calibration procedure. If executing automatic calibration, its do zero point judgement
  The automatic calibration cycle is every 24 hours after powered on and 

* void calibrateZero()
  execute zero poing calibration. 
  if you want to execute zero calibration, the MH-Z19 sensor must work in stable gas environment (400ppm) for over 20 minutes and you execute this function.

* void calibrateSpan(int ppm)
  execute span point calibration.
  if you want to execute span calibration, the MH-Z19 sensor must work in between 1000 to 2000ppm level co2 for over 20 minutes and you execute this function.
  
* int getPPM();
  get co2 ppm.
  
* int getTemperature();
  get temperature (MH-Z10 hiding function?)

* int getStatus();
  get status value (but I don't know what this value is.)

* boolean isWarming();
  check ths MH-Z19 sensor is warming up.
