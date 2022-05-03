#include <Arduino.h>

/*
  BLE_Peripheral.ino

  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE
  as a peripheral device and specifies a service and a characteristic. Depending
  of the value of the specified characteristic, an on-board LED gets on.

  The circuit:
  - Arduino Nano 33 BLE.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
#include <functions.h>

const char *deviceServiceUuid = "190H";
const char *deviceServiceCharacteristicUuid = "190F";

String value;

String val = "0100,0100,0100";
unsigned long prevTime;
int advertising;

BLEService handService(deviceServiceUuid);
BLEStringCharacteristic fingerCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite | BLENotify, 14);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!BLE.begin())
  {
    Serial.println("- Starting BLE module failed!");
    while (1)
      ;
  }

  BLE.setLocalName("Arduino Handroid");
  BLE.setAdvertisedService(handService);
  handService.addCharacteristic(fingerCharacteristic);
  BLE.addService(handService);
  fingerCharacteristic.writeValue(val);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}

void loop()
{
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  // delay(500);

  if (central)
  {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    prevTime = millis();
    while (central.connected())
    {
      writeValues();
      if (fingerCharacteristic.written())
      {
        //  value = fingerCharacteristic.c);
        //  Serial.println(value);
      }
    }

    Serial.println("* Disconnected to central device!");
  }
}

void writeValues()
{
  Serial.println("---");
  fingerCharacteristic.writeValue(val);
  Serial.println("___");
  if (millis() - prevTime > 5000)
  {
    if (val == "0100,0100,0100")
    {
      val = "1000,1000,1000";
    }
    else
    {
      val = "0100,0100,0100";
    }
    prevTime = millis();
  }
}