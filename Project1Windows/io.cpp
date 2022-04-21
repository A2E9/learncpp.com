#include <iostream>
#include <plog/Log.h>



int funcCall{ 1 };

int readNumber()
{
    PLOGD << "readNumber() called: " << funcCall;
    std::cout << "Number" << funcCall++ << ": ";
    int value{};
    std::cin >> value;
    return value;
}

void writeAnswer(int value)
{
    std::cout << "The answer is: " << value;
}
