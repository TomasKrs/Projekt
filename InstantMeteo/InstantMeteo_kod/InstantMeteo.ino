#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include "lcd_fonty.h"
#include "preklad.h"

// Wi-Fi nastavenia
const char* ssid = "ZADAJ-SSID-SIETE";
const char* password = "ZADAJ-HESLO-SIETE";

// OpenWeatherMap API
const String apiKey = "ZADAJ-API-KĽÚČ";  // Získaj na OpenWeatherMap
const String city = "Martin,SK";        // Mesto, ktoré chceš sledovať (nezabudnuť na kód krajiny)
const String units = "metric";          // Jednotky: "metric" pre °C, "imperial" pre °F
const String lang = "en";               // Jazyk odpovede (napr. "sk" pre slovenčinu - pozor ale na znakovú sadu)

// URL pre API
String weatherUrl = "http://api.openweathermap.org/data/2.5/forecast?q=" + city +
                    "&appid=" + apiKey + "&units=" + units + "&lang=" + lang + "&cnt=3";

// DHT Senzor
#define DHTPIN 13                       // Ktorý pin ovláda DHT senzor
#define DHTTYPE DHT11                   // Typ senzora DHT  (DHT22 alebo DHT11)
DHT dht(DHTPIN, DHTTYPE);               // zadefinovanie DHT senzora

// Inicializácia LCD displeja (16x4)
LiquidCrystal_I2C lcd(0x27, 16, 4);

// Procedúra na vymazanie riadku s parametrom
void clearLCDLine(int line)
{               
        lcd.setCursor(0,line);
        for(int n = 0; n < 20; n++) // 20 je počet symbolov v jednom riadku (20x2 alebo 20x4)
        {
                lcd.print(" ");
        }
}

// Procedúra na výpis jednotlivých hôdnot na display s parametrami
void LCDWriteLine(int line, int pic, float param1, String param2, float param3)
{
        clearLCDLine(line);
        lcd.setCursor(1, line);     // nastavenie kurzora na 0, riadok
        lcd.write(byte(pic));       // vykreslenie symbolu (pic)
        lcd.setCursor(3, line);     // nastavenie kurzora pre zaciatok vypisu hodnoty 1. parametru
        lcd.print(param1, 1);       // napisanie parametra
        // lcd.print(param2);          // vypisanie jednotky
        lcd.setCursor(10, line);    // nastavenie na poziciu oddelovaca (sipky)
        lcd.write(byte(3));         // napisanie oddelovaca (sipky)
        lcd.setCursor(12, line);    // nastavenie kurzora na zaciatok pisania 2. udaju
        lcd.print(param3,1);        // 2. udaj
        // lcd.print(param2);          // jednotky druheho udaju 
}

// Štart
void setup() {
  Serial.begin(115200);

  // DHT senzor inicializácia
  dht.begin();

  // Inicializácia LCD
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, Time);
  lcd.createChar(1, Sun);
  lcd.createChar(2, Humid);
  lcd.createChar(3, Arrow);
  lcd.createChar(4, Internet);
  lcd.createChar(5, Wind);
  lcd.createChar(6, Heart);
  lcd.createChar(7, Sensor);

  // Úvodný výpis na LCD
  lcd.setCursor(0, 0);
  lcd.print("*** InstantMeteo ***");
  lcd.setCursor(4,2);
  lcd.print("Pripajanie...");
  delay(5000);

  // Pripojenie na Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi pripojené!");
  lcd.setCursor(2, 2);
  lcd.print("WiFi pripojene!   ");
  lcd.setCursor(1, 3);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
  delay(5000);
}

void loop() {
  // Načítanie údajov z API
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(weatherUrl);  // Inicializácia požiadavky
    int httpCode = http.GET();  // Odoslanie GET požiadavky

    if (httpCode > 0) {  // Ak je odpoveď kladná
      String payload = http.getString();
      Serial.println("Úspešná odpoveď z API:");
      Serial.println(payload);

      // Spracovanie JSON dát
      DynamicJsonDocument doc(1024 * 5);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        // Načítanie predpovede na nasledujúce 3 hodiny
        String time = doc["list"][0]["dt_txt"];  // Čas predpovede (xx:yy)
        float temp = doc["list"][0]["main"]["temp"];  // Teplota (celzius)
        float pressure = doc["list"][0]["main"]["pressure"];  // Tlak (hPA)
        float humidity = doc["list"][0]["main"]["humidity"];  // Vlhkosť (%)
        const char* description = doc["list"][0]["weather"][0]["main"];  // Popis
        float wind = doc["list"][0]["wind"]["speed"];  // Vietor (m/s)

          // Načítanie predpovede na nasledujúcich 6 hodin
        String timeForw = doc["list"][1]["dt_txt"];  // Čas predpovede
        float tempForw = doc["list"][1]["main"]["temp"];  // Teplota
        float pressureForw = doc["list"][1]["main"]["pressure"];  // Tlak (hPA)
        float humidityForw = doc["list"][1]["main"]["humidity"];  // Vlhkosť
        const char* descriptionForw = doc["list"][1]["weather"][0]["main"];  // Popis
        float windForw = doc["list"][1]["wind"]["speed"];  // Vietor (m/s)

        // Preklad pocasia
        const char* popisPocasia = translate(description);
        const char* popisPocasiaForw = translate(descriptionForw);

        // Vypis do konzoly
        Serial.println("\nPredpoveď na 3 hodiny dopredu:");
        Serial.println("Čas: "+ time + " -------> " + timeForw);
        Serial.print("Teplota: ");
        Serial.print(temp); 
        Serial.print(" C -------> ");
        Serial.print(tempForw);
        Serial.println(" C");
        Serial.print("Tlak: ");
        Serial.print(pressure); 
        Serial.print(" hPa -------> ");
        Serial.print(pressureForw);
        Serial.println(" hPa");
        Serial.print("Vietor: ");
        Serial.print(wind);
        Serial.print(" m/s -------> ");
        Serial.print(windForw);
        Serial.println(" m/s");
        Serial.print("Popis:");
        Serial.print(popisPocasia);
        Serial.print("------------>");
        Serial.println(popisPocasiaForw);
     
        // Výstup na LCD displej
        lcd.clear();

          // Zobrazenie casu (0. staly riadok)
          lcd.setCursor(0, 0);
          lcd.write(byte(4));
          lcd.write(byte(0));
          lcd.print(" "+ time.substring(11, 16));
          lcd.setCursor(10, 0);
          lcd.write(byte(3));
          lcd.print(" "+ timeForw.substring(11, 16)); // skrat casovy udaj aby sa zmestil

          // Zobrazenie senzora (3. staly riadok)
          float humidityDHT = dht.readHumidity();
          float temperatureDHT = dht.readTemperature();
          clearLCDLine(2);
          lcd.setCursor(0,3);
          lcd.write(7);
          lcd.write(1);
          lcd.print(" ");
          lcd.print(temperatureDHT,1);
          lcd.setCursor(10,3);
          lcd.write(2);
          lcd.print(" ");
          lcd.print(humidityDHT,1);

          // opakovanie 20x

        for (int i = 0; i <= 20; i++) {
          // zamena udajov (1. a 2. riadok) - teplota a vlhkost
          LCDWriteLine(1,1, temp, "", tempForw);
          LCDWriteLine(2,2, humidity, "", humidityForw);
          delay(10000);
          // zamena udajov (1. a 2. riadok) - popis pocasia a vietor
          clearLCDLine(1);
          lcd.setCursor(3,1);
          lcd.print(popisPocasia);
          lcd.setCursor(10,1);
          lcd.write(3);
          lcd.print(" ");
          lcd.print(popisPocasiaForw);
          LCDWriteLine(2,5, wind, "", windForw);
          delay(10000);
          // zamena udajov (1. a 2. riadok) - teplota a tlak
          LCDWriteLine(1,1, temp, "", tempForw);
          LCDWriteLine(2,6, pressure, "", pressureForw);
          delay(10000);
        }
      } else {
        Serial.println("Chyba pri dekódovaní JSON.");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Chyba JSON");
      }
    } else {
      Serial.print("HTTP požiadavka zlyhala. Kód: ");
      Serial.println(httpCode);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HTTP chyba:");
      lcd.setCursor(0, 1);
      lcd.print(httpCode);
    }

    http.end();  // Ukončenie požiadavky
  }

}
