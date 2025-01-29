# Projekt
Projekt InstantMETEO je navrhnutý na rýchle zobrazovanie predpovede počasia na nasledujúce 3 a 6 hodín. Umožňuje človeku, ktorý sa ponáhľa z domu / kancelárie, okamžite vidieť dôležité informácie o počasi bez potreby vytiahnuť mobil alebo hľadať informácie online. Displej zobrazí teplotu, tlak, vlhkosť, vietor a popis počasia. Zároveň DHT sensor sa postará o zmeranie teploty v priestore, kde sa človek nachádza.
Použitie v praxi
•	Rýchla kontrola počasia pri odchode z domu
•	Možnosť lepšieho rozhodovania o vhodnom oblečení a vybavení
•	Vhodné pre domácnosti, kancelárie

Komponenty (hardware):
1. ESP32 (NodeMCU-32S) (Datasheet)
2. LCD displej 16x4 s I2C  (Datasheet) 
3. DHT11 (teplota a vlhkosť) – prípadne DHT22
4. Prepojovacie káble
 
Pred prvým nahratím do ESP32 treba vyplniť WIFI SSID a heslo + OpenWeatherMap API kľúČ

