// #pragma once
#ifndef BASE_H
#define BASE_H

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h>
#include <SPI.h>

#define SENSOR_PIN 34
#define SAMPLE_SIZE 1300

#define BTN_UP 39
#define BTN_MID 37
#define BTN_DOWN 38

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#define MAX_PLAYERS 7
#define SIDEBAR_SIZE 75
#define SIDEBAR_MARGIN (DISPLAY_HEIGHT / MAX_PLAYERS)

#define GRAPH_SIZE (DISPLAY_WIDTH - SIDEBAR_SIZE)

#define TFT_MISO -1
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST   17  // Reset pin (could connect to RST pin)

#define GREY 0x8C51 // RGB565
#define OFF_WHITE 0xF79E
#define OFF_BLACK 0xE71C

struct animation;

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS);

int colors[] = {
  0xD15C, // Pink
  0x3705,
  0xE6E5,
  0xE405, // Orange
  0xE145, // Red
  0x2E1C, // Light blue
  0x2F14, // Turquieze
  0xE14C, // Red blue
  0x29BC, // Blue
  0xD15C, // Purple
};
int colorAmount = sizeof(colors) / sizeof(colors[0]);

int selectedPlayer = 0;
int scores[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int graphX = 0;

bool measuring = false;
#endif