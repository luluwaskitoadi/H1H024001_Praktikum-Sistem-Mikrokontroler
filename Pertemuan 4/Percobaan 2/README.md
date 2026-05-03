# Percoaan 2: Pulse Width Modulation (PWM)

## Jawaban Pertanyaan Praktikum

### Soal 1: Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!

`analogWrite()` menghasilkan sinyal PWM (Pulse Width Modulation) pada pin
digital. PWM bekerja dengan menyalakan dan mematikan tegangan secara sangat
cepat (frekuensi ~490Hz pada Arduino Uno). Persentase waktu sinyal HIGH
dalam satu siklus disebut duty cycle. Nilai 0 berarti sinyal selalu LOW
(LED mati), nilai 255 berarti sinyal selalu HIGH (LED penuh), dan nilai
di antaranya menghasilkan rata-rata tegangan yang lebih rendah sehingga
LED tampak lebih redup. Mata manusia tidak mampu mendeteksi kedipan pada
frekuensi tersebut sehingga LED terlihat menyala dengan kecerahan bervariasi.

---

### Soal 2: Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

ADC menghasilkan resolusi 10-bit (2^10 = 1024 langkah, rentang 0–1023).
PWM `analogWrite()` menerima resolusi 8-bit (2^8 = 256 langkah, rentang 0–255).
Keduanya dihubungkan secara linear menggunakan `map()`:

```
PWM = (ADC / 1023) × 255
```

Setiap kenaikan ADC sebesar 4 kira-kira setara dengan kenaikan PWM sebesar 1.
Fungsi `map(nilaiADC, 0, 1023, 0, 255)` melakukan konversi ini secara otomatis
dengan scaling proporsional linear.

---

### Soal 3: Modifikasi program agar LED hanya menyala pada rentang PWM 50–200
Link simulasi Modifikasi: https://www.tinkercad.com/things/bNjO7M68HYG-pulse-width-modulation-pwm
<img width="1920" height="907" alt="image" src="https://github.com/user-attachments/assets/f664dc2c-3d32-4e86-bee1-23f74b4b961a" />


```cpp
const int potPin = A0;
const int ledPin = 9;

int nilaiADC = 0;
int pwm = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  nilaiADC = analogRead(potPin);

  pwm = map(nilaiADC,
            0,    // minimum ADC
            1023, // maksimum ADC
            50,    // PWM minimum
            200); // PWM maksimum

  analogWrite(ledPin, pwm);

  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}
```

#### Penjelasan Program

##### Library
`Arduino.h` — library dasar Arduino, menyertakan semua fungsi inti
seperti `analogRead()`, `analogWrite()`, `pinMode()`, dan `Serial`.

##### Pin Setup
- `potPin = A0` — pin pembacaan tegangan analog potensiometer
- `ledPin = 9` — pin PWM output ke LED pertama
- `ledPin2 = 10` — pin PWM output ke LED kedua

##### Variabel
- `nilaiADC` — menyimpan hasil analogRead (0–1023)
- `pwm` — menyimpan hasil konversi map (0–255)

##### setup()
- `pinMode(ledPin, OUTPUT)` — menetapkan pin 9 sebagai output
- `pinMode(ledPin2, OUTPUT)` — menetapkan pin 10 sebagai output
- `Serial.begin(9600)` — membuka komunikasi serial 9600 baud

##### loop()
1. `analogRead(potPin)` membaca nilai ADC dari potensiometer (0–1023)
2. `map(nilaiADC, 0, 1023, 0, 255)` mengkonversi ADC ke rentang PWM
3. Blok `if` memeriksa apakah pwm berada dalam rentang 50–200
4. Jika ya, `analogWrite()` mengirim nilai pwm ke kedua LED
5. Jika tidak, `analogWrite()` mengirim nilai 0 (LED mati)
6. `Serial.print` menampilkan ADC, PWM, dan status ke Serial Monitor
7. `delay(50)` menstabilkan pembacaan dan tampilan serial
