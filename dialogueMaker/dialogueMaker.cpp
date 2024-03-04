#include <iostream>
#include "dialogueMaker.h"

Scene::Scene(std::string id, std::string dialogue, bool isEndScene) {
  this->id = id;
  this->dialogue = dialogue;
  this->isEndScene = isEndScene;
}

void Scene::printCharToTerminalWidth(char ch) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int terminal_width = csbi.dwSize.X;

    for (int i = 0; i < terminal_width; ++i) {
        std::cout << ch;
    }
}

void Scene::printScene() {
  // Print ASCII art for the scene
  
  std::string asciiArt = getSceneASCII(id);
  if (!asciiArt.empty()) {
        std::cout << asciiArt << std::endl;
  }
  printCharToTerminalWidth('-');
  //std::cout << "\n\n" << dialogue << "\n\n";
  std::cout << "\n\n";
  for (int i = 0; i < dialogue.size(); i++)
  {
    std::cout << dialogue[i];
    Sleep(1);
  }
  std::cout << "\n\n";
  Sleep(5);
  printCharToTerminalWidth('-');
  std::cout << "\n\n";
  Sleep(5);
  Game::printstats();
  std::cout << "\n\n";
  printCharToTerminalWidth('-');
  if (options.size() > 0) {
    std::cout << "\n\n";
  }
  for (int i = 0; i < options.size(); i++) {
    std::cout << i+1 << ". " << options[i].text << '\n';
  }
  std::cout << "\n";
}

void Scene::addOption(std::string text, std::string nextSceneId, std::string statchange, std::string event) {
  Option option;
  option.text = text;
  option.sceneId = nextSceneId;
  option.statchange = statchange;
  option.event = event;
  options.push_back(option);
}

void Scene::addEvent(std::string event) {
  events.insert(event);
}

std::pair<std::string, std::string> Scene::chooseOption(int choice) {
  return {options[choice-1].sceneId, options[choice-1].event};
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

bool Scene::hasEvent(std::string event) {
  return events.find(event) != events.end();
}

// Define static member variables
std::map<std::string, std::string> Scene::sceneASCII;

// Define static method to set ASCII art for a scene
void Scene::setSceneASCII(std::string sceneId, std::string ascii) {
    sceneASCII[sceneId] = ascii;
}

// Define static method to retrieve ASCII art for a scene
std::string Scene::getSceneASCII(std::string sceneId) {
    if (sceneASCII.find(sceneId) != sceneASCII.end()) {
        return sceneASCII[sceneId];
    }
    return ""; // Return empty string if ASCII art not found
}

void Game::addScene(std::string id, std::string dialogue, bool isEndScene) {
  Scene* scene = new Scene(id, Game::parseText(dialogue), isEndScene);
  Game::scenes[id] = scene;
}

void Game::addEvent(std::string sceneId, std::string event) {
  checkIfSceneExists(sceneId);
  Game::scenes[sceneId]->addEvent(event);
}

void Game::addOption(std::string sceneId, std::vector<Option> options) {
  checkIfSceneExists(sceneId);
  for (int i = 0; i < options.size(); i++) {
    checkIfSceneExists(options[i].sceneId);
    Game::scenes[sceneId]->addOption(parseText(options[i].text), options[i].sceneId, options[i].statchange, options[i].event);
  }
}

void Game::start(std::string startSceneId) {
  Game::currentScene = Game::scenes[startSceneId];
}

void Game::setCurrentScene(std::string id) {
  Game::currentScene = Game::scenes[id];
  for (auto it = Game::currentEvents.begin(); it != Game::currentEvents.end(); it++) {
    if (Game::currentScene->hasEvent(*it)) {
      Game::currentScene = Game::scenes[*it];
    }
  }
}

void Game::printCurrentScene() {
  std::cout << "\033[2J\033[1;1H";
  Game::currentScene->printScene();
}

void Game::addCurrentEvent(std::string event) {
  currentEvents.insert(event);
}

void Game::askForChoice() {
  while (1) {
    std::string choice;
    std::string x = "Enter Your Choice: (q to quit game) (res to restart): ";
    Sleep(10);                                                            //to prevent "E" being shift up
    for (int i = 0; i < x.size(); i++)
    {
      std::cout << x[i];
      Sleep(15);
    }
    
    std::cin >> choice;

    if (choice == "res") {
      Game::ResetSaveFile("Save.txt");
      Game::LoadSave("Save.txt");
    }

    if (choice == "q") {
      std::cout << "Thanks for playing!\n";
      Game::SaveFile("Save.txt");
      cleanUp();
      exit(0);
    }

    int choiceInt;
    try {
      choiceInt = stoi(choice);
    } catch (std::invalid_argument e) {
      std::cout << "Invalid choice." << '\n';
      continue;
    }

    if (choiceInt > 0 && choiceInt <= Game::currentScene->getNumOptions()) {
      std::pair<std::string, std::string> nextScene = Game::currentScene->chooseOption(choiceInt);         // get next scene id
      Playsound::playsoundef(Game::currentScene->options[choiceInt-1].statchange);                         // play soundf if statchange
      PlayerP.changestat(Game::currentScene->options[choiceInt-1].statchange);                             // changestat
      std::string nextSceneId = nextScene.first;  
      std::string event = nextScene.second;
      Game::setCurrentScene(nextSceneId);                                                                  // set new scene
      Game::addCurrentEvent(event);
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
  if (PlayerP.CheckIfdied()) {                 // Change to the "die" scene
    if(PlayerP.hp == 0){               
      setCurrentScene("ending_you_die");       // died by 0 hp           // waiting scenes
    }else if(PlayerP.sanity == 0){
      setCurrentScene("ending_you_die");       // died by 0 sanity
    }
    printCurrentScene();                       // Print the "die" scene
    Game::ResetSaveFile("save.txt");
    cleanUp();
    return true;
  }
  
  if (Game::currentScene->getIsEndScene()) {
    Game::printCurrentScene();
    Game::ResetSaveFile("save.txt");
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
  Playsound::playsoundbg("prologue");                             // start play stater soundbg becuz most of scene dont have soundbg
  checkIfSceneExists(startSceneId);
  start(startSceneId);
  while (!gameEnded()) {
    Playsound::playsoundbg(Game::currentScene->id);               // play soundbg of the current scece if theres any
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
    {"br", "\033[38;2;57;21;0m"}, // brown
    {"bl", "\033[38;2;17;85;204m"}, // blue
    {"bla", "\033[38;2;0;0;0m"}, // black
    {"g", "\033[32m"}, // Green 
    {"dbl", "\033[38;2;25;51;102m"}, // dark blue
    {"dg", "\033[38;2;39;78;19m"}, // dark green
    {"dy", "\033[38;2;191;144;0m"}, // dark yellow
    {"o", "\033[38;2;252;119;53m"}, // orange
    {"p", "\033[38;2;252;119;53m"}, // purple
    {"pbl", "\033[38;2;0;0;255m"}, // purple mixed with blue
    {"r", "\033[38;2;255;0;0m"}, // Red
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

void Game::addPlayer(player p){
  PlayerP = p;
}

void Game::printstats(){
  PlayerP.printstats();
}


void Game::LoadSave(const std::string& filename){
  std::ifstream inFile(filename);                   // Open the file for reading
  if (inFile.is_open()) {
      std::string line;
      std::string tempSceneid;
      std::string tempEvent;
      while (std::getline(inFile, line)) {
          std::istringstream iss(line);
          std::string key;
          if (iss >> key) {
              if (key == "HP:") {
                  iss >> PlayerP.hp;                        // set hp from file to current hp
               } else if (key == "Sanity:") {
                  iss >> PlayerP.sanity;                    // set sanity from file to current sanity
               } else if (key == "Scene:") {
                  iss >> tempSceneid;                       // get tempSceneid 
               } else if (key == "CurrentEvents:"){
                  std::string event;
                  while (iss >> event) {
                    Game::addCurrentEvent(event);           // Add each event to the Game
                  }
               }
          }
       }
       Game::setCurrentScene(tempSceneid);
       Game::runGame(Game::currentScene->getId());
      //  std::cout << "Player data loaded from " << filename << std::endl;
      inFile.close(); // Close the file
   } else {
       std::cerr << "Unable to open file: " << filename << std::endl;
  }
}

void Game::SaveFile(const std::string& filename) {
  std::ofstream outFile(filename);                     // Open the file for writing
  if (outFile.is_open()) {
        // Write player stats to the file
      outFile << "HP: " << PlayerP.hp << "/" << PlayerP.hpmax << std::endl;
      outFile << "Sanity: " << PlayerP.sanity << "/" << PlayerP.sanity_max << std::endl;
      outFile << "Scene: " << Game::currentScene->id << std::endl;
      outFile << "CurrentEvents: ";
      for (const auto& event : Game::currentEvents) {
        outFile << event << ' ';
      }
      std::cout << "\nPlayer data saved to " << filename << std::endl;
      outFile.close(); // Close the file
    } else {
      std::cerr << "Unable to open file: " << filename << std::endl;
  }
}

void Game::ResetSaveFile(const std::string& filename){
  std::ofstream outFile(filename);                     // Open the file for writing
  Game::currentEvents.clear();
  PlayerP.hp = 100;
  PlayerP.sanity = 100;
  if (outFile.is_open()) {
        // Write player stats to the file
      outFile << "HP: " << PlayerP.hp << "/" << PlayerP.hpmax << std::endl;
      outFile << "Sanity: " << PlayerP.sanity << "/" << PlayerP.sanity_max << std::endl;
      outFile << "Scene: " << "prologue" << std::endl;
      outFile << "CurrentEvents: "<< std::endl;
      //  std::cout << "Did Reset data to " << filename << std::endl;
      outFile.close(); // Close the file
    } else {
      std::cerr << "Unable to open file: " << filename << std::endl;
    }  
}