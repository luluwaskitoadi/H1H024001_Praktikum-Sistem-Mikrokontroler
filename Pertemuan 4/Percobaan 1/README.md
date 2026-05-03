
# Percobaan 1: Analog to Digital Converter (ADC)

## Jawaban Pertanyaan Praktikum

### Soal 1: Apa fungsi perintah analogRead() pada rangkaian praktikum ini?

`analogRead()` membaca tegangan analog pada pin A0 dari potensiometer
dan mengkonversinya menjadi nilai digital 10-bit dengan rentang 0–1023.
Nilai 0 mewakili tegangan 0V (GND) dan 1023 mewakili tegangan 5V.
Fungsi ini adalah titik masuk data dari dunia analog ke sistem digital Arduino.

---

### Soal 2: Mengapa diperlukan fungsi map() dalam program tersebut?

`analogRead()` menghasilkan rentang 0–1023 (10-bit ADC), sedangkan
`analogWrite()` hanya menerima 0–255 (8-bit PWM) dan `myservo.write()`
hanya menerima 0–180 (derajat). Kedua domain nilai ini tidak kompatibel
secara langsung. `map()` melakukan scaling linear proporsional dari satu
rentang ke rentang lain tanpa perlu perhitungan manual.

---

### Soal 3: Modifikasi program agar servo bergerak 30°–150°
Link simulasi Modifikasi: https://www.tinkercad.com/things/c31qlPVEV9C-analog-to-digital-converter-adc
<img width="1920" height="910" alt="image" src="https://github.com/user-attachments/assets/8445d470-201f-477d-941f-61240350801a" />


```cpp
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
            0,    // nilai minimum ADC
            1023,  // nilai maksimum ADC
            30,    // sudut minimum servo
            150); // sudut maksimum servo

  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(15);
}
```

#### Penjelasan Program

##### Library
`Servo.h` — library bawaan Arduino untuk mengontrol servo motor.

##### Pin Setup
- `potPin = A0` — pin pembacaan tegangan analog potensiometer
- `servoPin = 9` — pin PWM output ke servo

##### Variabel
- `val` — menyimpan hasil analogRead (0–1023)
- `pos` — menyimpan sudut hasil konversi (30–150)

##### setup()
- `myservo.attach(servoPin)` — menghubungkan objek servo ke pin 9
- `Serial.begin(9600)` — membuka komunikasi serial 9600 baud

##### loop()
1. `analogRead(potPin)` membaca nilai ADC dari potensiometer
2. `map(val, 0, 1023, 30, 150)` mengkonversi rentang ADC penuh
   ke rentang sudut terbatas 30°–150°
3. `myservo.write(pos)` menggerakkan servo ke sudut hasil konversi
4. `Serial.print` menampilkan nilai ADC dan sudut ke Serial Monitor
5. `delay(15)` memberi waktu servo untuk mencapai posisi target
