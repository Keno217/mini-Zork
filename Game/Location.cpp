/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#include "Location.h"
#include <stdexcept>

// the 'room'
// constructor initialization
Location::Location(std::string location_name, std::string description) {
    if (location_name.empty() || description.empty()) {
        throw std::invalid_argument("Error: Invalid location_name/description.");
    }

    name = location_name;
    desc = description;
    visited = false;
}

// returns the 'room' neighbors (where you can traverse)
std::map<std::string, Location*> Location::get_Location() const {
    return neighbors;
}

// adds neighboring 'room' onto the current room
void Location::add_Location(std::string direction, Location* location) {
    if (direction.empty() || neighbors.end() != neighbors.find(direction)) {
        throw std::invalid_argument("Error: Invalid direction input, it's empty/already exists.");
    }

    neighbors.insert({direction, location});
}

// adds npc into the 'room'
void Location::add_NPC(NPC npc) {
    npcs.push_back(npc);
}

// get location name
std::string Location::get_Name() const {
    return name;
}

// returns list of npcs
std::vector<NPC>& Location::get_NPCs() {
    return npcs;
}

// adds item to room
void Location::add_Item(Item item) {
    items.push_back(item);
}

// returns list of items
std::vector<Item>& Location::get_Items() {
    return items;
}

// the room has been entered
void Location::set_Visited() {
    visited = true;
}

// returns if the room has been visited
bool Location::get_Visited() const {
    return visited;
}

// overload output stream
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << " - " << location.desc << "\n\nYou see the following NPCs:\n";
    for (const NPC& npc : location.npcs) {
        os << "- " << npc << "\n";
    }

    os << "\nYou see the following Items:\n";
    for (const Item& item : location.items) {
        os << "- " << item << "\n";
    }

    os << "\nYou can go in the following Directions:\n";
    for (const std::pair<const std::string, Location*>& direction : location.neighbors) {
        std::string tmp = direction.second->visited ? " (Visited)" : "";
        os << "- " << direction.first << " - " << direction.second->name << tmp << "\n";
    }
    return os;
}