#include "base.h"

void setup(void)
{
    tft.init(DISPLAY_HEIGHT, DISPLAY_WIDTH);
    tft.setRotation(0);
    drawSidebar();
}

void loop()
{
    tft.fillScreen(BLACK);
    delay(500);
    tft.fillScreen(WHITE);
    delay(500);
}