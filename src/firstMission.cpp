#include "../include/include.hpp"

bool firstMission()
{
    std::cout << "You encounter a goblin!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "He is very angry at you for some reason, you must defeat it." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Do you wish to use : \n-Fireball (a)\n-Sword (z)" << std::endl;

    int choice = scaninput();

    if (choice == -1) {
        std::cout << "Choose a valid choice!" << std::endl;
        return firstMission();
    } else if (choice == 0) {
        std::cout << "You decide to use a Fireball to strike the Goblin." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "The goblin explode in millions of particles! Damn!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else if (choice == 1) {
        std::cout << "You decide to use your Sword to strike the Goblin." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "You slice and dice the Goblin, he is no match for your strength!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else {
        std::cout << "You can't decide!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "You end up not doing anything at all..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "The goblin rushes at you and kill you in no matter of time, since you are an easy target by not moving..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return true;
}