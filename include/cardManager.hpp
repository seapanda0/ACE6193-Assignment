#include <vector>
#include <string>

#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

class Card;

class CardManager {
private: 
    std::vector<Card> allCards;

public:
    CardManager() = default;

    void addCard(std::string a_front, std::string a_back);
    void sortCardById();
    void removeCardById(int a_id);
    void readCardsFromTextFile(std::string a_name);
    void writeCardsToTextFile(std::string a_name);
};

#endif