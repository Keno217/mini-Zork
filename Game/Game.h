/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <string>
#include "Item.h"
#include "NPC.h"
#include "Location.h"

class Game {
private:
    std::map<std::string, void(Game::*)(std::vector<std::string>)> cmds;
    std::vector<Item> inventory;
    float current_weight;
    std::vector<Location*> locations;
    std::vector<std::string> lore;
    Location* current_location;
    int elf_calories_needed;
    bool in_progress;
    

    std::map<std::string, void(Game::*)(std::vector<std::string>)> setup_commands();
    void create_world();
    Location* random_location();

    void show_Help(std::vector<std::string> args);
    void guide(std::vector<std::string> args);
    void meet(std::vector<std::string> target);
    void go(std::vector<std::string> target);
    void show_items(std::vector<std::string> args);
    void take(std::vector<std::string> target);
    void give(std::vector<std::string> target);
    void talk(std::vector<std::string> target);
    void quest(std::vector<std::string> args);
    void look(std::vector<std::string> args);
    void teleport(std::vector<std::string> target);
    void quit(std::vector<std::string> args);

public:
    Game();
    void play();
};

#endif