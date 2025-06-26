#include <iostream>
#include "cardManager.hpp"

class CardManager;

int main() {

    CardManager cardManager("../database/bio.csv");
    cardManager.readCards();

    // cardManager.removeCardById(5);

    // cardManager.addCard("Front Example", "Back Example");

    // cardManager.addCard("Front Exam11ple", "Back Exam11ple");
    
    cardManager.writeCards();
    // cardManager.closeFile();
    return 0;
}