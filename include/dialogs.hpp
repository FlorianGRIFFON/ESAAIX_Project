#pragma once

#include "include.hpp"

struct dialog {
    int id;
    std::string text;
    bool isChoice;
    int nextA;
    int nextB;
    int nextE;
    std::vector<std::string> imgPath;
    std::vector<float> xPos;
    std::vector<float> yPos;
};
