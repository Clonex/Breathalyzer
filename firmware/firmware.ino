#include "base.h"

void setup(void)
{
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_MID, INPUT);
    pinMode(BTN_DOWN, INPUT);

    Serial.begin(9600);

    tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft.setRotation(1);
    tft.invertDisplay(false);
    tft.fillScreen(WHITE);

    drawChartBackground();
    btnTick();
}

int dLength = 0;
int data[SAMPLE_SIZE] = {};

void loop()
{
    int value = 500;//analogRead(SENSOR_PIN);
    // Serial.println(value);
    data[dLength] = value;
    dLength++;

    if(btnPressed(BTN_UP))
    {
        Serial.println("UP pressed..");
    }

    if(btnPressed(BTN_MID))
    {
        Serial.println("MID pressed..");
    }

    if(btnPressed(BTN_DOWN))
    {
        Serial.println("DOWN pressed..");
    }

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
    btnTick();
}