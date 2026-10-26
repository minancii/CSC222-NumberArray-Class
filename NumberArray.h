#ifndef NUMBERARRAY_H
#define NUMBERARRAY_H

// NumberArray stores doubles in a dynamically allocated array.
// The object owns its array and frees the memory when it is destroyed.
// Class invariant: size > 0, data points to size double elements,
// and valid indexes are from 0 through size - 1.

class NumberArray
{
private:
    static const int MAX_SIZE = 10;
    int size;
    double* data;

public:
    // Purpose: Allocate an array and initialize every element to 0.0.
    // Input: requestedSize, or MAX_SIZE by default.
    // Preconditions: None; invalid sizes use MAX_SIZE.
    // Postconditions: The object owns an initialized array of size elements.
    // Output: A new NumberArray object.
    NumberArray(int requestedSize = MAX_SIZE);

    // Purpose: Release the array when the object is destroyed.
    // Input: None.
    // Preconditions: The object's lifetime is ending.
    // Postconditions: The owned memory is freed with delete[].
    // Output: A confirmation message.
    ~NumberArray();

    // Purpose: Store a value at a valid index.
    // Input: index and value.
    // Preconditions: None; invalid indexes are ignored safely.
    // Postconditions: A valid index has the new value; other values stay the same.
    // Output: None, except a warning for invalid indexes.
    void setNumber(int index, double value);

    // Purpose: Get a value at a valid index.
    // Input: index.
    // Preconditions: None; invalid indexes are handled safely.
    // Postconditions: The array is unchanged.
    // Output: Stored value, or a static safe default of 0.0.
    double getNumber(int index) const;

    // Purpose: Calculate the smallest current number.
    // Input: None.
    // Preconditions: The array contains at least one element.
    // Postconditions: The array is unchanged.
    // Output: Minimum value.
    double getMin() const;

    // Purpose: Calculate the largest current number.
    // Input: None.
    // Preconditions: The array contains at least one element.
    // Postconditions: The array is unchanged.
    // Output: Maximum value.
    double getMax() const;

    // Purpose: Calculate the current average.
    // Input: None.
    // Preconditions: The array contains at least one element.
    // Postconditions: The array is unchanged.
    // Output: Average value.
    double getAverage() const;

    // Purpose: Display all array values.
    // Input: None.
    // Preconditions: The object has been constructed.
    // Postconditions: The array is unchanged.
    // Output: Values printed to the console.
    void print() const;
};

#endif
