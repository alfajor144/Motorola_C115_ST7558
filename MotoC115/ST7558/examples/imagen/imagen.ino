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

const unsigned char manzana [] PROGMEM = {
  // 'miImagen, 94x64px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xc5, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xcf, 0xab, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xdd, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xaa, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x70, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0xaa, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x55, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x71, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0e, 0xee, 0x0c, 0xee, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 
  0xff, 0x5d, 0xff, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xbf, 0xff, 0xbb, 0xbf, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xd5, 0x51, 0x7e, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xee, 0xee, 0xfc, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xd5, 
  0x55, 0x7c, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xab, 0xbb, 0xb8, 0x02, 0x00, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x54, 0x10, 0x50, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xea, 0xaa, 0x80, 0x88, 0x80, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x50, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xba, 0xaa, 0x82, 0x00, 0x00, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x50, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xea, 0xaa, 0x88, 0x88, 0x00, 0x8b, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x44, 
  0x40, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1b, 0xaa, 0xaa, 0xa0, 0x20, 0x00, 
  0x21, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xea, 0xa2, 0x88, 0x88, 0x88, 0x88, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x40, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1b, 0xaa, 0xa2, 0x80, 0x22, 0x02, 
  0x20, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xee, 0xaa, 0xa8, 0x08, 0x80, 0x80, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x54, 
  0x40, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xba, 0xaa, 0xa2, 0x22, 0x20, 
  0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x50, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0xea, 0xaa, 0xaa, 0x88, 0x88, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x54, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xba, 0xaa, 0x2a, 0x82, 0x22, 
  0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x54, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xfe, 0xaa, 0xaa, 0xa8, 0x88, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xd5, 
  0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xa2, 0xaa, 0xaa, 0x02, 
  0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xee, 0x8a, 0xaa, 0xaa, 0x88, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 
  0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0xa2, 0x2a, 0xaa, 0x02, 
  0xae, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x50, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xee, 0xaa, 0xaa, 0xa8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xd5, 0x50, 0x00, 0x45, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xba, 0xaa, 0xaf, 
  0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x75, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0e, 0xff, 0xef, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x15, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char smile [] PROGMEM = {
  // 'smile, 94x64px
  0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xaa, 0xaa, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 
  0xbb, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xee, 0xee, 0xef, 0xee, 0xef, 0xfe, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x55, 
  0x57, 0xff, 0xfc, 0x55, 0x55, 0x55, 0x55, 0x54, 0xbb, 0xab, 0xbb, 0xab, 0xbf, 0xff, 0xff, 0xeb, 
  0xbb, 0xab, 0xbb, 0xa8, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xc0, 0x1f, 0xf5, 0x55, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xee, 0xfc, 0x00, 0x01, 0xfe, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x53, 
  0xf0, 0x00, 0x00, 0x7f, 0x55, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbb, 0xbf, 0xc0, 0x00, 0x00, 0x1f, 
  0xbb, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x55, 0x5f, 0x80, 0x00, 0x00, 0x0f, 0xd5, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x5c, 
  0x00, 0x00, 0x00, 0x01, 0xf5, 0x55, 0x55, 0x54, 0xab, 0xbb, 0xab, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0xfb, 0xbb, 0xab, 0xb8, 0x55, 0x55, 0x55, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x7d, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xe0, 0x7f, 0x80, 0x03, 0xe0, 0x3a, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0xe1, 
  0xff, 0xe0, 0x0f, 0xf0, 0x3d, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbb, 0xc1, 0xe1, 0xe0, 0x3f, 0xfc, 
  0x1f, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x57, 0x83, 0xc0, 0xf0, 0x3c, 0x3c, 0x0f, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xef, 0x83, 0x80, 0x78, 0x78, 0x1e, 0x0f, 0xee, 0xee, 0xec, 0x55, 0x55, 0x57, 0x07, 
  0x00, 0x38, 0x70, 0x0f, 0x07, 0x55, 0x55, 0x54, 0xbb, 0xab, 0xbf, 0x07, 0x0e, 0x38, 0xe0, 0x07, 
  0x07, 0xab, 0xbb, 0xa8, 0x55, 0x55, 0x57, 0x07, 0x0e, 0x38, 0xe1, 0xc7, 0x07, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0x07, 0x0e, 0x38, 0xe1, 0xc7, 0x03, 0xee, 0xee, 0xec, 0x55, 0x55, 0x5e, 0x07, 
  0x80, 0x78, 0xe1, 0xc7, 0x03, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbe, 0x03, 0x80, 0x70, 0xf0, 0x0f, 
  0x03, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x5c, 0x01, 0xe1, 0xf0, 0x70, 0x0e, 0x01, 0xd5, 0x55, 0x54, 
  0xee, 0xee, 0xec, 0x01, 0xff, 0xe0, 0x3c, 0x3e, 0x01, 0xee, 0xee, 0xec, 0x55, 0x55, 0x5c, 0x00, 
  0x7f, 0xc0, 0x3f, 0xfc, 0x01, 0xd5, 0x55, 0x54, 0xab, 0xbb, 0xbc, 0x00, 0x3f, 0x00, 0x0f, 0xf8, 
  0x01, 0xfb, 0xab, 0xb8, 0x55, 0x55, 0x5c, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x01, 0xd5, 0x55, 0x54, 
  0xee, 0xee, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xee, 0xee, 0xec, 0x55, 0x55, 0x5c, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xd5, 0x55, 0x54, 0xbb, 0xbb, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xfb, 0xbb, 0xb8, 0x55, 0x55, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xd5, 0x55, 0x54, 
  0xee, 0xee, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xee, 0xee, 0xec, 0x55, 0x54, 0x5e, 0x03, 
  0x80, 0x00, 0x00, 0x07, 0x03, 0xd5, 0x55, 0x54, 0xbb, 0xaa, 0xbe, 0x03, 0x80, 0x00, 0x00, 0x07, 
  0x03, 0xab, 0xbb, 0xa8, 0x55, 0x55, 0x56, 0x01, 0xc0, 0x00, 0x00, 0x0e, 0x03, 0x95, 0x55, 0x54, 
  0xee, 0xee, 0xef, 0x01, 0xc0, 0x00, 0x00, 0x0e, 0x07, 0xee, 0xee, 0xec, 0x55, 0x55, 0x57, 0x01, 
  0xe0, 0x00, 0x00, 0x1e, 0x07, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbf, 0x00, 0xf0, 0x00, 0x00, 0x3c, 
  0x07, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x57, 0x80, 0x78, 0x00, 0x00, 0x78, 0x0f, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xef, 0x80, 0x3c, 0x00, 0x00, 0xf8, 0x0e, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0xc0, 
  0x1f, 0x00, 0x03, 0xf0, 0x1f, 0x55, 0x55, 0x54, 0xab, 0xbb, 0xab, 0xe0, 0x0f, 0xe0, 0x1f, 0xc0, 
  0x3f, 0xbb, 0xab, 0xb8, 0x55, 0x55, 0x55, 0x60, 0x07, 0xff, 0xff, 0x80, 0x3d, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xf0, 0x01, 0xff, 0xfe, 0x00, 0x7e, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x78, 
  0x00, 0x1f, 0xe0, 0x00, 0xf5, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbb, 0xbc, 0x00, 0x00, 0x00, 0x01, 
  0xfb, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x03, 0xd5, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xef, 0x80, 0x00, 0x00, 0x07, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x57, 
  0xc0, 0x00, 0x00, 0x1f, 0x55, 0x55, 0x55, 0x54, 0xbb, 0xab, 0xbb, 0xab, 0xf0, 0x00, 0x00, 0x7f, 
  0xbb, 0xab, 0xbb, 0xa8, 0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x01, 0xfd, 0x55, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xee, 0xff, 0xc0, 0x0f, 0xfe, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x55, 
  0x5f, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x54, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xff, 0xfe, 0x3b, 
  0xbb, 0xbb, 0xbb, 0xb8, 0x55, 0x55, 0x55, 0x55, 0x55, 0x3f, 0xe1, 0x55, 0x55, 0x55, 0x55, 0x54, 
  0xee, 0xee, 0xee, 0xee, 0xee, 0xea, 0xae, 0xee, 0xee, 0xee, 0xee, 0xec, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54, 0xab, 0xbb, 0xab, 0xbb, 0xab, 0xbb, 0xab, 0xbb, 
  0xab, 0xbb, 0xab, 0xb8, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x54
};

const unsigned char dino [] PROGMEM = {
  // 'dino, 94x64px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf3, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xf3, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 
  0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x3f, 0xff, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xc0, 0x00, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 
  0x03, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x0f, 0xff, 0xff, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x18, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3e, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
void setup()   {
  Serial.begin(9600);

  Wire.begin();
  lcd.init();
  lcd.setContrast(65);
  
  lcd.clearDisplay();
  lcd.display();
}

void loop() {

  lcd.clearDisplay(); //limpiar pantalla
  lcd.display();      //pantalla obedece
  delay(50);
  
  lcd.drawBitmap(0, 0,  manzana, 94, 64, BLACK);  //dibujar en pantalla
  lcd.display(); //pantalla obedece
  delay(3000);

  lcd.clearDisplay(); //limpiar pantalla
  lcd.display();      //pantalla obedece
  delay(50);
  
  lcd.drawBitmap(0, 0,  smile, 94, 64, BLACK);  //dibujar en pantalla
  lcd.display(); //pantalla obedece
  delay(3000);

  lcd.clearDisplay(); //limpiar pantalla
  lcd.display();      //pantalla obedece
  delay(50);
  
  lcd.drawBitmap(0, 0,  dino, 94, 64, BLACK);  //dibujar en pantalla
  lcd.display(); //pantalla obedece
  delay(3000);

}
