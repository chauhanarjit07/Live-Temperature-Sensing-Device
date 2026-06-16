#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2       // Pin connected to DHT11 data pin
#define DHTTYPE DHT11  // DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt if not found
  }
  display.clearDisplay();
  display.display();

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // If sensor failed to read
  if (isnan(hum) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial monitor output
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tHumidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Display on OLED
  display.clearDisplay();
  
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,10);
  display.setFont(&FreeSansBold12pt7b); 
  display.print("Temptrack");
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Temp: ");
  display.print(temp, 1);
  display.print(" C | ");
  temp=1.8*temp+32;
  display.print(temp,1);
  display.print(" F ");
  display.setCursor(0, 40);
  display.print("Hum: ");
  display.print(hum, 1);
  display.print(" %");
  if(temp>104){
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,30);
    display.print("Warning! Temprature>40");
  }
  display.display();

  delay(1000);
}