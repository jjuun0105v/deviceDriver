#include "DeviceDriver.h"
#include <iostream>
#include <stdexcept>
using namespace std;


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::CheckSameValue(long address)
{
    int first_Value = (int)(m_hardware->read(address));

    for (int i = 0; i < READ_RETRY_CNT; i++)
    {
        int read_value = (int)(m_hardware->read(address));
        if (first_Value != read_value) throw ReadFailException();
    }

    return first_Value;
}

int DeviceDriver::read(long address)
{
    int value = CheckSameValue(address);
    return value;
}

bool DeviceDriver::IsAbleToWrite(long address)
{
    if (0xFF == (int)(m_hardware->read(address)))
    {
        return true;
    }

    return false;
}

void DeviceDriver::write(long address, int data)
{
    if (true == IsAbleToWrite(address))
    {
        m_hardware->write(address, (unsigned char)data);
        return;
    }
    else
    {
        throw WriteFailException();
    }

}