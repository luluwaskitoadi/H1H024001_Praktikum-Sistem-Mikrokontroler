unsigned long previousMillis1 = 0;   // waktu LED 1
unsigned long previousMillis2 = 0;   // waktu LED 2

const long interval1 = 1000;         // interval LED 1 = 1 detik
const long interval2 = 500;          // interval LED 2 = 500 ms

bool ledState1 = false;              // status LED 1
bool ledState2 = false;              // status LED 2

const int led1 = 13;                 // LED pertama
const int led2 = 12;                 // LED kedua

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {

  // Ambil waktu saat ini
  unsigned long currentMillis = millis();

  // ================= LED 1 =================
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;   // simpan waktu terakhir
    ledState1 = !ledState1;            // toggle LED
    digitalWrite(led1, ledState1);
  }

  // ================= LED 2 =================
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;   // simpan waktu terakhir
    ledState2 = !ledState2;            // toggle LED
    digitalWrite(led2, ledState2);
  }
}