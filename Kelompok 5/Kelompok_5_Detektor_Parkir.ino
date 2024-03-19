#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Inisialisasi objek LCD I2C dengan alamat 0x27

const int trigPin = 7;    // Pin trigger sensor ultrasonik
const int echoPin = 4;    // Pin echo sensor ultrasonik
const int buzzerPin = 9;  // Pin buzzer pasif

unsigned long previousMillis = 0;
const long buzzerInterval = 100; // Interval waktu antara bunyi buzzer (ms)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Jarak:");

  // Tes bunyi buzzer saat booting
  beep(1000); // Bunyikan buzzer saat booting
}

void loop() {
  // Mengirim sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menerima waktu pantulan sinyal ultrasonik
  long duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak dalam sentimeter
  long distance_cm = duration * 0.034 / 2;

  // Menyalakan buzzer berdasarkan jarak
  if (distance_cm < 10) {
    beep(20); // Bunyi sangat cepat jika jarak kurang dari 10 cm
  } else if (distance_cm >= 10 && distance_cm < 20) {
    beep(500); // Bunyi agak cepat jika jarak antara 10 dan 20 cm
  } else if (distance_cm >= 20 && distance_cm < 30) {
    beep(1000); // Bunyi agak lama jika jarak antara 20 dan 30 cm
  } else {
    noTone(buzzerPin); // Matikan bunyi buzzer jika jarak lebih dari atau sama dengan 30 cm
  }

  // Menampilkan jarak di LCD
  lcd.setCursor(7, 0);
  lcd.print("    "); // Menghapus nilai sebelumnya
  lcd.setCursor(7, 0);
  lcd.print(distance_cm);
  lcd.print(" ");

  delay(100); // Delay untuk stabilitas bacaan
}

// Fungsi untuk menyalakan buzzer dengan durasi tertentu
void beep(int duration) {
  unsigned long currentMillis = millis();
  
  // Bunyi buzzer hanya jika telah berlalu interval waktu tertentu
  if (currentMillis - previousMillis >= buzzerInterval) {
    previousMillis = currentMillis;
    tone(buzzerPin, 1000); // Nyalakan bunyi buzzer dengan frekuensi 1000 Hz
    delay(duration); // Tahan bunyi buzzer selama durasi yang ditentukan
    noTone(buzzerPin); // Matikan bunyi buzzer
  }
}