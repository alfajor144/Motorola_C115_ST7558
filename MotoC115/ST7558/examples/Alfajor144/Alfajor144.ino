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

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char myBitmap [] PROGMEM = {
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 
  0x3f, 0xf0, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0xff, 0x80, 0x00, 0x1f, 
  0x80, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x0f, 0xc0, 0x7f, 0xe0, 0x61, 0xf0, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x1f, 
  0x81, 0xff, 0xf0, 0x70, 0xf8, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x3f, 0x07, 0xff, 0xf8, 0x70, 
  0x7e, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x7e, 0x0f, 0xf0, 0xf8, 0xf0, 0x7e, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0xfc, 0x1f, 0xe0, 0x7c, 0xf0, 0x7e, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x01, 0xf0, 
  0x1f, 0xc0, 0x7c, 0xf0, 0x1f, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x03, 0xe0, 0x3f, 0x00, 0x7c, 0xf0, 
  0x0f, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x03, 0xe0, 0x7e, 0x00, 0x3c, 0xe0, 0x0f, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x03, 0xc0, 0x7e, 0x00, 0x3f, 0xe0, 0x07, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0x80, 
  0xfc, 0x00, 0x3f, 0xe0, 0x07, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0x80, 0xfc, 0x00, 0x3f, 0xc0, 
  0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x00, 0xfc, 0x00, 0x3f, 0xc0, 0x03, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x0f, 0x01, 0xfc, 0x00, 0x3f, 0x80, 0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0e, 0x01, 
  0xfc, 0x00, 0x3f, 0x00, 0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0e, 0x01, 0xfc, 0x00, 0x3e, 0x00, 
  0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0e, 0x01, 0xfc, 0x00, 0x7c, 0x0e, 0x03, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x0e, 0x01, 0xfc, 0x00, 0xfc, 0x1e, 0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x01, 
  0xfc, 0x01, 0xfc, 0x7c, 0x07, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x00, 0xfe, 0x03, 0xfc, 0xfc, 
  0x07, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x80, 0x7f, 0xff, 0xff, 0xf0, 0x1f, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x0f, 0x80, 0x7f, 0xff, 0x3f, 0xe0, 0x3f, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0xc0, 
  0x3f, 0xfe, 0x1f, 0xc0, 0x7f, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0xe0, 0x1f, 0xfc, 0x0f, 0x80, 
  0xff, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0xf0, 0x03, 0xc0, 0x00, 0x01, 0xf9, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xf9, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x04, 0xf8, 
  0x00, 0x00, 0x00, 0x03, 0xe1, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x0c, 0xfe, 0x00, 0x00, 0x00, 0x0f, 
  0xe1, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x0e, 0x7e, 0x00, 0x00, 0x00, 0x1f, 0x81, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x0e, 0x3f, 0x80, 0x00, 0x00, 0x7f, 0x81, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x1f, 
  0xf0, 0x00, 0x00, 0xff, 0x01, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x0f, 0x0f, 0xf8, 0x00, 0x03, 0xfe, 
  0x03, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x07, 0x07, 0xff, 0x80, 0x7f, 0xf0, 0x07, 0x80, 0x00, 0x1c, 
  0xe0, 0x00, 0x03, 0x80, 0xff, 0xff, 0xff, 0x80, 0x0f, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x03, 0xc0, 
  0x7f, 0xff, 0xff, 0x80, 0x1f, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x01, 0xe0, 0x0f, 0xff, 0xf8, 0x00, 
  0x1f, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0xf0, 0x03, 0xff, 0x80, 0x00, 0x7c, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x7c, 
  0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x0f, 
  0xe0, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x01, 
  0xff, 0xf0, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc
};

    
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
  lcd.display();
  delay(50);

  lcd.setTextSize(1);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0,0); // (94,64)
  lcd.println("Prueba de screen Motorola C115      94 x 64      manejada con:   arduino nano                    Alfa-Jor 144");
  lcd.display();
  delay(4000);
  
  lcd.clearDisplay(); 
  lcd.display();
  delay(50);
  
  lcd.drawBitmap(0, 0,  myBitmap, 94, 64, BLACK);
  lcd.display();
  delay(1000);

}