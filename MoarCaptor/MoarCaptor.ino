/*
 * GY BMP 280 test sketch
 * http://satujamsaja.blogspot.co.id
 *
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// using I2C
Adafruit_BME280 bme;
#define debugSerial SerialUSB

void setup(){
  debugSerial.begin(9600);
  debugSerial.print("--------------------");
  if (!bme.begin())  {
      debugSerial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop(){
    debugSerial.print("---- GY BMP 280 ----------------");
    debugSerial.print("Temperature = ");
    debugSerial.print(bme.readTemperature());
    debugSerial.println(" *C");
    debugSerial.print("Pressure = ");
    debugSerial.print(bme.readPressure() / 100); // 100 Pa = 1 millibar
    debugSerial.println(" mb");
    debugSerial.print("Approx altitude = ");
    debugSerial.print(bme.readAltitude(1013.25));
    debugSerial.println(" m");
    debugSerial.print("--------------------------------");
    delay(2000);
}
