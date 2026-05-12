# Percobaan 1 : Eksternal Interrupt

## Jawaban Pertanyaan Praktikum

### 1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt!

Ketika tombol ditekan, pin 2 yang semula `HIGH` (karena diatur sebagai `INPUT_PULLUP`) berubah menjadi `LOW`. Perubahan sinyal dari `HIGH` ke `LOW` ini terdeteksi sebagai *edge* `FALLING` oleh *hardware interrupt controller* ATmega328P.

Proses yang terjadi selanjutnya: CPU akan langsung menghentikan eksekusi fungsi `loop()`, menyimpan *state* program saat ini ke *stack*, lalu melompat untuk mengeksekusi fungsi ISR (Interrupt Service Routine) bernama `tombolInterrupt()`. Di dalam ISR, nilai variabel `ledState` di-*toggle* (dibalik). Setelah eksekusi ISR selesai, CPU akan memulihkan *state* yang disimpan tadi dan melanjutkan `loop()` dari titik tepat di mana ia dihentikan. Pada iterasi `loop()` berikutnya, perintah `digitalWrite(13, ledState)` akan menuliskan nilai terbaru ke LED, sehingga kondisi LED berubah.

#### 2. Apa fungsi `attachInterrupt()` pada program tersebut?

Fungsi `attachInterrupt()` bertugas untuk mendaftarkan fungsi ISR ke *hardware interrupt controller* mikrokontroler.

* **Parameter 1 (`digitalPinToInterrupt(2)`):** Mengonversi nomor pin fisik ke nomor interrupt internal (pada Arduino Uno, pin 2 = interrupt 0).
* **Parameter 2:** Merupakan nama fungsi ISR yang akan dipanggil dan dijalankan saat interrupt terjadi.
* **Parameter 3 (`FALLING`):** Menentukan kondisi sinyal *trigger* yang akan memicu interrupt.

Tanpa pemanggilan fungsi `attachInterrupt()`, *hardware interrupt* tidak akan terhubung ke fungsi instruksi apa pun, sehingga penekanan tombol fisik tidak akan ditangani oleh program.

#### 3. Mengapa pada ISR tidak disarankan menggunakan `delay()` dan `Serial.print()`?

* **Penggunaan `delay()`:** `delay()` bekerja dengan mengandalkan timer internal. Namun, selama ISR sedang berjalan, proses interrupt lain akan dinonaktifkan sementara. Hal ini menyebabkan timer yang digunakan oleh `delay()` tidak bisa berjalan dan akan berujung membuat sistem mengalami *hang*.
* **Penggunaan `Serial.print()`:** ini menggunakan *buffer* dan interrupt komunikasi serial (UART) untuk mengirim data secara asinkron. Memanggil `Serial.print()` di dalam ISR sangat berisiko menyebabkan *deadlock* karena interrupt UART tidak dapat diinterupsi/terjadi selama proses ISR sedang aktif.

#### 4. Apa fungsi keyword `volatile` pada variabel `ledState`?

Keyword `volatile` berfungsi sebagai instruksi kepada *compiler* bahwa nilai variabel `ledState` dapat berubah sewaktu-waktu di luar alur eksekusi normal program (dalam hal ini, nilainya diubah secara tiba-tiba oleh ISR yang dipicu *hardware*).

Tanpa keyword `volatile`, *compiler* mungkin akan melakukan optimasi dengan menyimpan nilai variabel tersebut di dalam register CPU dan tidak membacanya ulang dari memori (RAM) pada setiap iterasi `loop()`. Akibatnya, perubahan nilai yang dilakukan oleh ISR tidak akan terbaca oleh program utama. Dengan menggunakan `volatile`, *compiler* akan dipaksa untuk selalu membaca nilai variabel tersebut langsung dari RAM secara *real-time*, sehingga perubahan apa pun dari ISR akan selalu terdeteksi dengan akurat.

#### 5. Perbedaan mode interrupt RISING, CHANGE, dan LOW; analisis perubahan perilaku LED:

* **`RISING`:** ISR dipicu pada saat sinyal berubah dari `LOW` ke `HIGH` (saat tombol dilepas). *Perilaku:* LED mengalami *toggle* **bukan** saat tombol ditekan, melainkan baru akan merespons sesaat ketika tombol **dilepaskan** (terdapat jeda *delay* alami antara aksi menekan dan respons LED).
* **`CHANGE`:** ISR dipicu pada setiap terjadi perubahan sinyal fisik, baik itu `FALLING` maupun `RISING`. *Perilaku:* LED akan melakukan *toggle* dua kali dalam satu siklus tekan-lepas (satu kali saat tombol ditekan, dan satu kali lagi saat tombol dilepas). Secara bersih (*net*), LED akan kembali ke kondisi semula setelah satu siklus tombol selesai.
* **`LOW`:** ISR akan dipicu secara terus-menerus tiada henti selama kondisi pin tertahan di level logika `LOW` (tombol ditahan/ditekan lama). *Perilaku:* Karena ISR dipanggil berulang-ulang dengan sangat cepat selama tombol ditahan, LED akan melakukan *toggle* ribuan kali per detik. Secara kasat mata, LED akan tampak menyala redup atau terus menyala karena frekuensi pergantian nyala-mati yang terlalu tinggi untuk bisa ditangkap oleh mata telanjang.
