#pragma once

#include "../Player/player.h"
#include "../Sound/sound.h"
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>      // for file streams
#include <sstream>      // for string stream

struct Option {
  std::string text;
  std::string sceneId;
  std::string statchange;
  std::string event;
};

class Scene {
  std::string id;
  std::string dialogue;
  bool isEndScene;
  std::vector<Option> options;
  std::set<std::string> events;

  Scene(std::string id, std::string dialogue, bool isEndScene=false);

  void printScene(); 

  void addOption(std::string text, std::string nextSceneId, std::string statchange, std::string event);

  void addEvent(std::string event);

  std::pair<std::string, std::string> chooseOption(int choice);

  std::string getId();

  std::string getDialogue();

  int getNumOptions();

  bool getIsEndScene();

  bool hasEvent(std::string event);

  friend class Game;

  // Map to store ASCII art for each scene
  static std::map<std::string, std::string> sceneASCII;

  // Add a method to retrieve ASCII art for a scene
  static std::string getSceneASCII(std::string sceneId);
  public:
  // Add a method to set ASCII art for a scene
  static void setSceneASCII(std::string sceneId, std::string ascii);
};

class Game {
  static inline player PlayerP;
  static inline std::map<std::string, Scene*> scenes;
  static inline Scene* currentScene;
  static inline std::set<std::string> currentEvents;

  static void setCurrentScene(std::string id);
  static void cleanUp();
  static void checkIfSceneExists(std::string id);
  static void askForChoice();
  static void start(std::string startSceneId);
  static bool gameEnded();
  static void printCurrentScene();
  static std::string parseText(std::string text);
  static void addCurrentEvent(std::string event);

  friend class Playsound;

  public:
    static void SaveFile(const std::string& filename);

    static void LoadSave(const std::string& filename);

    static void ResetSaveFile(const std::string& filename);

    static void printstats();

    static void addPlayer(player p);

    static void addScene(std::string id, std::string dialogue, bool isEndScene=false);

    static void addEvent(std::string sceneId, std::string event);

    static void addOption(std::string sceneId, std::vector<Option> options);

    static void printAllScenes();

    static void runGame(std::string startSceneId);
};

