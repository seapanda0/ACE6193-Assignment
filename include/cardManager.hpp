#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Card.hpp"

#define DATABASE_DELIMTER ';'

class CardManager {
private: 
    std::vector<Card> allCards;
    std::string path;
    std::fstream cardFile;

public:
    // Initialize the object by passing the path to the database file
    CardManager(std::string a_path);
    void addCard(std::string a_front, std::string a_back);
    void removeCardById(int a_id);
    void reassignIDs();
    void readCards();
    void writeCards();
    void closeFile();
    std::vector<Card>& getCards();
    float computeAverageConfidence() const;
};

void writeTimeStamp();

#endif