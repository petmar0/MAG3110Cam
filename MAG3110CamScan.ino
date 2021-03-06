#include <Wire.h>
#include "i2c.h"

#include "i2c_MAG3110.h"
MAG3110 mag3110;
const int selectPins[4] = {2, 3, 4, 5}; // S-pins to Arduino pins: S0~2, S1~3, S2~4, S3~5

void selectMuxPin(byte pin)
{
  if (pin > 15) return; // Exit if pin is out of scope
  for (int i=0; i<4; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}


void setup()
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    Serial.print("Probe MAG3310: ");
    mag3110.initialize();
}

void loop()
{
    float xyz_uT[3];
  for(int i=0; i<16; i++){
    selectMuxPin(i);
    mag3110.initialize();
    delay(10);
    mag3110.getMeasurement(xyz_uT);
    Serial.print(millis()); Serial.print(",");
    Serial.print(i);
    Serial.print(",");
    Serial.print(xyz_uT[0],2);
    Serial.print(",");
    Serial.print(xyz_uT[1],2);
    Serial.print(",");
    Serial.print(xyz_uT[2],2);
    Serial.println();
  }
}

/**<

Program size:
A1.0.5: 7144b
A1.5.7: 6860b
A1.6.3: 6766b / 493b
 */
