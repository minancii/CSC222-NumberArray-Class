#include "NumberArray.h"
#include <iostream>
#include <cmath>
#include <random>
#include <string>

using namespace std;

// Compare a test result with what we expected.
bool checkNumber(string testName, double actual, double expected)
{
    bool passed = fabs(actual - expected) < 0.00001;
    cout << testName << endl;
    cout << "Expected: " << expected << " | Actual: " << actual;
    cout << " | " << (passed ? "PASS" : "FAIL") << endl << endl;
    return passed;
}

int main()
{
    int passed = 0;
    int total = 0;

    cout << "===== NumberArray Class Tests =====" << endl;

    // Test 1: the default constructor creates ten zeros.
    cout << "\nTEST 1 - Default constructor and zeros" << endl;
    NumberArray defaultArray;
    defaultArray.print();
    bool allZeros = true;
    for (int i = 0; i < 10; i++)
    {
        if (defaultArray.getNumber(i) != 0.0)
        {
            allZeros = false;
        }
    }
    total++;
    if (allZeros) passed++;
    cout << "Expected: ten zeros | Actual: " << (allZeros ? "ten zeros" : "other values");
    cout << " | " << (allZeros ? "PASS" : "FAIL") << endl;

    // Test 2: a five-element array with known numbers.
    cout << "\nTEST 2 - Parameterized constructor and valid indexes" << endl;
    NumberArray numbers(5);
    double knownValues[5] = { 4.5, -2.0, 0.0, 8.5, 9.0 };
    for (int i = 0; i < 5; i++)
    {
        numbers.setNumber(i, knownValues[i]);
    }
    numbers.print();

    total++;
    if (checkNumber("First index (0)", numbers.getNumber(0), 4.5)) passed++;
    total++;
    if (checkNumber("Middle index (2)", numbers.getNumber(2), 0.0)) passed++;
    total++;
    if (checkNumber("Last index (4)", numbers.getNumber(4), 9.0)) passed++;

    // Test 3: invalid indexes must not access memory outside the array.
    cout << "TEST 3 - Invalid indexes" << endl;
    numbers.setNumber(-1, 99.0);
    numbers.setNumber(5, 99.0);
    total++;
    if (checkNumber("Invalid getNumber(-1)", numbers.getNumber(-1), 0.0)) passed++;
    total++;
    if (checkNumber("Invalid getNumber(5)", numbers.getNumber(5), 0.0)) passed++;
    total++;
    if (checkNumber("First value still unchanged", numbers.getNumber(0), 4.5)) passed++;
    total++;
    if (checkNumber("Last value still unchanged", numbers.getNumber(4), 9.0)) passed++;

    // Test 4: 4.5 - 2 + 0 + 8.5 + 9 = 20; average is 20 / 5 = 4.
    cout << "TEST 4 - Known data and statistics" << endl;
    total++;
    if (checkNumber("Minimum", numbers.getMin(), -2.0)) passed++;
    total++;
    if (checkNumber("Maximum", numbers.getMax(), 9.0)) passed++;
    total++;
    if (checkNumber("Average", numbers.getAverage(), 4.0)) passed++;

    // Test 5: statistics must update when one number changes.
    cout << "TEST 5 - Recalculate after a change" << endl;
    numbers.setNumber(4, 14.0);
    total++;
    if (checkNumber("New maximum", numbers.getMax(), 14.0)) passed++;
    total++;
    if (checkNumber("New average", numbers.getAverage(), 5.0)) passed++;

    // Test 6: one element with a negative decimal value.
    cout << "TEST 6 - Size one with a negative decimal" << endl;
    NumberArray single(1);
    single.setNumber(0, -3.5);
    single.print();
    total++;
    if (checkNumber("Size-one minimum", single.getMin(), -3.5)) passed++;
    total++;
    if (checkNumber("Size-one maximum", single.getMax(), -3.5)) passed++;
    total++;
    if (checkNumber("Size-one average", single.getAverage(), -3.5)) passed++;

    // Test 7: random values and a separate calculation to check the answers.
    cout << "TEST 7 - Random dataset" << endl;
    NumberArray randomArray(8);
    mt19937 generator(12345);
    uniform_real_distribution<double> distribution(-20.0, 20.0);
    double expectedMin = 0.0;
    double expectedMax = 0.0;
    double sum = 0.0;

    for (int i = 0; i < 8; i++)
    {
        double value = distribution(generator);
        randomArray.setNumber(i, value);
        sum += value;

        if (i == 0 || value < expectedMin) expectedMin = value;
        if (i == 0 || value > expectedMax) expectedMax = value;
    }
    randomArray.print();
    total++;
    if (checkNumber("Random minimum", randomArray.getMin(), expectedMin)) passed++;
    total++;
    if (checkNumber("Random maximum", randomArray.getMax(), expectedMax)) passed++;
    total++;
    if (checkNumber("Random average", randomArray.getAverage(), sum / 8)) passed++;

    bool reasonable = randomArray.getMin() <= randomArray.getAverage()
        && randomArray.getAverage() <= randomArray.getMax();
    total++;
    if (reasonable) passed++;
    cout << "Expected: min <= average <= max | Actual: ";
    cout << (reasonable ? "true" : "false") << " | " << (reasonable ? "PASS" : "FAIL") << endl;

    // Test 8: the destructor runs at the end of a block.
    cout << "\nTEST 8 - Block-scoped destructor" << endl;
    {
        NumberArray temporary(2);
        temporary.setNumber(0, 10.0);
        temporary.setNumber(1, 20.0);
        cout << "Temporary array: ";
        temporary.print();
        cout << "Leaving the block now..." << endl;
    }
    cout << "Destructor message should appear above this line." << endl;

    cout << "\n===== Test Summary =====" << endl;
    cout << "Passed " << passed << " out of " << total << " checks." << endl;
    cout << "More destructor messages will appear when main ends." << endl;

    return (passed == total) ? 0 : 1;
}
