#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    int CheckSameValue(long address);
    bool CheckAbleToWrite(long address);

protected:
    FlashMemoryDevice* m_hardware;
};
