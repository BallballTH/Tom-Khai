#include "dialogueMaker/dialogueMaker.h"
#include "Dialogue/ImportFile.h"
#include "setSceneASCII.h"

int main() {
  importScenesFromFile("Dialogue/Dialogues.txt");
  importEventsFromFile("Dialogue/Events.txt");
  importOptionsFromFile("Dialogue/Options.txt");
  SetASCII();

  // Game loop
  Game::LoadSave("save.txt");
}
