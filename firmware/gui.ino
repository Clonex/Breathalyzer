#include "base.h"

void drawSidebar()
{
    
}

void drawPoint(int x, int y)
{
    tft.drawLine(x, 0, x, tft.height(), WHITE);
    tft.drawLine(x + 1, 0, x + 1, tft.height(), WHITE);

    tft.drawPixel(x, y, RED);
    // tft.drawPixel(x + 1, y, GREY);
    // tft.drawPixel(x, y + 1, GREY);
    // tft.drawPixel(x, y - 1, GREY);
}