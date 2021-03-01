#include "FastLED.h"
#include <SPI.h>

//Leave as GRB. Use CRGB(r,g,b) for setting color values
#define COLOR_ORDER       GRB
#define MAX_BRIGHTNESS    100
#define NUM_LEDS          140
#define DATA_PIN          6

#define WIDTH 20
#define HEIGHT 7

CRGB leds[NUM_LEDS];

uint8_t charset[60][5];

void setup() {
  createAllCharacters();
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds < WS2812B, DATA_PIN - 1, COLOR_ORDER > (leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  displayText("TEAM 79 KRUNCH!", 0x1515FF, 0);
  line(0xE837FC);
  displayText("FIRST POWER UP", 0xFECF10, 0x800000);
  crossLines(0xFECF07, 0xFF0000);
  displayText("GRACIOUS PROFESSIONALISM!", 0x1515FF, 0);
  checkerboard(0x42F4EB, 0xAD2FED);
  displayText("DEAN KAMEN ROCKS!", 0x00FF00, 0);
  rainbow();
  displayText("WOODIE FLOWERS IS OUR HERO!", 0xF918AE, 0);
  water();
  displayText("WATER GAME 2019 CONFIRMED!", 0xFFFFFF, 0x0707CC);
  powerOff();

  //For media night
//  displayText("HI MOM!   HI DAD!", 0x00ff99, 0x5b004e);
//  crossLines(0x00ff99, 0x5b004e);
//  displayText("WELCOME TO THE 2018 MEDIA NIGHT!", 0xFFFFFF, 0);
//  displayText("THANKS TO OUR SPONSORS:", 0xFFFFFF, 0);
//  displayText("EAST LAKE HIGH SCHOOL", 0xFFFFFF, 0);
//  displayText("HONEYWELL", 0xeb3527, 0);
//  displayText("JABIL", 0x595959, 0);
//  displayText("PINELLAS COUNTY STEM ACADEMY", 0x3b4f81, 0);
//  displayText("DOOLITTLE INSTITUTE", 0x0950f7, 0);
//  displayText("BUTLER", 0xcc14ff, 0);
//  displayText("GE", 0x326FBD, 0);
//  displayText("NETWORK FOR GOOD", 0x809EFF, 0);
//  displayText("JMS MEDICAL SUPPLY", 0x00ABE4, 0);
//  displayText("TATA CONSULTANCY SERVICES", 0x665CC7, 0);
//  displayText("DEX IMAGING", 0xCC0000, 0);
//  displayText("LOWE'S", 0x0015d8, 0);
//  displayText("MAGIC BUS", 0xff960c, 0);
//  displayText("ROTARY INTERNATIONAL", 0xf7ef09, 0);
//  displayText("PINELLAS COUNTY SCHOOLS", 0x1cff41, 0);
//  displayText("STATE OF FLORIDA", 0xff960c, 0);
//  water();
//  rainbow();
//  checkerboard(0xf91bd8, 0x16ff92);
//  powerOff();
}

void line(uint32_t color) {
  FastLED.clear();
  int num = WIDTH * HEIGHT;
  for (int i = 0; i < num; i++) {
    leds[i] = color;
    FastLED.show();
    delay(10);
  }
  delay(500);
  for (int i = num - 1; i >= 0; i--) {
    leds[i] = 0;
    FastLED.show();
    delay(10);
  }
}

void displayText(String text, uint32_t textColor, uint32_t backgroundColor) {
  FastLED.clear();
  int scroll = -22;
  int endScroll = strlen(text.c_str()) * 6 - 1;
  while (scroll < endScroll) {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        int xScroll = x + scroll;
        if (xScroll % 6 == 5 || xScroll < 0 || xScroll > strlen(text.c_str()) * 6 - 1) {
          leds[(HEIGHT - 1 - y) * WIDTH + ((y % 2) * ((WIDTH - 1) - 2 * x) + x)] = backgroundColor;
        } else {
          int i = xScroll / 6;
          char c;
          if (i < strlen(text.c_str())) c = text.c_str()[i];
          else c = ' ';
          if (binValue(charset[c - 32][xScroll % 6], y)) {
            leds[(HEIGHT - 1 - y) * WIDTH + ((y % 2) * ((WIDTH - 1) - 2 * x) + x)] = textColor;
          } else {
            leds[(HEIGHT - 1 - y) * WIDTH + ((y % 2) * ((WIDTH - 1) - 2 * x) + x)] = backgroundColor;
          }
        }
      }
    }
    FastLED.show();
    delay(1000 / 16);
    scroll++;
  }
}

void crossLines(uint32_t color1, uint32_t color2) {
  FastLED.clear();
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (y % 2 == 0) {
        setPix(x, y, color1);
      } else setPix(WIDTH - x - 1, y, color2);
    }
    FastLED.show();
    delay(40);
  }
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (y % 2 == 0) {
        setPix(x, y, 0);
      } else setPix(WIDTH - x - 1, y, 0);
    }
    FastLED.show();
    delay(40);
  }
}

void checkerboard(uint32_t color1, uint32_t color2) {
  FastLED.clear();
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = y % 2; x < WIDTH; x += 2) {
      setPix(x, y, color1);
      FastLED.show();
      delay(50);
    }
  }
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = (y + 1) % 2; x < WIDTH; x += 2) {
      setPix(x, y, color2);
      FastLED.show();
      delay(50);
    }
  }
}

void rainbow() {
  uint16_t hue;
  FastLED.clear();

  for (hue = 10; hue < 255 * 3; hue++)
  {

    fill_rainbow( &(leds[0]), NUM_LEDS /*led count*/, hue /*starting hue*/);
    FastLED.show();
    delay(1);
  }
}

void water() {
  FastLED.clear();
  uint32_t color = 0x3737FC;
  int x = 0;
  int x1 = 0;
  int dy = 0;
  for (int i = 0; i < 49; i++) {
    delay(1);
    x = random(WIDTH);
    x1 = random(WIDTH);
    while (x1 == x) x1 = random(WIDTH);
    dy = random(5);
    for (int y = -3; y < HEIGHT + 3; y++) {
      FastLED.show();
      setPix(x, y - 2, color);
      setPix(x1, y - 2 + dy, color);
      FastLED.show();
      setPix(x, y - 1, color);
      setPix(x1, y - 1 + dy, color);
      FastLED.show();
      setPix(x, y, color);
      setPix(x1, y + dy, color);
      FastLED.show();
      if (y - 3 < HEIGHT - i / 7) {
        setPix(x, y - 3, 0);
      }
      if (y - 3 + dy < HEIGHT - i / 7) {
        setPix(x1, y - 3 + dy, 0);
      }
    }
    if (i % 7 == 0) {
      for (int xx = 0; xx < WIDTH; xx++) {
        setPix(xx, HEIGHT - i / 7, color);
      }
    }
  }
}

void powerOff() {
  FastLED.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = 0xFFFFFF;
  }
  FastLED.show();
  delay(500);
  for (int pos = 0; pos < 4; pos++) {
    for (int x = pos; x < WIDTH - pos; x++) {
      setPix(x, pos, 0);
      setPix(x, HEIGHT - 1 - pos, 0);
    }
    for (int y = pos; y < HEIGHT - pos; y++) {
      setPix(pos, y, 0);
      setPix(WIDTH - 1 - pos, y, 0);
    }
    FastLED.show();
    delay(250);
  }
}

void createChar(char c, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {
  charset[c - 32][0] = b0;
  charset[c - 32][1] = b1;
  charset[c - 32][2] = b2;
  charset[c - 32][3] = b3;
  charset[c - 32][4] = b4;
}

boolean binValue(uint8_t b, int pos) {
  return (b & (1 << pos)) > 0;
}

//You must use this function to set the pixels since the order is very weird. x and y are taken from the top left corner of the display.
void setPix(int x, int y, uint32_t color) {
  if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
    return;
  int i = (HEIGHT - 1 - y) * WIDTH + ((y % 2) * ((WIDTH - 1) - 2 * x) + x);
  leds[i] = color;
}

void createAllCharacters() {
  createChar('!', 0, 0, 0x5F, 0, 0);
  createChar('\'', 0, 0x05, 0x03, 0, 0);
  createChar('.', 0, 0x60, 0x60, 0, 0);
  createChar(',', 0, 0x50, 0x30, 0, 0);
  createChar(':', 0, 0x36, 0x36, 0, 0);
  createChar('?', 0x02, 0x01, 0x51, 0x09, 0x06);
  createChar('0', 0x3E, 0x51, 0x49, 0x45, 0x3E);
  createChar('1', 0, 0x42, 0x7F, 0x40, 0);
  createChar('2', 0x42, 0x61, 0x51, 0x49, 0x46);
  createChar('3', 0x41, 0x41, 0x45, 0x4B, 0x31);
  createChar('4', 0x18, 0x14, 0x12, 0x7F, 0x10);
  createChar('5', 0x27, 0x45, 0x45, 0x45, 0x39);
  createChar('6', 0x3C, 0x4A, 0x49, 0x49, 0x30);
  createChar('7', 0x01, 0x01, 0x79, 0x05, 0x03);
  createChar('8', 0x36, 0x49, 0x49, 0x49, 0x36);
  createChar('9', 0x06, 0x49, 0x49, 0x29, 0x1E);
  createChar('A', 0x7E, 0x09, 0x09, 0x09, 0x7E);
  createChar('B', 0x7F, 0x49, 0x49, 0x49, 0x36);
  createChar('C', 0x3E, 0x41, 0x41, 0x41, 0x22);
  createChar('D', 0x7F, 0x41, 0x41, 0x22, 0x1C);
  createChar('E', 0x7F, 0x49, 0x49, 0x49, 0x41);
  createChar('F', 0x7F, 0x09, 0x09, 0x09, 0x01);
  createChar('G', 0x3E, 0x41, 0x49, 0x49, 0x7A);
  createChar('H', 0x7F, 0x08, 0x08, 0x08, 0x7F);
  createChar('I', 0, 0x41, 0x7F, 0x41, 0);
  createChar('J', 0x20, 0x40, 0x41, 0x3F, 0x01);
  createChar('K', 0x7F, 0x08, 0x14, 0x22, 0x41);
  createChar('L', 0x7F, 0x40, 0x40, 0x40, 0x40);
  createChar('M', 0x7F, 0x02, 0x0C, 0x02, 0x7F);
  createChar('N', 0x7F, 0x04, 0x08, 0x10, 0x7F);
  createChar('O', 0x3E, 0x41, 0x41, 0x41, 0x3E);
  createChar('P', 0x7F, 0x09, 0x09, 0x09, 0x06);
  createChar('Q', 0x3E, 0x41, 0x51, 0x21, 0x5E);
  createChar('R', 0x7F, 0x09, 0x19, 0x29, 0x46);
  createChar('S', 0x46, 0x49, 0x49, 0x49, 0x31);
  createChar('T', 0x01, 0x01, 0x7F, 0x01, 0x01);
  createChar('U', 0x3F, 0x40, 0x40, 0x40, 0x3F);
  createChar('V', 0x1F, 0x20, 0x40, 0x20, 0x1F);
  createChar('W', 0x7F, 0x20, 0x18, 0x20, 0x7F);
  createChar('X', 0x63, 0x14, 0x08, 0x14, 0x63);
  createChar('Y', 0x03, 0x04, 0x78, 0x04, 0x03);
  createChar('Z', 0x61, 0x51, 0x49, 0x45, 0x43);
  createChar('%', 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
}

