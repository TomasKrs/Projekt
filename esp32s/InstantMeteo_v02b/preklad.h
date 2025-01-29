#ifndef preklad_H
#define preklad_H

// #include <Arduino.h>

// Štruktúra na uloženie dvojíc anglických a slovenských výrazov
struct Translation {
    const char* english;
    const char* slovak;
};

// Pole s anglickými výrazmi a ich slovenskými prekladmi
const Translation translations[] = {
    {"Thunderstorm", "Burka"},
    {"Drizzle", "Mrholi"},
    {"Rain", "Dazd"},
    {"Snow", "Sneh"},
    {"Mist", "Hmla"},
    {"Smoke", "Opar"},
    {"Haze", "Opar"},
    {"Dust", "Prasno"},
    {"Fog", "Hmla"},
    {"Sand", "Piesok"},
    {"Ash", "Popol"},
    {"Squall", "Burka"},
    {"Tornado", "Tornad"},
    {"Clear", "Jasno"},
    {"Clouds", "Oblaky"}
};

// Funkcia na vyhľadanie slovenského prekladu podľa anglického výrazu
const char* translate(const char* englishWord) {
    for (int i = 0; i < sizeof(translations) / sizeof(translations[0]); i++) {
        if (strcmp(translations[i].english, englishWord) == 0) {
            return translations[i].slovak; // Nájde sa preklad
        }
    }
    return "Neznamy vyraz"; // Ak sa nenašiel preklad
}

#endif // preklad_H
