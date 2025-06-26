#include <iostream>
#include "cardManager.hpp"

class CardManager;

int main() {

    CardManager cardManager("../database/bio.csv");
    cardManager.readCards();
    cardManager.closeFile();
    return 0;
}