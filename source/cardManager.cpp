#include "cardManager.hpp"
#include "Card.hpp"
#include <vector>
#include <algorithm>

void CardManager::addCard(std::string a_front, std::string a_back)
{
    int newId = allCards.size() + 1;
    allCards.push_back(Card());
}

void CardManager::sortCardById()
{
    std::sort(allCards.begin(), allCards.end(), [](const Card & a, const Card & b) {
        return a.getID() < b.getID();
    });
}
