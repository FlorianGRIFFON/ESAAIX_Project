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
            d.nextB = item["nextB"];
            d.nextE = item["nextE"];

            dialogs.push_back(d);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return dialogs;
}