#pragma once
#include "SensorData.h"


class DataQueue
{
private:
    /* data */
    int currentStartIndex = 0;
    static const int dataLength = 5;
    SensorData data[dataLength];
public:
    DataQueue();

    int setInsideArrayBounds(int index);

    void addData(struct SensorData _data);

    SensorData GetData(int index);

    int GetDataLength();
};



