#include <iostream>
#include <memory>

#include "cardManager.hpp"
#include "State.hpp"
class CardManager;

int main() {

    CardManager cardManager("../database/bio.csv");
    // cardManager.readCards();

    // cardManager.removeCardById(5);

    // cardManager.addCard("Front Example", "Back Example");

    // cardManager.addCard("Front Exam11ple", "Back Exam11ple");
    
    // cardManager.writeCards();
    // cardManager.closeFile();

    Context app(std::make_unique<InitialState>(), &cardManager);
    app.request();

    return 0;
}