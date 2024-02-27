#include "../Player/player.h"
#include <map>
#include <vector>
#include <string>
#include <set>


struct Option {
  std::string text;
  std::string sceneId;
  std::string event;
  std::string statchange;
};

class Scene {
  std::string id;
  std::string dialogue;
  bool isEndScene;
  std::vector<Option> options;
  std::set<std::string> events;

  Scene(std::string id, std::string dialogue, bool isEndScene=false);

  void printScene(); 

  void addOption(std::string text, std::string nextSceneId, std::string event, std::string statchange);

  void addEvent(std::string event);

  std::pair<std::string, std::string> chooseOption(int choice);

  std::string getId();

  std::string getDialogue();

  int getNumOptions();

  bool getIsEndScene();

  bool hasEvent(std::string event);

  friend class Game;
};

class Game {
  static inline player Player;
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

  static void printstats();

  public:

    static void addScene(std::string id, std::string dialogue, bool isEndScene=false);

    static void addEvent(std::string sceneId, std::string event);

    static void addOption(std::string sceneId, std::vector<Option> options);

    static void printAllScenes();

    static void runGame(std::string startSceneId);

    static void addPlayer(player p);
};

