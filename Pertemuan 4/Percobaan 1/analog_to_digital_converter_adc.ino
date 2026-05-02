#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int pos = 0;
int val = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // Baca ADC 10-bit lalu geser kanan 2 bit → 8-bit (0–255)
  val = analogRead(potensioPin) >> 2;

  // Map 8-bit (0–255) ke sudut servo (0–180)
  pos = map(val,
            0,    // nilai minimum ADC 8-bit
            255,  // nilai maksimum ADC 8-bit
            0,    // sudut minimum servo
            180); // sudut maksimum servo

  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(15);
}