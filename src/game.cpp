#include "../include/include.hpp"

int main() {
    std::cout << "Welcome, player!\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    if (firstMission()) {
        std::cout << "Congratulations for beating the game!" << std::endl;
    } else {
        std::cout << "Wow, you are really bad at this game!" << std::endl;
    }

    return 0;
}