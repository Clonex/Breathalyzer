#include "base.h"

void drawSidebar()
{
    
}

void drawPoint(int x, int y)
{
    // tft.drawLine(x, 0, x, tft.height(), WHITE);
    // tft.drawLine(x + 1, 0, x + 1, tft.height(), WHITE);
    drawChartLine(x);

    tft.drawPixel(x, y, RED);
}

void drawChartBackground()
{
    tft.drawRect(0, 0, GRAPH_SIZE, DISPLAY_HEIGHT, OFF_WHITE);
    for(int x = 0; x < tft.width(); x++)
    {
        drawChartLine(x);
    }
}

void drawChartLine(int x)
{
    int unitSizeY = DISPLAY_HEIGHT / 100;

    if((x % (DISPLAY_WIDTH / 10)) == 0)
    {
        tft.drawRect(x, 0, x, DISPLAY_HEIGHT, OFF_BLACK);
    }else{
        for(int y = 0; y <= 110; y += 10)
        {
            int yPos = y * unitSizeY;
            tft.drawPixel(x, yPos, OFF_BLACK);
        }
    }
}


void drawText(char *text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}