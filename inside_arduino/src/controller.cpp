// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
// *** SPFD5408 change -- End


// I have no idea what is it for
#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A2  // A1
#define XM A1  // A2
#define XP 7   // D6
#define YM 6   // D7

// Calibrate values
#define TS_MINX 910
#define TS_MINY 95
#define TS_MAXX 130
#define TS_MAXY 890

#define HALFX 120
#define WIDTH 240
#define HEIGHT 250
#define HALFHEIGHT 125
#define KEY_Q 0x14

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); // Connect TouchScreen

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// min pressure we consider valid (0 == no pressing)
#define MINPRESSURE 1
#define MAXPRESSURE 1000

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Connect Display

void drawBorder () {

        // Draw a border
        uint16_t width = tft.width() - 1;
        uint16_t height = tft.height() - 1;
        uint8_t border = 10;

        tft.fillScreen(CYAN);
        tft.fillRect(border, border, (width - border * 2), (height - border * 2), BLACK);

}

void touched(int start_x, int start_y, int wid, int hei, int color){
    for (int i = 0; i <= 3; i++ ){
      tft.drawRect(start_x+i, start_y+i, wid-2*i, hei-2*i, WHITE);
    }
}

void stop_touch(int start_x, int start_y, int wid, int hei, int color){
    for (int i = 0; i <= 3; i++ ){
      tft.drawRect(start_x+i, start_y+i, wid-2*i, hei-2*i, color);
    }
}

TSPoint waitOneTouch() {
        // wait 1 touch to exit function
        TSPoint p;
        do {
                p = ts.getPoint();
                pinMode(XM, OUTPUT); //Pins configures again for TFT control
                pinMode(YP, OUTPUT);
        } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
        return p;
}

  void change_window(){
    tft.setTextSize (4);
    tft.fillScreen(BLACK);
    tft.fillRect(0, 160, WIDTH, HEIGHT, MAGENTA);
    tft.setCursor(80, 90);
    tft.setTextColor(WHITE);
    tft.print("YES");
    tft.setTextColor(BLACK);
    tft.setCursor(90, 220);
    tft.print("NO");
  }

  void draw_playground(){
    tft.setTextSize (3);
    tft.fillScreen(BLACK);
    tft.fillRect(0, 70, HALFX, HEIGHT, CYAN); // fillRec(startX, startY, ширина, высота)
    tft.fillRect(HALFX, 70, HALFX, HEIGHT, MAGENTA);
    tft.setCursor(85, 30);
    tft.setTextColor(WHITE);
    tft.print("MENU");
    tft.setTextColor(BLACK);
    tft.setCursor(138, 180);
    tft.print("RIGHT");
    tft.setCursor(23, 180);
    tft.print("LEFT");
  }


void setup() {

/// IMPORTANT
        Serial.begin(9600);
        Serial.println("Start!");
        tft.reset();
        tft.begin(0x9341); // SDFP5408
        tft.invertDisplay(true);
        tft.setRotation(2);
        // Keyboard.begin();
///  ENDIMPORTANT

        // Initial screen

        drawBorder();

        tft.setTextColor(WHITE);
        tft.setCursor (34, 70); // setCursor(OX, OY)
        tft.setTextSize (3);
        tft.println("Controller");

        tft.setCursor (103, 120);
        tft.setTextSize (2);
        tft.println("for");

        tft.setCursor (39, 160);
        tft.setTextSize (4);
        tft.setTextColor(MAGENTA);
        tft.println("ECLIPSE");

        tft.setCursor (72, 255);
        tft.setTextSize (1);
        tft.setTextColor(WHITE);
        tft.println("Touch to proceed");

        // Wait touch
        Serial.println("waitOneTouch!");
        waitOneTouch();

        draw_playground();

        pinMode(13, OUTPUT);
}


void loop(){

  Serial.print("NEWLOOP");
  Serial.print("\n");

/// IMPORTANT
        TSPoint p = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
///  ENDIMPORTANT

int FLAG = 0;

while (Serial.available() > 0) {  //если есть доступные данные
    // считываем байт
    char incomingByte = Serial.read();

    // отсылаем то, что получили
    Serial.print("I received: ");
    Serial.println(incomingByte);
    FLAG = 1;
}

if (FLAG == 1){
   change_window();
   TSPoint p = waitOneTouch();
   if(p.y < 450){
     Serial.print("NO");
     Serial.print("\n");
   } else {
     Serial.print("YES");
     Serial.print("\n");
   }
   FLAG = 0;
   draw_playground();
}


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

    /// Вывод данных от экрана в монитор порта
    /*
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    */

    /// нажали на стрелочки
    if (p.y < 700){

      /// нажали направо
      if (p.x < 570){
          Serial.print("RIGHT");
          Serial.print("\n");
          // Keyboard.write(KEY_RIGHT_ARROW);
          touched(HALFX, 70, HALFX, HEIGHT, MAGENTA);
          stop_touch(HALFX, 70, HALFX, HEIGHT, MAGENTA);

      /// нажали налево
      } else {
        Serial.print("LEFT");
        Serial.print("\n");
        // Keyboard.write(KEY_LEFT_ARROW);
        touched(0, 70, HALFX, HEIGHT, CYAN);
        stop_touch(0, 70, HALFX, HEIGHT, CYAN);
      }

    /// нажали на меню
    } else {
      Serial.print("MENU");
      Serial.print("\n");
      // Keyboard.write(KEY_Q);
      touched(0, 0, WIDTH, 70, BLACK);
      stop_touch(0, 0, WIDTH, 70, BLACK);
    }
  }

}
