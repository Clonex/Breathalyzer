#include "base.h"

void setup(void)
{
    Serial.begin(9600);

    tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft.setRotation(1);
    tft.invertDisplay(false);
    tft.fillScreen(WHITE);
}

void loop()
{
    int value = 500;//analogRead(SENSOR_PIN);
    Serial.println(value);
    int y = map(value, 0, 1023, 0, tft.height());
    drawPoint(graphX, y);
    graphX = (graphX + 1) % tft.width();
}