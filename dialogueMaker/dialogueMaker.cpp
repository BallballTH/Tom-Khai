#include <iostream>
#include "dialogueMaker.h"

Scene::Scene(std::string id, std::string dialogue, bool isEndScene=false) {
  this->id = id;
  this->dialogue = dialogue;
  this->isEndScene = isEndScene;
}

void Scene::printScene() {
  int sceneLength = dialogue.length();
  /*for (int i = 0; i < sceneLength; i++) {
    std::cout << "-";
  }*/
  std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
  PlaySound::playsoundss("keyboard")
  std::cout << '\n' << dialogue << '\n';
  PlaySound::StopPlay();
  std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
  /*for (int i = 0; i < sceneLength; i++) {
    std::cout << "-";
  }*/
  if (options.size() > 0) {
    std::cout << "\n\n";
  }
  for (int i = 0; i < options.size(); i++) {
    std::cout << i+1 << ". " << options[i].text << '\n';
  }
  std::cout << "\n";
}

void Scene::addOption(std::string text, std::string nextSceneId) {
  Option option;
  option.text = text;
  option.sceneId = nextSceneId;
  options.push_back(option);
}

std::string Scene::chooseOption(int choice) {
  return options[choice-1].sceneId;
}

std::string Scene::getId() {
  return id;
}

std::string Scene::getDialogue() {
  return dialogue;
}

int Scene::getNumOptions() {
  return options.size();
}

bool Scene::getIsEndScene() {
  return isEndScene;
}

void Game::addScene(std::string id, std::string dialogue, bool isEndScene) {
  Scene* scene = new Scene(id, Game::parseText(dialogue), isEndScene);
  Game::scenes[id] = scene;
}

void Game::addOption(std::string sceneId, std::vector<Option> options) {
  checkIfSceneExists(sceneId);
  for (int i = 0; i < options.size(); i++) {
    checkIfSceneExists(options[i].sceneId);
    Game::scenes[sceneId]->addOption(options[i].text, options[i].sceneId);
  }
}

void Game::start(std::string startSceneId) {
  Game::currentScene = Game::scenes[startSceneId];
}

void Game::setCurrentScene(std::string id) {
  Game::currentScene = Game::scenes[id];
}

void Game::printCurrentScene() {
  std::cout << "\033[2J\033[1;1H";
  Game::currentScene->printScene();
}

void Game::askForChoice() {
  while (1) {
    std::string choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    int choiceInt;
    try {
      choiceInt = stoi(choice);
    } catch (std::invalid_argument e) {
      std::cout << "Invalid choice." << '\n';
      continue;
    }

    if (choiceInt > 0 && choiceInt <= Game::currentScene->getNumOptions()) {
      std::string nextSceneId = Game::currentScene->chooseOption(choiceInt);
      PlaySound::playsoundss(nextSceneId);
      setCurrentScene(nextSceneId);
      break;
    } else {
      std::cout << "Invalid choice." << '\n';
    }
  }
}

void Game::cleanUp() {
  for (auto it = Game::scenes.begin(); it != Game::scenes.end(); it++) {
    delete it->second;
  }
  Game::scenes.clear();
  Game::currentScene = NULL;
}

bool Game::gameEnded() {
  if (Game::currentScene->getIsEndScene()) {
    Game::printCurrentScene();
    cleanUp();
    return true;
  }
  return false;
}

void Game::printAllScenes() {
  for (auto it = Game::scenes.begin(); it != Game::scenes.end(); it++) {
    std::cout << it->first << ": " << it->second->getDialogue() << '\n';
  }
}

void Game::runGame(std::string startSceneId) {
  checkIfSceneExists(startSceneId);
  start(startSceneId);
  while (!gameEnded()) { 
    printCurrentScene();
    askForChoice();
  }
}

void Game::checkIfSceneExists(std::string sceneId) {
  if (Game::scenes.find(sceneId) == Game::scenes.end()) {
    std::cout << "Scene with id \"" << sceneId << "\" does not exist." << '\n';
    cleanUp();
    exit(0);
  }
}

std::string Game::parseText(std::string text) {
  std::map<std::string, std::string> decorations = {
    {"b", "\033[1m"}, // Bold
    {"ul", "\033[4m"}, // Underline
    {"r", "\033[31m"}, // Red
    {"g", "\033[32m"}, // Green
    {"y", "\033[33m"}, // Yellow
    {"random", "\033[38;2;69;211;76m"}, // rgb(69, 211, 76)
  };
  std::vector<std::string> tags;
  std::string parsedText = "";
  std::string currentTag = "";

  for (int i = 0; i < text.size(); i++) {
    if (text[i] == '[') {
      i++;
      while (text[i] != ']') {
        currentTag += text[i];
        i++;
      }
      if (currentTag == "/") {
        tags.pop_back();
        parsedText += "\033[m";
        for (int i = 0; i < tags.size(); i++) {
          parsedText += decorations[tags[i]];
        }
      } else {
        tags.push_back(currentTag);
        parsedText += decorations[currentTag];
      }
      currentTag = "";
    } else {
      parsedText += text[i];
    }
  }

  for (int i = 0; i < tags.size(); i++) {
    parsedText += "\033[m";
  }
  return parsedText;
}


void Game::playersound(){

}