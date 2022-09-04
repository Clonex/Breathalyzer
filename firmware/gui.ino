#include "base.h"
#define LOADING_RESOLUTION 18

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
    if(!measuring)
    {
        tft.drawLine(x, 0, x, tft.height(), WHITE);
        drawChartLine(x);
    }

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

void drawCircle(double amount, int radius, int innerRadius, int x, int y, int color)
{
    int points = amount * LOADING_RESOLUTION;
    double slice = 2 * PI / LOADING_RESOLUTION;// / points;
    for (int i = 0; i < points; i++)
    {
        double angle = slice * i;
        int newX = (int)(x + radius * cos(angle));
        int newY = (int)(y + radius * sin(angle));
        
        tft.fillCircle(newX, newY, innerRadius, color);
    }
}

void drawPieSlice(int x, int y, int radius, int color, int startAngle, int EndAngle)
{
  for (int i=startAngle; i<EndAngle; i++)
  {
    double radians = i * PI / 180;
    double px = x + radius * cos(radians);
    double py = y + radius * sin(radians);
    tft.drawPixel(px, py, color);
  }
}