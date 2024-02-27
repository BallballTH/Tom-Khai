#include <map>
#include <vector>
#include <string>
#include "../Sound/sound.cpp"

struct Option {
  std::string text;
  std::string sceneId;
};

class Scene {
  std::string id;
  std::string dialogue;
  bool isEndScene;
  std::vector<Option> options;

  Scene(std::string id, std::string dialogue, bool isEndScene);

  void printScene(); 

  void addOption(std::string text, std::string nextSceneId);

  std::string chooseOption(int choice);

  std::string getId();

  std::string getDialogue();

  int getNumOptions();

  bool getIsEndScene();

  friend class Game;
};

class Game {
  static inline std::map<std::string, Scene*> scenes;
  static inline Scene* currentScene;

  static void setCurrentScene(std::string id);
  static void cleanUp();
  static void checkIfSceneExists(std::string id);
  static void askForChoice();
  static void start(std::string startSceneId);
  static bool gameEnded();
  static void printCurrentScene();
  static std::string parseText(std::string text);

  static void Playsound();

  public:
    static void addScene(std::string id, std::string dialogue, bool isEndScene=false);

    static void addOption(std::string sceneId, std::vector<Option> options);

    static void printAllScenes();

    static void runGame(std::string startSceneId);
};

