# Percobaan 1 : Multitasking (FreeRTOS)

## Jawaban Pertanyaan Praktikum

### 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task berjalan secara **bergantian**. FreeRTOS menggunakan scheduler *preemptive* berbasis prioritas dengan sistem *time-slicing*. Karena ketiga task memiliki prioritas sama (priority 1), scheduler membagi waktu CPU secara bergantian di antara task yang dalam kondisi *Ready*. Ketika sebuah task memanggil `vTaskDelay()`, task tersebut masuk ke kondisi *Blocked* dan CPU diserahkan ke task lain. Efeknya terlihat seperti berjalan bersamaan (*concurrent*) meskipun sebenarnya hanya satu task yang menggunakan CPU pada satu waktu tertentu.

### 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Langkah menambah task keempat:

* Deklarasikan prototipe fungsi task baru, misalnya `void TaskKeempat(void *pvParameters);`.


* Tambahkan `xTaskCreate(TaskKeempat, "task4", 128, NULL, 1, NULL);` di dalam `setup()` sebelum `vTaskStartScheduler()`.


* Definisikan fungsi task-nya di luar `loop()` dengan menyertakan *looping* `while(1)` dan `vTaskDelay()`.

### 3. Modifikasilah program dengan menambah sensor (potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya?

link modifikasi : https://wokwi.com/projects/463715247595730945
### B. Kode Program Modifikasi

```cpp
#include <Arduino_FreeRTOS.h>

// Variabel global untuk mengatur kecepatan (delay) semua task
volatile int blinkDelay = 500; 

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);
void TaskPotensio(void *pvParameters); // Task tambahan untuk baca sensor

void setup() {
  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
  xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL);
  xTaskCreate(TaskPotensio, "task4", 128, NULL, 1, NULL); // Task keempat

  vTaskStartScheduler();
}

void loop() {}

// Task baca potensiometer untuk mengubah kecepatan
void TaskPotensio(void *pvParameters) {
  while(1) {
    int sensorValue = analogRead(A0);
    // Map nilai 0-1023 jadi delay 50ms - 1000ms
    blinkDelay = map(sensorValue, 0, 1023, 50, 1000); 
    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);
  while(1) {
    digitalWrite(8, HIGH);
    vTaskDelay(blinkDelay / portTICK_PERIOD_MS); // Pakai variabel blinkDelay
    digitalWrite(8, LOW);
    vTaskDelay(blinkDelay / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT);
  while(1) {
    digitalWrite(7, HIGH);
    vTaskDelay((blinkDelay + 100) / portTICK_PERIOD_MS); // Variasi delay
    digitalWrite(7, LOW);
    vTaskDelay((blinkDelay + 100) / portTICK_PERIOD_MS);
  }
}

void Taskprint(void *pvParameters) {
  int counter = 0;
  while(1) {
    counter++;
    Serial.print("Counter: ");
    Serial.print(counter);
    Serial.print(" | Delay Aktif: ");
    Serial.println(blinkDelay);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Print tetap per 1 detik
  }
}

```

### Penjelasan
Setelah potensiometer ditambahkan, nilai analog di pin A0 akan terus dibaca oleh TaskPotensio. Nilai ini kemudian mengubah variabel blinkDelay secara global. Hasilnya, kecepatan kedipan LED pada TaskBlink1 dan TaskBlink2 akan berubah secara real-time mengikuti putaran potensiometer, membuktikan bahwa FreeRTOS dapat menangani pembacaan sensor dan aksi output dalam task yang berbeda secara efisien.
