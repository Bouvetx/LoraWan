#include <TheThingsNetwork.h>
#include <CayenneLPP.h> 
// Set your AppEUI and AppKey
const char *appEui = "70B3D57ED002AB85";
const char *appKey = "2D633DC2FBF5676FB60E64F930E70735";

#define loraSerial Serial2
#define debugSerial SerialUSB

#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  ttn.onMessage(message);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  uint16_t temp = getTemperature();
  byte payload[2];
  payload[0] = highByte(temp);
  payload[1] = lowByte(temp);
  ttn.sendBytes(payload, sizeof(payload));
  // Delay between readings - 10 000 = 10 seconds
  delay(5000);
}

uint16_t getTemperature(){
  // 10mV per C, 0C is 500mV
  float mVolts = (float) analogRead(TEMP_SENSOR) * 3300.0 / 1023.0;
  int temp = (mVolts - 500) * 10;
  debugSerial.print((mVolts - 500) / 10);
  debugSerial.println(" Celcius");
  return int(temp);
}
void message(const uint8_t *payload, size_t size, port_t port){
  if (payload[0] == 0) {
    digitalWrite(LED_BUILTIN, LOW);
  }  else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
