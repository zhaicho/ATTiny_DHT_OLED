

// include the library code
#include <Wire.h>      // Wire/I2C library for Trinket and Gemma
#include <Tiny4kOLED.h>
#include <TinyDHT.h>        // lightweit DHT sensor library
//#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket

// Uncomment whatever type sensor you are using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22     // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define TEMPTYPE 0        // Use Fahrenheit (0 for celsius)

// Trinket GPIO #1 would be better but LED prevents digital talk with DHT sensor
#define DHTPIN 3          // Sensor connected to GPIO #3
DHT dht(DHTPIN, DHTTYPE);  // Define Temp Sensor

// Connect display via  i2c, default address #0 (A0-A2 not jumpered)
//TinyLiquidCrystal lcd(0);

void setup() {
  //if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz
  dht.begin();  // Initialize DHT Teperature Sensor
  
//  lcd.begin(16, 2);  // set up the LCD's number of rows and columns: 
//  lcd.setBacklight(HIGH); // Set backlight
  oled.begin(128, 32, sizeof(tiny4koled_init_128x32br), tiny4koled_init_128x32br);

  // 这个库提供了两种字体，FONT8X16和FONT6X8
  oled.setFont(FONT8X16);

  // 清除所有的内存
  oled.clear();
  oled.on();
  pinMode(1,OUTPUT);
  digitalWrite(1,LOW);
}

void loop() {
  int8_t h = dht.readHumidity();               // Read humidity
  int16_t t = dht.readTemperature(TEMPTYPE);   // read temperature

  oled.setCursor(30, 0); 

     oled.print("Hum : ");            // write to LCD
     oled.print(h);
     oled.print(" %");
     oled.setCursor(30, 2); 
     oled.print("Temp: "); 
     oled.print(t);
     oled.print(" C");
  delay(2000);  // Read temp every second (2000 ms) (DHT sensor max rate)
}