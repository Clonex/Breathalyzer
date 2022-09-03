#include "base.h"

/**
 * Get average score, without counting the given top and bottom percentage. 
 **/
int getScore(float cutOffPercent)
{
    int ret = 0;
    insertionSort(data, SAMPLE_SIZE);

    int margin = SAMPLE_SIZE * cutOffPercent;
    int size = 0;
    for(int i = margin; i < (SAMPLE_SIZE - margin); i++)
    {
        if(data[i] > 0)
        {
            ret += data[i];
            size++;
        }
    }

    // Reset
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        data[i] = 0;
    }

    return ret / size;
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