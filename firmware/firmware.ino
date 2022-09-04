#include "base.h"
#include <WiFi.h>

void setup(void)
{
    WiFi.setSleep(true);
    // analogReadResolution(1);

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
int data[SAMPLE_SIZE] = {0};

void loop()
{
    int value = analogRead(SENSOR_PIN);
    if(measuring)
    {
        data[dLength] = value;
        dLength++;
        if(dLength >= (SAMPLE_SIZE - 1))
        {
            measuring = false;
            scores[selectedPlayer] = getScore(0.1);
            Serial.print("Score: ");
            Serial.println(scores[selectedPlayer]);
            dLength = 0;
        }
    }

    if(btnPressed(BTN_UP))
    {
        Serial.println("UP pressed..");
        selectedPlayer = (selectedPlayer + 1) % colorAmount;
    }

    if(btnPressed(BTN_MID))
    {
        Serial.println("MID pressed..");
    }

    if(btnPressed(BTN_DOWN))
    {
        Serial.println("DOWN pressed..");
        showCounter();
        measuring = true;
    }

    if(dLength >= SAMPLE_SIZE)
    {
        int score = getScore(0.1);
        Serial.print("Score: ");
        Serial.println(score);
        dLength = 0;
    }

    int y = map(value, 0, 4095, 0, tft.height() - 50) + 25;
    drawPoint(graphX, y);
    graphX = (graphX + 1) % tft.width();
    drawScoreLines();
    btnTick();
    animationTick();
}