#ifndef LCD_FONTY_H
#define LCD_FONTY_H

// Vlastné znaky pre LCD display (čas, teplota, vlhkosť, šípka, oko, vietor, srdce, senzor)

// LCD symbol hodin
byte Time[] = {
  B10100,
  B00001,
  B10000,
  B10101,
  B11000,
  B10001,
  B00000,
  B10100
};

// LCD symbol Slnka (teploty)
byte Sun[] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000
};

// LCD symbol vlhkosti (kvapka)
byte Humid[] = {
  B00000,
  B00100,
  B01100,
  B11110,
  B11110,
  B11110,
  B01100,
  B00000
};

// LCD symbol sipky 
byte Arrow[] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000
};

// LCD symbol Internetu
byte Internet[] = {
  B11111,
  B10001,
  B10101,
  B10001,
  B10101,
  B10101,
  B10001,
  B11111
};

// LCD symbol vetra
byte Wind[] = {
  B01100,
  B10011,
  B00000,
  B11111,
  B00000,
  B11101,
  B00010,
  B00000
};

// LCD symbol srdca
byte Heart[] = {
  B00000,
  B11011,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000
};

// LCD symbol senzoru
byte Sensor[] = {
  B11111,
  B10101,
  B11011,
  B10101,
  B11011,
  B11111,
  B10101,
  B10101
};

// LCD symbol metrov za sekundu
byte mdels[] = {
  B11111,
  B10101,
  B10101,
  B00111,
  B00100,
  B00111,
  B00001,
  B00111
};
#endif // LCD_FONTY_H