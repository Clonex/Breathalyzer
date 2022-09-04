#include "base.h"

/**
 * Get average score, without counting the given top and bottom percentage. 
 **/
int getScore(float cutOffPercent)
{
    int ret = 0;
    int margin = SAMPLE_SIZE * cutOffPercent;
    int size = 0;
    insertionSort(data, SAMPLE_SIZE);
    
    for(int i = margin; i < (SAMPLE_SIZE - margin); i++)
    {
        int value = data[i];
        if(value > 0)
        {
            ret += value;
            size++;
        }
    }

    // Reset
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        data[i] = 0;
    }

    if(size == 0)
    {
        return 0;
    }

    return ret / size;
}

void timerAnimation(float progress)
{
    float lastProgress = 0;
    if(progress > 0.1)
    {
        lastProgress = progress - 0.1;
    }

    drawPieSlice(tft.width() / 2, tft.height() / 2, 50, 0xFDA2, 0xF800, lastProgress * 360, progress * 360);
}

void showCounter()
{
    Serial.println("showCounter()");
    int x = tft.width() / 2;
    int y = tft.height() / 2;
    tft.fillCircle(x, y, 50, OFF_WHITE);
    Animation(timerAnimation, SAMPLE_SIZE);
}

void insertionSort(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;   
        }
        arr[j + 1] = key;
    }
}

