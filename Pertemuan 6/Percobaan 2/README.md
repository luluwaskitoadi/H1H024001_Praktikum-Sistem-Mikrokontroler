# Percobaan 2 : Timer dengan `millis()`

### 1. Jelaskan bagaimana fungsi `millis()` bekerja pada program tersebut!

Fungsi `millis()` mengembalikan jumlah milidetik sejak Arduino pertama kali dinyalakan. Perhitungan waktu ini dilakukan oleh **Timer0** internal ATmega328P yang berjalan di *background* secara otomatis.

**Cara kerjanya dalam program:**
Pada setiap iterasi di dalam fungsi `loop()`, nilai waktu saat ini diambil dan disimpan dalam variabel `currentMillis` menggunakan perintah `millis()`. Kemudian, program menghitung selisih waktu dengan operasi `currentMillis - previousMillis` untuk mengetahui berapa lama waktu yang sudah berlalu sejak terakhir kali status LED berubah. Jika selisih waktu tersebut sudah mencapai atau melebihi batas yang ditentukan (misalnya `1000ms`), maka status LED akan di-*toggle* (diubah), dan nilai `previousMillis` akan diperbarui ke waktu saat ini sebagai titik referensi baru. Proses ini berulang terus-menerus, menghasilkan efek LED berkedip setiap 1 detik.

### 2. Apa perbedaan utama antara `delay()` dan `millis()`?

* **`delay()` (Sifat: *Blocking*):** Perintah seperti `delay(1000)` akan **menghentikan seluruh eksekusi program** selama 1000ms. Selama periode jeda tersebut, CPU benar-benar tertahan dan tidak dapat menjalankan instruksi baris kode lain sama sekali.
* **`millis()` (Sifat: *Non-Blocking*):** Fungsi ini **tidak menghentikan program**. Ia hanya mencatat dan membandingkan waktu secara *real-time*. Selama menunggu interval 1000ms tercapai, CPU tetap bebas mengeksekusi instruksi atau kode lain yang berada di dalam `loop()`.

### 3. Mengapa metode `millis()` disebut *non-blocking*?

Metode `millis()` disebut *non-blocking* karena **tidak ada instruksi yang menahan atau memblokir eksekusi CPU** di satu titik tertentu.

Program akan terus bergerak maju melewati blok kondisi `if` (pengecekan interval), terlepas dari apakah kondisi waktunya sudah terpenuhi atau belum. CPU tidak perlu "menunggu" diam di tempat; ia akan terus mengeksekusi baris kode berikutnya, kembali ke awal `loop()`, dan mengecek kondisi lagi pada iterasi selanjutnya. Hal ini membuat sistem tetap responsif terhadap *input* lain atau *task* lain yang berada di dalam `loop()` selama masa tunggu interval tersebut.

### 4. Modifikasi dua LED dengan interval berbeda

* `previousMillis1` dengan `interval1 = 1000` untuk **LED 1** (di Pin 13).
* `previousMillis2` dengan `interval2 = 500` untuk **LED 2** (di Pin 12).

**Analisis Hasil:**
Satu nilai `currentMillis` diambil sekali pada setiap iterasi `loop()` dan digunakan untuk mengecek kedua kondisi secara terpisah. Karena kedua blok `if` berjalan dalam `loop()` yang sama tanpa menggunakan fungsi `delay()`, kedua LED dapat berkedip dengan frekuensinya masing-masing secara independen dan bersamaan — LED 1 berkedip setiap 1 detik dan LED 2 berkedip setiap 500ms — tanpa saling menghambat satu sama lain.

#### Kode Program

```cpp
// Deklarasi Pin
const int led1Pin = 13;
const int led2Pin = 12;

// Variabel penyimpan waktu terakhir LED berubah
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

// Variabel interval waktu berkedip (dalam milidetik)
const long interval1 = 1000; // Interval LED 1 (1 detik)
const long interval2 = 500;  // Interval LED 2 (0.5 detik)

// Status LED saat ini
int led1State = LOW;
int led2State = LOW;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  // Catat waktu saat ini
  unsigned long currentMillis = millis();

  // ----- Kontrol LED 1 -----
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis; // Update waktu referensi
    
    // Toggle status LED 1
    if (led1State == LOW) {
      led1State = HIGH;
    } else {
      led1State = LOW;
    }
    digitalWrite(led1Pin, led1State);
  }

  // ----- Kontrol LED 2 -----
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis; // Update waktu referensi
    
    // Toggle status LED 2
    if (led2State == LOW) {
      led2State = HIGH;
    } else {
      led2State = LOW;
    }
    digitalWrite(led2Pin, led2State);
  }
}

```
