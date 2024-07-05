#pragma once
#include "FlashMemoryDevice.h"
#include <stdexcept>

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    int CheckSameValue(long address);
    bool IsAbleToWrite(long address);

protected:
    FlashMemoryDevice* m_hardware;

private:
    const int READ_RETRY_CNT = 4;
};

class ReadFailException : public std::exception
{
public:
    char const* what() const override
    {
        return "read fail!!!";
    }
};

class WriteFailException : public std::exception
{
public:
    char const* what() const override
    {
        return "write fail!!!";
    }
};