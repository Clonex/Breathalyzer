// #pragma once
#ifndef BASE_H
#define BASE_H

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h>
#include <SPI.h>

#define SENSOR_PIN 35
#define SAMPLE_SIZE 1024 * 10

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

#define GREY 0x8C51 // RGB565
#define OFF_WHITE 0xF79E
#define OFF_BLACK 0xE71C

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS);

int colors[] = {
  0xD129E0, // Pink
  0x30E029,
  0xE0DF29,
  0xE08229, // Orange
  0xE02929, // Red
  0x29C2E0, // Light blue
  0x29E0A1, // Turquieze
  0xE02960, // Red blue
  0x2934E0, // Blue
  0xD129E0, // Purple
};

int selectedBar = 0;
int sideBar[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int graphX = 0;
#endif