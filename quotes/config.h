
#ifndef CONFIG_H
#define CONFIG_H

#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Roboto_Regular_12pt7b.h"
#include "Gobold_Thin9pt7b.h"

// DETAILS TO EDIT
#define SSID     "*****" // your network SSID (name of wifi network)
#define PASSWORD "*****" // your network password
#define TIME_ZONE "+07:00" // Your time zone. Daylight saving not handled yet.
#define UPDATES_PER_DAY 1
// Number of times to update starting 12am
// 1 = Updates every 24 hours 
// 2 = Updates every 12 hours
// 3 = Updates every 8 hours. Not a good idea since it won't line up with day changes.
// 4 = Updates every 6 hours
// ... and so on
// Higher number means lower battery life

#define QUOTE_TAGS ""          // Comma separated quote tags. see https://api.quotable.io/tags
#define MAX_QUOTE_LENGTH 256   // Maximum characters in a quote
#define MAX_AUTHOR_LENGTH 128  // Maximum characters in a author

#define FIRST_LINE_MARGIN 55   // Margin to leave on the left for the first line (in pixels)
#define QUOTE_MARGIN_LEFT 18   // Margin to leave on the left of the quote 2nd line onwards (in pixels)
#define QUOTE_MARGIN_RIGHT 18  // Margin to leave on the right of the quote (in pixels)

#define EXPECTED_LINE_CHARS 40 // Maximum expected characters in a line
#define LINE_HEIGHT_FACTOR 30  // Dividing string length with this to get number of lines

#define DEBUG Serial

// PIN ASSIGNMENT

// I2C pins
#define SDA 16
#define SCL 17

// SPI pins

// SD card pins
#define SD_CS 21
#define SD_EN 5

// E-paper pins
#define EPD_CS 22
#define EPD_DC 15
#define EPD_BUSY 34
#define EPD_EN 12
#define EPD_RES 13

// PCF8574 pins
#define PCF_INT 35
#define SD_CD P4 // input
#define EXT_GPIO1 P5
#define EXT_GPIO2 P6
#define EXT_GPIO3 P7
#define PCF_I2C_ADDR 0x20

// LiPo
#define CHARGING_PIN 36
#define BATT_EN 25
#define BATTERY_VOLTAGE 34

// Fonts
#define QUOTE_FONT &Roboto_Regular12pt7b
#define AUTHOR_FONT &Gobold_Thin9pt7b

#endif /* CONFIG_H */
