/*
 * File:        digital_thermometer.ino
 * Author:      Emre Kızılelma
 * Date:        2024-12-17
 * Description: This program reads temperature data from an LM35 sensor
 *              and displays the temperature on an LCD screen and via
 *              the serial monitor.
 * Version:     1.0
 * License:     MIT
 */

#include <LiquidCrystal_I2C.h>

#define VOLTAGE_REF 5000.0           // Besleme gerilimi: 5000 mV ->  5 V
#define ADC_RESOLUTION 1024.0        // ADC Resolution (Analog Digital Converter Resolution) (Analog Dijital Çevirici Çözünürlüğü) -> 10 bit = 2^10
#define TEMP_CONVERSION_FACTOR 10.0  // 10 mV/°C -> LM35 sensörü her bir °C sıcaklık için çıkışında 10 mV artış sağlar.

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 2x16 LCD ekran tanımlaması yapıldı

const uint8_t LM35_PIN = A0;   // A0 = 0xe -> 14 numaralı analog pin
const uint8_t BUZZER_PIN = 8;  // 8 numaralı dijital pin

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // 8 numaralı 'Buzzer' pini çıkış olarak ayarlandı.
  Serial.begin(9600);           // Arduino-Bilgisayar seri haberleşme protokolünün değeri 9600 baud (saniyede alınan / gönderilen bit sayısı) olarak ayarlandı.
  lcd.begin();                  
  lcd.print("Sicaklik: ");
}

void loop() {
  int sensor_value = analogRead(LM35_PIN); // LM35 Sıcaklık sensöründen analog okuma yapılıp sensor_value isimli değişkene atanır.

  float voltage = (sensor_value * VOLTAGE_REF) / ADC_RESOLUTION; // Voltaj değerinin hesaplanması
  float temperature = voltage / TEMP_CONVERSION_FACTOR;          // Sıcaklık değerinin hesaplanması
  
  // LCD Ekrana sıcaklık bilgilerinin yazılması
  lcd.setCursor(0, 1);
  lcd.print(temperature, 1);
  lcd.print(" C ");

  // Seri mönitöre sıcaklık bilgilerinin yazılması
  Serial.print("Sicaklik Degeri: ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  delay(1000); // 1000ms = 1s


  // Sıcaklık 25°C'yi geçtiği zaman buzzer'ı 1ms aralıklarla çalıştırır.
  if (temperature > 25.0) {
    tone(BUZZER_PIN, 100);
    delay(1000);
    noTone(BUZZER_PIN);
    delay(1000);
  }

  else {

  } 
}
