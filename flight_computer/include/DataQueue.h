#pragma once
#include "SensorData.h"


class DataQueue
{
private:
    /* data */
    int currentStartIndex = 0;
    static const int dataLength = 5;
    struct SensorData data[dataLength];
public:
    DataQueue();

    int setInsideArrayBounds(int index);

    void addData(struct SensorData _data);

    struct SensorData GetData(int index);

    int GetDataLength();
};



