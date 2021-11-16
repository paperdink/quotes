
#ifndef CONFIG_H
#define CONFIG_H

#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "Roboto_Regular_12pt7b.h"
#include "Gobold_Thin9pt7b.h"

// DETAILS TO EDIT
#define SSID     "wire" // your network SSID (name of wifi network)
#define PASSWORD "avrmicro!2" // your network password
#define OWM_ID "6f08bcf115cc4d5ee1c5b4967a1d6279"
#define TIME_ZONE "+07:00"
#define UPDATES_PER_DAY 1
// Number of times to update starting 12am
// 1 = Updates every 24 hours 
// 2 = Updates every 12 hours
// 3 = Updates every 8 hours. Not a good idea since it won't line up with day changes.
// 4 = Updates every 6 hours
// ... and so on
// Higher number means lower battery life

#define MAX_QUOTE_LENGTH 512
#define MAX_AUTHOR_LENGTH 128

#define QUOTE_MARGIN 20
#define FIRST_LINE_MARGIN 55

#define FIRST_LINE_CHARS 34
#define NORMAL_LINE_CHARS 37
#define LINE_HEIGHT_FACTOR 30

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
