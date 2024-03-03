#include "dialogueMaker/dialogueMaker.h"
#include "Dialogue/ImportFile.h"

int main() {
  importScenesFromFile("Dialogue/Dialogues.txt");
  importEventsFromFile("Dialogue/Events.txt");
  importOptionsFromFile("Dialogue/Options.txt");

  // Game loop
  Game::runGame("begin");
}
