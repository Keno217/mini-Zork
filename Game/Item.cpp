/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#include "Item.h"
#include <stdexcept>
#include <typeinfo>

// item in the game, can be edible or a tool on the map
// constructor initialization
Item::Item(std::string item_name, std::string description, int calories, float weight) {
    if (item_name.empty() || description.empty() || !(calories >= 0 && calories <= 1000) || 
        !(typeid(calories) == typeid(int)) || !(weight >= 0 && weight <= 500) || 
        !(typeid(weight) == typeid(float))) {
        throw std::invalid_argument("Error: Invalid item_name/description/calories/weight.");
    }

    name = item_name;
    desc = description;
    cal = calories;
    w = weight;
}

// returns the name of item
std::string Item::get_Name() const {
    return name;
}

// returns the weight of item
float Item::get_Weight() const {
    return w;
}

// returns the amount of calories the item has
int Item::get_Calories() const {
    return cal;
}

// overload output stream
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Name: " << item.name << " (Calories: " << item.cal << ") - " << item.w << " lb - " << item.desc;
    return os;
}