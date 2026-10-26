#include "NumberArray.h"
#include <iostream>

using namespace std;

NumberArray::NumberArray(int requestedSize)
{
    // Use the default size if the input is zero or negative.
    size = (requestedSize > 0) ? requestedSize : MAX_SIZE;
    data = new double[size];

    for (int i = 0; i < size; i++)
    {
        data[i] = 0.0;
    }
}

NumberArray::~NumberArray()
{
    delete[] data;
    data = nullptr;
    cout << "NumberArray destructor: dynamic memory released." << endl;
}

void NumberArray::setNumber(int index, double value)
{
    if (index >= 0 && index < size)
    {
        data[index] = value;
    }
    else
    {
        cout << "Invalid index " << index << ". Number was not changed." << endl;
    }
}

double NumberArray::getNumber(int index) const
{
    // Return this safe static value if the index is invalid.
    static const double SAFE_DEFAULT = 0.0;

    if (index >= 0 && index < size)
    {
        return data[index];
    }

    cout << "Invalid index " << index << ". Returning 0.0." << endl;
    return SAFE_DEFAULT;
}

double NumberArray::getMin() const
{
    double minimum = data[0];

    for (int i = 1; i < size; i++)
    {
        if (data[i] < minimum)
        {
            minimum = data[i];
        }
    }

    return minimum;
}

double NumberArray::getMax() const
{
    double maximum = data[0];

    for (int i = 1; i < size; i++)
    {
        if (data[i] > maximum)
        {
            maximum = data[i];
        }
    }

    return maximum;
}

double NumberArray::getAverage() const
{
    double total = 0.0;

    for (int i = 0; i < size; i++)
    {
        total += data[i];
    }

    return total / size;
}

void NumberArray::print() const
{
    cout << "[";

    for (int i = 0; i < size; i++)
    {
        cout << data[i];
        if (i < size - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}
