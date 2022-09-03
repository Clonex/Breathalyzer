#include "base.h"

void setup(void)
{
    Serial.begin(9600);

    tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft.setRotation(1);
    tft.invertDisplay(false);
    tft.fillScreen(WHITE);

    drawChartBackground();
}

int dLength = 0;
int data[SAMPLE_SIZE] = {};

void loop()
{
    int value = 500;//analogRead(SENSOR_PIN);
    // Serial.println(value);
    data[dLength] = value;
    dLength++;

    if(dLength >= SAMPLE_SIZE)
    {
        int score = getScore(0.1);
        Serial.print("Score: ");
        Serial.println(score);
        dLength = 0;
    }

    int y = map(value, 0, 1023, 0, tft.height());
    drawPoint(graphX, y);
    graphX = (graphX + 1) % tft.width();
}