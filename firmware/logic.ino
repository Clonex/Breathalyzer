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
    
    // double vibrationVal = (easeOutBounce(progress) * 200) + 50;
    float vibrationVal = 40 + (clickingSine(progress) * 215);
    // float vibrationVal = 40 + (sin(progress * PI) * 215);
    dacWrite(26, vibrationVal);
    
    drawPieSlice(tft.width() / 2, tft.height() / 2, 50, 0xFDA2, 0xF800, lastProgress * 360, progress * 360);
}

void showCounter()
{
    tft.fillCircle(tft.width() / 2, tft.height() / 2, 50, OFF_WHITE);
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

float clickingSine(float x)
{
    int temp = x * 100;
    if(0.4 > x && temp % 2 == 0)
    {
        return 0;
    }else{
        return sin(x * PI);
    }
}

// double easeInOutBounce(double x) {
//     if(x < 0.5)
//     {
//         return (1 - easeOutBounce(1 - 2 * x)) / 2;
//     }else{
//         return (1 + easeOutBounce(2 * x - 1)) / 2;;
//     }
// }

// double easeOutBounce(double x)
// {
//     double n1 = 7.5625;
//     double d1 = 2.75;

//     if (x < 1 / d1) {
//         return n1 * x * x;
//     } else if (x < 2 / d1) {
//         return n1 * (x -= 1.5 / d1) * x + 0.75;
//     } else if (x < 2.5 / d1) {
//         return n1 * (x -= 2.25 / d1) * x + 0.9375;
//     } else {
//         return n1 * (x -= 2.625 / d1) * x + 0.984375;
//     }
// }

// double easeInBounce(double x) {
//     return 1 - easeOutBounce(1 - x);
// }