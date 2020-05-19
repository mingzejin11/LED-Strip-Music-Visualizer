/*
Mingze Jin LED-Audio Spectrum
Only thing that needs to be adjusted is the "num_leds" in this sketch to how many LEDs you are using
*/

#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define num_leds 300
#define pin 6

CRGB leds[num_leds];
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, pin, GRB>(leds, num_leds);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();  // Clear any old data displayed on the LCD
}

void loop() {
  int brightness = (analogRead(2) * 0.24);
  int sensitivity = (analogRead(3) * 0.009);
  
  lcd.setCursor(0, 0);
  lcd.print("Brightness:  ");
  if (round(analogRead(2) * 0.09775171) < 10) {
    lcd.setCursor(14, 0);
  } else {
    lcd.setCursor(13, 0);
  }
  lcd.print(round(analogRead(2) * 0.09775171));
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Sensitivity: ");
  if (round(analogRead(3) * 0.09775171) < 10) {
    lcd.setCursor(14, 1);
  } else {
    lcd.setCursor(13, 1);
  }
  lcd.print(round(analogRead(3) * 0.09775171));
  lcd.print("%");
  
  int x = analogRead(0);
  x = x * sensitivity;
  int y = analogRead(1);
  int d;
//  if (x < 71) {
//    Serial.println("");
//  } else if (x > 71 && x <= 142) {
//    Serial.println("11");
//  } else if (x > 142 && x <= 213) {
//    Serial.println("1111");
//  } else if (x > 213 && x <= 284) {
//    Serial.println("111111");
//  } else if (x > 284 && x <= 355) {
//    Serial.println("11111111");
//  } else if (x > 355 && x <= 426) {
//    Serial.println("1111111111");
//  } else {
//    Serial.println("111111111111");
//  }
  
  int c = 0;
  FastLED.setBrightness(brightness);
  if (y < 100) {
    if (x < 71) {
      leds[(num_leds / 2)] = CRGB(255, 0, 0);
    }
    else if (x > 71 && x <= 142) {
      leds[(num_leds / 2)] = CRGB(255, 154, 0);
    }
    else if (x > 142 && x <= 213) {
      leds[(num_leds / 2)] = CRGB(255, 255, 0);
    }
    else if (x > 213 && x <= 284) {
      leds[(num_leds / 2)] = CRGB(0, 255, 0);
    }
    else if (x > 284 && x <= 355) {
      leds[(num_leds / 2)] = CRGB(0, 0, 255);
    }
    else if (x > 355 && x <= 426) {
      leds[(num_leds / 2)] = CRGB(150, 102, 255);
    }
    else {
      leds[(num_leds / 2)] = CRGB(255, 0, 255);
    }
  }
  else if (y > 100 && y <= 1000) {
    if (y >= 100 && y < 250) { // 2nd up
      c = ((y - 100) * (255 / 150));
      leds[(num_leds / 2)] = CRGB(255, c, 0);
    }
    else if (y >= 250 && y < 400) { // 1st down
      c = ((y - 400) * (-255 / 150));
      leds[(num_leds / 2)] = CRGB(c, 255, 0);
    }
    else if (y >= 400 && y < 550) { // 3rd up
      c = ((y - 400) * (255 / 150));
      leds[(num_leds / 2)] = CRGB(0, 255, c);
    }
    else if (y >= 550 && y < 700) { // 2nd down
      c = ((y - 700) * (-255 / 150));
      leds[(num_leds / 2)] = CRGB(0, c, 255);
    }
    else if (y >= 700 && y < 850) { // 1st up
      c = ((y - 700) * (255 / 150));
      leds[(num_leds / 2)] = CRGB(c, 0, 255);
    }
    else if (y >= 850 && y < 1000) { // 3rd down
      c = ((y - 1000) * (-255 / 150));
      leds[(num_leds / 2)] = CRGB(255, 0, c);
    }
    else {
      leds[(num_leds / 2)] = CRGB(255, 0, 0);
    }
  }
  else {
    int a = y;
    int d;
    while (y > 1000) {
      y = analogRead(1);
      if (a >= 100 && a < 250) { // 2nd up
        d = ((a - 100) * (255 / 150));
        leds[(num_leds / 2)] = CRGB(255, d, 0);
      }
      else if (a >= 250 && a < 400) { // 1st down
        d = ((a - 400) * (-255 / 150));
        leds[(num_leds / 2)] = CRGB(d, 255, 0);
      }
      else if (a >= 400 && a < 550) { // 3rd up
        d = ((a - 400) * (255 / 150));
        leds[(num_leds / 2)] = CRGB(0, 255, d);
      }
      else if (a >= 550 && a < 700) { // 2nd down
        d = ((a - 700) * (-255 / 150));
        leds[(num_leds / 2)] = CRGB(0, d, 255);
      }
      else if (a >= 700 && a < 850) { // 1st up
        d = ((a - 700) * (255 / 150));
        leds[(num_leds / 2)] = CRGB(d, 0, 255);
      }
      else if (a >= 850 && a < 1000) { // 3rd down
        d = ((a - 1000) * (-255 / 150));
        leds[(num_leds / 2)] = CRGB(255, 0, d);
      }
      else {
        leds[(num_leds / 2)] = CRGB(255, 0, 0);
      }
      FastLED.show();
      delay(60);
      fill_solid(leds, num_leds, leds[(num_leds / 2)]);
      a = a + 1;
      if (a > 1023) {
        a = 0;
      }
    }
  }
  FastLED.show();
  delay(10);
  for (int z = num_leds; z > (num_leds / 2); z --) {
    leds[z] = leds[z - 1];
  }
  for (int z = 0; z < (num_leds / 2); z ++) {
    leds[z] = leds[z + 1];
  }
}
