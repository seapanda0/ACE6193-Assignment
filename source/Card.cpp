#include "Card.hpp"

Card::Card(std::string a_front, std::string a_back, int a_id)
{
    front = a_front;
    back = a_back;
    id = a_id;
}

int Card::getID() const
{
    return id;
}
