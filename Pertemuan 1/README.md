## **Jawaban Percobaan 1.5.4 (Percabangan)**

1. **Pada kondisi apa program masuk ke blok if?**

   Saat nilai `timeDelay <= 100`.
   Artinya delay sudah sangat kecil (LED berkedip sangat cepat), sehingga sistem melakukan reset.

2. **Pada kondisi apa program masuk ke blok else?**

   Saat nilai `timeDelay > 100`.
   Program akan terus mengurangi delay agar kedipan LED semakin cepat.

3. **Apa fungsi dari perintah delay(timeDelay)?**

   Mengatur lama waktu LED menyala dan mati.
   Semakin besar nilai delay → LED berkedip lambat
   Semakin kecil nilai delay → LED berkedip cepat

4. **Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati),
ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang →
mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!**

```cpp
int ledPin = 6;
int timeDelay = 100; // mulai dari cepat

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  if (timeDelay < 500) {
    timeDelay += 100; // dari cepat ke sedang
  } else {
    digitalWrite(ledPin, LOW); // mati
    while(true); // berhenti
  }
}
```

**Penjelasan:**

* `timeDelay = 100` → LED cepat
* `timeDelay += 100` → jadi lebih lambat (sedang)
* Saat cukup lambat → LED dimatikan permanen

---

## **Jawaban Percobaan 1.6.4 (Perulangan)**

1. **Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan**

  https://www.tinkercad.com/things/kxc8bb8RHza-perulangan?sharecode=pBjejah-fIyF2NHrar3cymjA62TYpYMmZpRzxMmen2E

2. **Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
**

   Menggunakan:

```cpp
for (int ledPin = 2; ledPin < 8; ledPin++)
```

Program menyalakan LED dari pin kecil ke besar secara berurutan.

3. **Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
**

   Menggunakan:

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--)
```

Program menyalakan LED dari pin besar ke kecil.

4. **Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian
dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
**

```cpp
void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // kiri (2,3,4)
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(500);

  // kanan (5,6,7)
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(500);
}
```
