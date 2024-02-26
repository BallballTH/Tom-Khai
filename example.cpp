#include "dialogueMaker/dialogueMaker.h"


int main() {
  player kaitom;
  Game::addPlayer(kaitom);
  // Create scenes
  Game::addScene("begin", "You are in [r]a forest[/]. [ul]What do you do?[/]");
  Game::addScene("2", "You see a bear. What do you do?");
  Game::addScene("3", "You see a river. What do you do?");
  Game::addScene("4", "You see a bridge. What do you do?");
  Game::addScene("bad_ending", "You died.", true);
  Game::addScene("nice_ending", "You survived.", true);

  Game::addScene("5", "You are in [r]a forest[/].");

  Game::addScene("6", "You rest for a while. [ul]What do you do?[/]");

  // Create events for specific scenes
  Game::addScene("6event_1", "You are in [r]a special forest[/].");

  // Add events to scene (Example: 6event_1 is a special event for scene 6)
  Game::addEvent("6", "6event_1");

  // Add options to scenes
  Game::addOption("begin", {{"Go left", "2", "event_1","hp - 50"}, {"Go right", "3",}, {"Go straight", "4","","hp - 50"}});

  Game::addOption("2", {
    {"Run", "begin"},
    {"Fight", "bad_ending"},
  });

  Game::addOption("3", {
    {"Swim", "bad_ending"},
    {"Walk around", "begin"},
  });

  Game::addOption("4", {
    {"Cross it", "5"},
    {"Jump off", "bad_ending"}
  });

  // Add option to trigger event (Example: When choose Go to something, it will trigger event 6event_1)
  Game::addOption("5", {
    {"[b]Special?[/]", "6"},
    {"What the ", "3"},
    {"Go to something", "4", "6event_1"},
  });

  Game::addOption("6", {
    {"Go to 5", "5"},
    {"Go to 4", "4"},
  });

  Game::addOption("6event_1", {
    {"Kill Yourself", "bad_ending"},
    {"Gambit", "nice_ending"},
  });

  // Game loop
  Game::runGame("begin");
}

