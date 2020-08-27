#include <iostream>
#include <algorithm>
#include "GFNumber.h"
#include "GField.h"

/**
 * main function
 * @return
 */
int main()
{
    GFNumber a, b;
    std::cin >> a;
    std::cin >> b;
    std::cout << a + b << "\n" << a - b << "\n" << b - a << "\n" << a * b << "\n";
    a.printFactors();
    b.printFactors();
    return 0;
}

