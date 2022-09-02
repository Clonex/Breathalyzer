// #pragma once
#ifndef BASE_H
#define BASE_H

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h>
#include <SPI.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#define SIDEBAR_MAX 7
#define SIDEBAR_SIZE 75
#define SIDEBAR_MARGIN (DISPLAY_HEIGHT / SIDEBAR_MAX)

#define GRAPH_SIZE (DISPLAY_WIDTH - SIDEBAR_SIZE)

#define TFT_MISO -1
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST   17  // Reset pin (could connect to RST pin)

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS);

int colors[][3] = {
  {209, 41, 224}, // Pink
  {48, 224, 41},
  {224, 223, 41},
  {224, 130, 41}, // Orange
  {224, 41, 41}, // Red
  {41, 194, 224}, // Light blue
  {41, 224, 161}, // Turquieze
  {224, 41, 96}, // Red blue
  {41, 52, 224}, // Blue
  {209, 41, 224}, // Purple
};

int selectedBar = 0;
int sideBar[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int graphX = 0;
#endif