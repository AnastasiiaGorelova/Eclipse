// // *** SPFD5408 change -- Begin
// #include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
// #include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
// #include <SPFD5408_TouchScreen.h>
// // *** SPFD5408 change -- End
//
// // I have no idea what is it for
// #if defined(__SAM3X8E__)
//     #undef __FlashStringHelper::F(string_literal)
//     #define F(string_literal) string_literal
// #endif
//
// // Foreward initialization
// void drawBorder ();
// TSPoint waitOneTouch();
//
// #define XM A1  // must be an analog pin, use "An" notation!
// #define YP A2  // must be an analog pin, use "An" notation!
// #define XP 7   // can be a digital pin
// #define YM 6   // can be a digital pin
//
// // Calibrate values
// #define TS_MINX 910
// #define TS_MINY 95
// #define TS_MAXX 130
// #define TS_MAXY 890
//
// TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); // Connect TouchScreen
//
// #define LCD_CS A3
// #define LCD_CD A2
// #define LCD_WR A1
// #define LCD_RD A0
// #define LCD_RESET A4
//
// // Assign human-readable names to some common 16-bit color values:
// #define BLACK   0x0000
// #define BLUE    0x001F
// #define RED     0xF800
// #define GREEN   0x07E0
// #define CYAN    0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW  0xFFE0
// #define WHITE   0xFFFF
//
//
// Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Connect Display
// #define BOXSIZE 40
// #define PENRADIUS 3
// int oldcolor, currentcolor;
//
// void setup(void) {
//
//         Serial.begin(9600);
//
//         Serial.println(F("Paint!"));
//
//         tft.reset();
//
//         tft.begin(0x9341); // SDFP5408
//
//         tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial
//
//         // Border
//
//         drawBorder();
//
//         // Initial screen
//
//         tft.setCursor (55, 50);
//         tft.setTextSize (3);
//         tft.setTextColor(RED);
//         tft.println("SPFD5408");
//         tft.setCursor (65, 85);
//         tft.println("Library");
//         tft.setCursor (55, 150);
//         tft.setTextSize (2);
//         tft.setTextColor(BLACK);
//         tft.println("TFT Paint");
//
//         tft.setCursor (80, 250);
//         tft.setTextSize (1);
//         tft.setTextColor(BLACK);
//         tft.println("Touch to proceed");
//
//         // Wait touch
//
//         waitOneTouch();
//
// // *** SPFD5408 change -- End
//
//         tft.fillScreen(BLACK);
//
//         tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
//         tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
//         tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
//         tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
//         tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
//         tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
//         //tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
//
//         tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
//         currentcolor = GREEN;
//
//         pinMode(13, OUTPUT);
// }
//
// // min pressure we consider valid (0 == no pressing)
// #define MINPRESSURE 1
// #define MAXPRESSURE 1000
//
//
// void loop(){
//
//         digitalWrite(13, HIGH);
//         TSPoint p = ts.getPoint();
//         digitalWrite(13, LOW);
//
//         pinMode(XM, OUTPUT);
//         pinMode(YP, OUTPUT);
//
//         // we have some minimum pressure we consider 'valid'
//         // pressure of 0 means no pressing!
//
//         if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
//
//                    Serial.print("X = "); Serial.print(p.x);
//                    Serial.print("\tY = "); Serial.print(p.y);
//                    Serial.print("\tPressure = "); Serial.println(p.z);
//
//
//                 if (p.y < (TS_MINY-5)) {
//                         Serial.println("erase");
//                         // press the bottom of the screen to erase
//                         tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
//                 }
//                 // scale from 0->1023 to tft.width
//
//                 // *** SPFD5408 change -- Begin
//                 p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
//                 p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());;
//
//                 /*
//                    Serial.print("("); Serial.print(p.x);
//                    Serial.print(", "); Serial.print(p.y);
//                    Serial.println(")");
//                  */
//                 if (p.y < BOXSIZE) {
//                         oldcolor = currentcolor;
//
//                         if (p.x < BOXSIZE) {
//                                 currentcolor = RED;
//                                 tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
//                         } else if (p.x < BOXSIZE*2) {
//                                 currentcolor = YELLOW;
//                                 tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
//                         } else if (p.x < BOXSIZE*3) {
//                                 currentcolor = GREEN;
//                                 tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
//                         } else if (p.x < BOXSIZE*4) {
//                                 currentcolor = CYAN;
//                                 tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
//                         } else if (p.x < BOXSIZE*5) {
//                                 currentcolor = BLUE;
//                                 tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
//                         } else if (p.x < BOXSIZE*6) {
//                                 currentcolor = MAGENTA;
//                                 tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
//                         }
//
//                         if (oldcolor != currentcolor) {
//                                 if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
//                                 if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
//                                 if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
//                                 if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
//                                 if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
//                                 if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
//                         }
//                 }
//                 if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
//                         tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
//                 }
//         }
// }
//
// // Wait one touch
//
// TSPoint waitOneTouch() {
//         // wait 1 touch to exit function
//         TSPoint p;
//         do {
//                 p = ts.getPoint();
//                 pinMode(XM, OUTPUT); //Pins configures again for TFT control
//                 pinMode(YP, OUTPUT);
//         } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
//         return p;
// }
//
//
// void drawBorder () {
//
//         // Draw a border
//
//         uint16_t width = tft.width() - 1;
//         uint16_t height = tft.height() - 1;
//         uint8_t border = 10;
//
//         tft.fillScreen(RED);
//         tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);
//
// }
