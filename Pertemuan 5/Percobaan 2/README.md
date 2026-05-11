# Percobaan 2: Komunikasi Task

## Jawaban Pertanyaan Praktikum

### 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan bergantian secara *concurrent* . Task `read_data` mengirim data ke queue menggunakan `xQueueSend()` lalu melakukan *delay* 100ms. Selama *delay*, task masuk ke kondisi *Blocked* dan scheduler mengaktifkan task `display`. Task `display` menunggu data dari queue menggunakan `xQueueReceive()` dengan parameter `portMAX_DELAY`, yang artinya ia berada dalam status *Blocked* (menunggu) sampai ada data yang masuk.

Mekanisme queue ini memastikan sinkronisasi antar task  fungsi `display` hanya berjalan setelah `read_data` mengirimkan data ke antrean, sehingga tidak ada data yang terlewat atau terbaca ganda.

### 2. Apakah program ini berpotensi mengalami *race condition*? Jelaskan!

**Tidak**, program ini tidak berpotensi mengalami *race condition*.

*Race condition* umumnya terjadi ketika dua atau lebih task mengakses memori atau sumber daya bersamaan tanpa mekanisme sinkronisasi yang jelas. Pada program ini, pertukaran data antara task `read_data` dan `display` sepenuhnya diatur melalui antrean (Queue) bawaan FreeRTOS. Queue adalah struktur data *thread-safe* yang dikelola langsung oleh kernel RTOS dengan perlindungan *mutual exclusion* di dalamnya. Hal ini menjamin bahwa proses "tulis" dan "baca" data ke/dari memori queue tidak akan pernah bertabrakan secara bersamaan.

### 3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?


https://github.com/user-attachments/assets/97e12d0c-88c1-4d19-8f53-9676268dccc5


### source kode
```cpp

#include <DHT.h>

#define DHTPIN 2      // Pin data sensor (S) terhubung ke pin D2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

// Variabel pengganti Scheduler RTOS
unsigned long waktuSebelumnya = 0;
const long jedaWaktu = 2000; // Jeda 2 detik antar pembacaan

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Sistem Mulai Membaca Sensor..."); 
}

void loop() {
  // Mengecek waktu saat ini (sebagai pengganti Task RTOS)
  unsigned long waktuSekarang = millis();

  // Jika sudah berlalu 2 detik, jalankan eksekusi
  if (waktuSekarang - waktuSebelumnya >= jedaWaktu) {
    waktuSebelumnya = waktuSekarang;

    // Membaca data dari sensor DHT
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    // Memastikan data valid (berperan seperti QueueReceive)
    if (!isnan(t) && !isnan(h)) {
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.println(" °C");
      
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.println(" %");
      Serial.println("---");
    } else {
      Serial.println("Gagal membaca sensor DHT!");
    }
  }
}
```
