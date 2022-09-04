#include "base.h"

void drawSidebar()
{
    
}

void drawScoreLines()
{
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        int score = scores[i];
        // Serial.println("HUH:");
        // Serial.println(score);
        if(score >= 0)
        {
            // Serial.println("123");
            int color = colors[selectedPlayer];
            int y = 500;//map(score, 0, 4095, 0, tft.height() - 50) + 25;
            int x = tft.width() - graphX;

            tft.drawPixel(x, y, color);
            tft.drawPixel(x, y - 1, GREY);
        }
    }
}

void drawPoint(int x, int y)
{
    int color = colors[selectedPlayer];

    x = tft.width() - x;
    tft.drawLine(x, 0, x, tft.height(), WHITE);
    // tft.drawLine(x + 1, 0, x + 1, tft.height(), WHITE);
    drawChartLine(x);

    tft.drawPixel(x, y, color);
    tft.drawPixel(x, y - 1, GREY);
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