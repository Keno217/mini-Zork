/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NPC.h"
#include "Item.h"

class Location {
private:
    bool visited;
    std::string name;
    std::string desc;
    std::vector<NPC> npcs;
    std::vector<Item> items;
    std::map<std::string, Location*> neighbors;

public:
    Location(std::string location_name, std::string description);

    std::map<std::string, Location*> get_Location() const;
    void add_Location(std::string direction, Location* location);
    void add_NPC(NPC npc);
    void add_Item(Item item);
    std::string get_Name() const;
    std::vector<NPC>& get_NPCs();
    std::vector<Item>& get_Items();
    void set_Visited();
    bool get_Visited() const;

    friend std::ostream& operator<<(std::ostream& os, const Location& location);
};

#endif