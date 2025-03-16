/*
Name: Kenan Velagic 
2/11/25
Last Updated: 3/15/25
*/

#include "NPC.h"
#include <stdexcept>

// non-playable characters
// Constructor
NPC::NPC(std::string npc_name, std::string description) {
    if (npc_name.empty() || description.empty()) {
        throw std::invalid_argument("Error: Invalid npc_name/description.");
    }

    name = npc_name;
    desc = description;
    msg_len = 0;
}

// adds a message to the NPC's dialog list
void NPC::add_Message(std::string message) {
    msg.push_back(message);
}

// returns the NPC's name
std::string NPC::get_Name() const {
    return name;
}

// returns the NPC's description
std::string NPC::get_Desc() const {
    return desc;
}

// returns the current message and increments to the next, waiting to be spoken again
std::string NPC::get_Msg() {
    if (msg.empty()) {
        return "";
    }

    if (msg_len >= msg.size()) {
        msg_len = 0;
    }

    int tmp = msg_len;
    msg_len++;
    return msg[tmp];
}

// overload output stream to display only NPC name
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    return os;
}