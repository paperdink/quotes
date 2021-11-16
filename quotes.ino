/* The MIT License (MIT)
 * Copyright (c) 2021 Rohit Gujarathi

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <WiFiClientSecure.h>
#include <SPI.h>
#include <sys/time.h>

#include "config.h"

// E-paper
GxIO_Class io(SPI, /*CS=*/ EPD_CS, /*DC=*/ EPD_DC, /*RST=*/ EPD_RES);
GxEPD_Class display(io, /*RST=*/ EPD_RES, /*BUSY=*/ EPD_BUSY);

#define QUOTE_MARGIN 20
#define FIRST_LINE_MARGIN 55

#define FIRST_LINE_CHARS 34
#define NORMAL_LINE_CHARS 37
#define LINE_HEIGHT_FACTOR 30

char *quote_string = "All action results from thought, so it is thoughts that matter.";
char *author_string = "Sai Baba";

int8_t connect_wifi();
void display_quote(GxEPD_Class* display);
//char quote_string[512];

void setup() {  
  DEBUG.begin(115200);
  DEBUG.println();
  DEBUG.println("paperd.ink");

  pinMode(EPD_EN, OUTPUT);
  pinMode(EPD_RES, OUTPUT);
  pinMode(SD_EN, OUTPUT);
  pinMode(BATT_EN, OUTPUT);
  pinMode(PCF_INT, INPUT); // Required to lower power consumption

  // Power up EPD
  digitalWrite(EPD_EN, LOW);
  digitalWrite(EPD_RES, LOW);
  delay(50);
  digitalWrite(EPD_RES, HIGH);
  delay(50);
  //display.init(115200); // enable diagnostic output on DEBUG
  display.init();
/* 
  if(connect_wifi() == 0){
    configTime(0, 0, "pool.ntp.org");
    if(get_date_dtls(TIME_ZONE) < 0){
      configTime(0, 0, "pool.ntp.org");
    }
  }else{
    get_date_dtls(TIME_ZONE);
  }
*/

  //get_quote();
  display_quote(&display);
  display.update();

  DEBUG.println("Turning off everything");
  digitalWrite(SD_EN, HIGH);
  digitalWrite(BATT_EN, HIGH);
  digitalWrite(EPD_EN, HIGH);
  // Powerdown EPD
  //display.powerDown(); // Dont use this if you require partial updates
  digitalWrite(EPD_RES, LOW);
  delay(50);
  digitalWrite(EPD_RES, HIGH);

  // Sleep till update time.
  //uint64_t sleep_time = (86400/(UPDATES_PER_DAY))-(((now.mil_hour*3600)+(now.min*60)+(now.sec))%(86400/UPDATES_PER_DAY));
  //esp_sleep_enable_timer_wakeup(sleep_time*uS_TO_S_FACTOR);
  //DEBUG.printf("Going to sleep for %lld seconds...", sleep_time);
  // Go to sleep
  //esp_deep_sleep_start();
}

void loop() {
  // put your main code here, to run repeatedly:

}

int32_t get_chars_words(char *string, char *first_line, int32_t char_count){
  int32_t length_count = 0;
  int32_t space_index = 0;
  char *temp = first_line;
  
  while(*string != '\0' && length_count < (char_count-1)){
    length_count++;
    *temp = *string;
    Serial.printf("%c", *string);
    if(*string == ' '){
      Serial.printf("got space\n");
      space_index = length_count;
    }

    temp++;
    string++;
  }

  if(length_count < (char_count-1)){
    space_index = length_count;
  }
  
  first_line[space_index] = '\0';

  Serial.printf("Completed %d\n", space_index);
  return space_index;
}

void display_quote(GxEPD_Class* display){
  int16_t  x, y;
  uint16_t w, h;
  char line[NORMAL_LINE_CHARS];
  uint32_t first_line_chars, num_lines = 0;
  int32_t remaining, completed;

  remaining = strlen(quote_string);
  
  display->setFont(QUOTE_FONT);
  display->setTextColor(GxEPD_BLACK);
  display->setTextSize(1);

  // To get height of the font
  display->getTextBounds(F("A"), 0, 0, &x, &y, &w, &h);
  num_lines = remaining/LINE_HEIGHT_FACTOR;
  display->setCursor(FIRST_LINE_MARGIN, (display->height()-(num_lines*h))/2);

  completed = get_chars_words(quote_string, line, FIRST_LINE_CHARS);
  remaining -= completed;
  display->println(line);

  while(remaining > 0){
    quote_string += completed;
    completed = get_chars_words(quote_string, line, NORMAL_LINE_CHARS);
    remaining -= completed;
    display->getTextBounds(quote_string, 0, 0, &x, &y, &w, &h);
    display->setCursor(QUOTE_MARGIN+display->getCursorX(), display->getCursorY());
    display->println(line);
    Serial.printf("Remaining %d\n", remaining);
  }

  display->setFont(AUTHOR_FONT);
  display->getTextBounds(author_string, 0, 0, &x, &y, &w, &h);
  display->setCursor((display->width()-w)/2, display->getCursorY());
  display->print("-");
  display->println(author_string);
}

int8_t connect_wifi(){
 uint8_t connAttempts = 0;
 WiFi.begin(SSID, PASSWORD);
 while (WiFi.status() != WL_CONNECTED ) {
   delay(500);
   DEBUG.print(".");
   if(connAttempts > 40){
    return -1;
   }
   connAttempts++;
 }
 DEBUG.println("Connected");
 return 0;
}
