#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

void importOptionsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string sceneId, text, nextSceneId, event;
        std::getline(iss, sceneId, '|');
        std::getline(iss, text, '|');
        std::getline(iss, nextSceneId, '|');
        std::getline(iss, event);
        // Add option to the scene
        Game::addOption(sceneId, {{text, nextSceneId, event}});
    }

    file.close();
}