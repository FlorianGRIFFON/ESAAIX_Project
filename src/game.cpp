#include "../include/include.hpp"

void drawTextOnDialog(sf::RenderWindow& window, sf::Font& font, const std::string& text) {
    sf::Text dialogText;
    dialogText.setFont(font);
    dialogText.setCharacterSize(20);
    dialogText.setFillColor(sf::Color::White);

    std::string displayedText = "";

    // Position the text inside the dialog box
    dialogText.setPosition(55.f, 455.f);

    for (size_t i = 0; i <= text.size(); ++i) {
        displayedText = text.substr(0, i);
        dialogText.setString(displayedText);

        window.draw(dialogText);
        window.display();

        // Adjust the speed at which the characters are displayed (you can modify this value)
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}

// Function to reset the window and draw shapes
void resetWindow(sf::RenderWindow& window, std::vector<sf::RectangleShape>& toDraw) {
    window.clear();

    for (auto& rect : toDraw) {
        window.draw(rect);
    }

    window.display();
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "Usage: ./program_name file_path" << std::endl;
        return 1;
    }

    std::string filePath = av[1];
    std::vector<dialog> vectorDialogs = parseDialogsFromFile(filePath);

    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game Example");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("ressources/arial.ttf")) {
        std::cout << "Font file not found!" << std::endl;
        return -1;
    }

    // Initialize shapes for drawing
    sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setFillColor(sf::Color(230, 180, 175));
    background.setPosition(0.f, 0.f);

    sf::RectangleShape dialogBox(sf::Vector2f(700.f, 140.f));
    dialogBox.setFillColor(sf::Color::Black);
    dialogBox.setPosition(50.f, 450.f);

    sf::RectangleShape border(sf::Vector2f(704.f, 144.f));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2.f);
    border.setOutlineColor(sf::Color::White);
    border.setPosition(48.f, 448.f);

    std::vector<sf::RectangleShape> toDraw;
    toDraw.push_back(background);
    toDraw.push_back(dialogBox);
    toDraw.push_back(border);

    // Variable to store the user's choice
    int currentId = 0;

    resetWindow(window, toDraw);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return 0;
                }
            }
        }

        // If there are texts in the vector to display
        if (!vectorDialogs.empty()) {
            dialog currentDialog = findDialogByID(vectorDialogs, currentId);
            
            drawTextOnDialog(window, font, currentDialog.text);

            bool proceedToNextText = false;

            // Wait for spacebar input to proceed to the next text
            while (!proceedToNextText) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (currentDialog.isChoice) {
                            if (event.key.code == sf::Keyboard::Escape) {
                                window.close();
                                return 0;
                            }   else if (event.key.code == sf::Keyboard::A) {
                                proceedToNextText = true;
                                currentId = currentDialog.nextA;
                            } else if (event.key.code == sf::Keyboard::B) {
                                proceedToNextText = true;
                                currentId = currentDialog.nextB;
                            } else if (event.key.code == sf::Keyboard::E) {
                                proceedToNextText = true;
                                currentId = currentDialog.nextE;
                            }
                        } else if (event.key.code == sf::Keyboard::Space) {
                            proceedToNextText = true;
                            currentId = currentDialog.nextA;
                        }
                    }
                }
            }
            
            resetWindow(window, toDraw);
        }
    }

    return 0;
}