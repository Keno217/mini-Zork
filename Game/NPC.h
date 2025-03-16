/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <vector>

class NPC {
private:
    std::string name;
    std::string desc;
    int msg_len;
    std::vector<std::string> msg;

public:
    NPC(std::string npc_name, std::string description);

    void add_Message(std::string message);
    std::string get_Name() const;
    std::string get_Desc() const;
    std::string get_Msg();

    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
};

#endif