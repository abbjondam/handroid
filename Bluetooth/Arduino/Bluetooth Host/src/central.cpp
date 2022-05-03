#include <Arduino.h>
#include <ArduinoBLE.h>
#include <functions.h>

const char *deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char *deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
BLEService handService(deviceServiceUuid);
BLECharacteristic fingerCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite | BLENotify, 14);

int gesture = -1;
int oldGestureValue = -1;
int connected = 0;
char *val = "0100,0100,0100";

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!BLE.begin())
  {
    Serial.println("* Starting BLE module failed!");
    while (1)
      ;
  }

  BLE.setLocalName("Nano 33 BLE (Central)");
  BLE.setConnectionInterval(1, 1);
  BLE.setAdvertisedService(handService);
  handService.addCharacteristic(fingerCharacteristic);
  BLE.addService(handService);
  // fingerCharacteristic.writeValue(0);

  Serial.println("Arduino Nano 33 BLE Sense (Central Device)");
  Serial.println(" ");
}

void writeValues()
{
  Serial.println("---");
  fingerCharacteristic.writeValue(val);
  Serial.println("___");
  if (val == "0100,0100,0100")
  {
    val = "1000,1000,1000";
  }
  else
  {
    val = "0100,0100,0100";
  }
  delay(5000);
}

void loop()
{
  Serial.println("---");
  while (!fingerCharacteristic.subscribed())
  {
    Serial.println("- Discovering peripheral device...");
    BLE.scanForUuid(deviceServiceUuid);

    BLE.advertise();
  }
  // Serial.println(val);
  // fingerCharacteristic.writeValue(val);
  // Serial.println("___");
  // if (val == "0100,0100,0100")
  // {
  //   val = "1000,1000,1000";
  // }
  // else
  // {
  //   val = "0100,0100,0100";
  // }
  if (!fingerCharacteristic.subscribed())
  {
    Serial.println("- Discovering peripheral device...");
    BLE.scanForUuid(deviceServiceUuid);

    BLE.advertise();
  }
  else
  {
    writeValues();
  }
}
