/*----------------------------------------------------------
    MH-Z19 CO2 sensor  Zero calibration SAMPLE
  ----------------------------------------------------------*/

#include <MHZ19_uart.h>

const int rx_pin = 16; //Serial rx pin no
const int tx_pin = 17; //Serial tx pin no

const int waitingMinutes = 30; //waiting 30 minutes

MHZ19_uart mhz19;

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
  Serial.println("MH-Z19 is warming up now.");
  delay(20 * 1000); //
  Serial.println();
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
long cnt = 0;
const long waitingSeconds = waitingMinutes * 60L;
void loop()
{
  if (++cnt % 60 == 0)
  {
    Serial.print(cnt / 60);
    Serial.println("min.");
    Serial.print("co2: ");
    Serial.print(mhz19.getCO2PPM());
    Serial.println("ppm now.");
  }
  else
  {
    Serial.print(".");
  }
  delay(1000);

  if (cnt > waitingSeconds)
  {
    Serial.println("");
    mhz19.calibrateZero();
    Serial.println("1st zero calibration now .");

    delay(60000);
    mhz19.calibrateZero(); // Just in case
    Serial.println("2nd zero calibration now .");

    for (int i = 0; i < 10; i++)
    {
      Serial.print("co2: ");
      Serial.print(mhz19.getCO2PPM());
      Serial.println("ppm now.");
      delay(10000);
    }
    cnt = 0;
    return;
  }
}
