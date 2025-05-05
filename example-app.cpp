#include <iostream>
#include <vector>
#include <cmath>
#include "Example.hpp" // Include the header file for the Example class
#include "Config.h"    // Include the generated config header

static void printVersion()
{
    std::cout << "TemplateProject version: " << APP_VERSION_MAJOR << "."
              << APP_VERSION_MINOR << std::endl;
}

int main()
{
    printVersion();

    constexpr double RAD_TO_PI = 180.0 / M_PI;

    std::cout << "5^(1/2) rad = " << sqrt(5) * RAD_TO_PI << " deg" << std::endl;

    {
        std::vector<Example> objs(3); // vector of size 3

        std::cout << "Number of test objects: " << Example::getObjCnt() << std::endl;

        // Modern C++ for each loop (use with containers):
        for (auto &ob : objs)
        {
            std::cout << "UUID: " << ob.getTag() << "\n";
        }
    }

    std::cout << "Number of test objects: " << Example::getObjCnt() << std::endl;

    return 0;
}
