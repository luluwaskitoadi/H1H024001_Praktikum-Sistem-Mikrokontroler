// Variabel volatile agar dapat diubah dalam ISR
volatile bool ledState = false;

// ISR: dijalankan saat tombol dilepas (RISING edge)
void tombolInterrupt() {
  ledState = !ledState;   // Toggle status LED
}

void setup() {

  // Konfigurasi LED
  pinMode(13, OUTPUT);

  // Tombol dengan pull-up internal
  pinMode(2, INPUT_PULLUP);

  // Interrupt mode RISING
  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    RISING
  );
}

void loop() {

  // Tampilkan status LED
  digitalWrite(13, ledState);

}