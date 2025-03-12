#include <DS3231.h>

byte   Hour, Minute, Second;

void setup() {
  DS3231.begin();
  Serial.begin(9600);
}

void loop() {
  DS3231.Get_Time(&Hour, &Minute, &Second);

  Serial.print(" Time : ");
  Serial.print(Hour);
  Serial.print("\0\0");                   // for Space
  Serial.print(Minute);
  Serial.print("\0\0");
  Serial.println(Second);

  delay(1000);
}
