/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Item {
private:
    std::string name;
    std::string desc;
    int cal;
    float w;

public:
    Item(std::string item_name, std::string description, int calories, float weight);

    std::string get_Name() const;
    float get_Weight() const;
    int get_Calories() const;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif