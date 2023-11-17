#include "../include/include.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

dialog findDialogByID(const std::vector<dialog>& dialogs, int id) {
    for (const auto& d : dialogs) {
        if (d.id == id) {
            return d;
        }
    }
    // Return an empty dialog if the ID is not found
    return dialog{};
}

std::vector<dialog> parseDialogsFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<dialog> dialogs;

    if (file.is_open()) {
        json jsonData;
        file >> jsonData;

        for (const auto& item : jsonData) {
            dialog d;
            d.id = item["id"];
            d.text = item["Text"];
            d.isChoice = item["isChoice"];
            d.nextA = item["nextA"];
            
            // Check if "nextB" exists in the JSON, otherwise default it to 0
            if (item.find("nextB") != item.end()) {
                d.nextB = item["nextB"];
            } else {
                d.nextB = 0; // Default value
            }
            
            // Check if "nextE" exists in the JSON, otherwise default it to 0
            if (item.find("nextE") != item.end()) {
                d.nextE = item["nextE"];
            } else {
                d.nextE = 0; // Default value
            }

            dialogs.push_back(d);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return dialogs;
}
/*  */