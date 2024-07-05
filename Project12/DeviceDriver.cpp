#include "DeviceDriver.h"
#include <iostream>
#include <stdexcept>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::CheckSameValue(long address)
{
    int value = (int)(m_hardware->read(address));

    for (int i = 0; i < 4; i++)
    {
        if (value == (int)(m_hardware->read(address))) continue;

        throw out_of_range("value is different!!");
    }

    return value;
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int value;
    try
    {
        value = CheckSameValue(address);
        return (int)(m_hardware->read(address));
    }
    catch (out_of_range& e)
    {
        cout << e.what() << endl;//<< " not same value\n";
    }

    return value;
}

bool DeviceDriver::CheckAbleToWrite(long address)
{
    if (0xFF == (int)(m_hardware->read(address)))
    {
        return true;
    }

    return false;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    try
    {
        if (true == CheckAbleToWrite(address))
        {
            m_hardware->write(address, (unsigned char)data);
            return;
        }

        throw invalid_argument("its value has already been written");
    }
    catch (invalid_argument& e)
    {
        cout << e.what() << endl;//<< " not same value\n";
    }
}