/***************************************************************************
 * Display Temperature & Humidity / Musée d'histoire naturelle de Fribourg
/***************************************************************************
 * Copyright 2016 Simon Schoepfer and Jacques Supcik
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***************************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHT_PIN  7
#define DHT_TYPE DHT11 
#define ROWS     2
#define COLUMNS  16

#define HUM_FR_TXT "Hum.     "
#define TMP_FR_TXT "Temp.    "
#define HUM_DE_TXT "Feuchtig."
#define TMP_DE_TXT "Temp.    "

#define TEMP_LINE 1
#define HUM_LINE 0

#define DELTA_TEMP 0
#define DELTA_HUM  0
#define NUMBER_POS 10
#define LANG_PERIOD 3000

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, COLUMNS, ROWS);   

void setup() {
    lcd.init();
    dht.begin();

    byte Celsius[8] = {B11100,B10100,B11100,B0000,B00000,B00000,B00000,B00000};
    lcd.createChar(0, Celsius);

    lcd.setCursor(NUMBER_POS + 2, HUM_LINE);
    lcd.print("%");

    lcd.setCursor(NUMBER_POS + 2, TEMP_LINE);
    lcd.write((uint8_t)0); 
    lcd.setCursor(NUMBER_POS + 3, TEMP_LINE);
    lcd.print("C");
}

void loop() {
    if (((millis() / LANG_PERIOD) % 2) == 1) { // change every 3 seconds
        lcd.setCursor(0, HUM_LINE);
        lcd.print(HUM_FR_TXT);
        lcd.setCursor(0, TEMP_LINE);
        lcd.print(TMP_FR_TXT);
    } else {
        lcd.setCursor(0, HUM_LINE);
        lcd.print(HUM_DE_TXT);
        lcd.setCursor(0, TEMP_LINE);
        lcd.print(TMP_FR_TXT);
    }
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    lcd.setCursor(NUMBER_POS, HUM_LINE);
    int hi = (int)(h) + DELTA_HUM;
    if (hi > 99) hi = 99;
    if (hi < 10) hi = 10;
    lcd.print(hi);
  
    lcd.setCursor(NUMBER_POS, TEMP_LINE);
    int ti = (int)(t) + DELTA_TEMP;
    if (ti > 99) ti = 99;
    if (ti < 10) ti = 10;
    lcd.print(ti);
}

