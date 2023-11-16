#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <sstream>
#include <fstream>
#include <regex>

#include "dialogs.hpp"

std::vector<dialog> parseDialogsFromFile(const std::string& filePath);
dialog findDialogByID(const std::vector<dialog>& dialogs, int id);
