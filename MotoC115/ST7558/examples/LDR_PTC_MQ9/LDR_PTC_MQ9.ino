/*
 *  94________
 * | _________ |64
 * ||         ||
 * ||_________||
 * |___________|
 *   12345678
 *   
 * 1: VCC = 3.3v
 * 2: null
 * 3: SCL = A5
 * 4: SDA = A4
 * 5: GND
 * 6: GND
 * 7: cap 1uF -> GND
 * 8: RESET = A0
 */
#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>
#include <ST7558.h>
#include <Wire.h>

#define RST A0
ST7558 lcd = ST7558(RST);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
    
void setup()   {
  Serial.begin(9600);
  
  Wire.begin();
  lcd.init();
  lcd.setContrast(65);
  
  lcd.display();
  lcd.clearDisplay();
}

void loop() {

  lcd.clearDisplay(); 
  
  lcd.setTextSize(2);
  lcd.setTextColor(BLACK);

  /*
  //Datos del LDR
  lcd.setCursor(0,0); // (94,64)
  lcd.println("LDR: "+String(analogRead(3)));
  
  //Datos del TERMISTOR
  lcd.setCursor(0,0); // (94,64)
  lcd.println("PTC: "+String(map(analogRead(3),300,800,20,70)));
  */

  //MQ-9: Sensor de gas CO
  lcd.setCursor(0,0); // (94,64)
  lcd.println("MQ9: "+String(analogRead(3)));
  
  lcd.display();
  delay(500);

}
