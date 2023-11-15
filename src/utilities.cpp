#include "../include/include.hpp"

int scaninput()
{
    std::string userInput;
    std::getline(std::cin, userInput);

    if (userInput.size() == 1) {
        char key = userInput[0];
        switch (key) {
            case 'A':
            case 'a':
                return 0;
                break;
            case 'B':
            case 'b':
                return 1;
                break;
            case 'E':
            case 'e':
                return 2;
                break;
            default:
                return -1;
                break;
        }
    }
    return -1;
}
