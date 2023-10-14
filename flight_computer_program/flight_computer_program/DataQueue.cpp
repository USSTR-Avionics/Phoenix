#include "DataQueue.h"
#include "SensorData.h"

DataQueue::DataQueue(/* args */)
{

}

void DataQueue::addData(SensorData _data){
    data[currentStartIndex] = _data;
    currentStartIndex += 1;
    if(currentStartIndex >= dataLength){
        currentStartIndex = 0;
    }
}

SensorData DataQueue::GetData(int index){
    if(index >= 0 && index <= dataLength){
        return data[index];
    }

}

int DataQueue::GetDataLength(){
    return dataLength;
}
