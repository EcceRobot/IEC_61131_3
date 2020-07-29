#include "IEC_61131_3.h"

TON TON_1 = TON();

void setup() {
  Serial.begin(115200);
}


void loop() {

  // even if IN is high at 5000ms the output has to wait another 500ms to go high

  TON_1.execute(millis() > 5000 && millis() < 6000, 500);

  Serial.print(millis());
  Serial.print("\t\t");
  Serial.println(TON_1.Q);

}
