#include <Arduino.h>

#define hastighetssensor 12 //D6
#define motorPinDir 0 //D2
#define motorPinSpeed 5 //D1


unsigned long n_pulses = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
int n_turns = 0;
bool one = false;


ICACHE_RAM_ATTR void sensorCallback() {
  n_pulses++;
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    attachInterrupt(digitalPinToInterrupt(hastighetssensor), sensorCallback, RISING);


}

void loop() {
 
  if (n_pulses % 96 == 0 && one) {
    n_turns++;
    one = false;
    Serial.print(n_turns);
    Serial.print(" Since last: 0.");
    Serial.print((millis() - time1));
    Serial.print(" ms ETA: ");
    Serial.print(((millis() - time1) * (1000-n_turns))/(1000*60));
    Serial.print(" min ");
    Serial.print(((millis() - time1) * (1000-n_turns))/(1000)%60);
    Serial.println(" s");
    time1 = millis();
    }
  if (n_pulses % 96 != 0) {
    one = true;
    }

  if (n_turns >= 1000) {
    
    digitalWrite(motorPinDir, 1);
    analogWrite(motorPinSpeed, 0);
    }
   else {
    digitalWrite(motorPinDir, 1);
    analogWrite(motorPinSpeed, 512);
    }

  // put your main code here, to run repeatedly:

}