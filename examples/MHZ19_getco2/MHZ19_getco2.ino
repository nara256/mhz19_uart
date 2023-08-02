/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/
#include <MHZ19_uart.h>

#define rxPin 9
#define txPin 10

const int rx_pin = rxPin; //Serial rx pin no
const int tx_pin = txPin; //Serial tx pin no

MHZ19_uart mhz19;

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);

  Serial.println("MH-Z19 is warming up now.");
  delay(10 * 1000); //
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
  int co2ppm = mhz19.getCO2PPM();
  int temp = mhz19.getTemperature();

  Serial.print("co2: ");
  Serial.println(co2ppm);
  Serial.print("temp: ");
  Serial.println(temp);

  delay(5000);
}
