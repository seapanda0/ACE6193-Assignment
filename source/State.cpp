#include "State.hpp"
#include <string>
#include <iostream>

/*INITIAL State Start*/
// std::unique_ptr<State> nextState;

void InitialState::handle(Context *context)
{
    std::cout << "Welcome to Simple Flashcard Program\n";
    std::cout << "Attempting to load your cards...\n";
    context->cardManager->readCards();

    // if (!success)
    // {
    //     std::cout << "Couldn't load cards...\n";
    //     std::cout << "Closing program\n";

    //     context->exit();
    //     // context->clearScreen();
    // }
    // else

    context->setState(std::make_unique<IdleState>());
}
/*INITIAL State End*/

/* IDLE State Start*/
void IdleState::handle(Context *context)
{
    context->clearScreen();

    std::cout << "Main Menu:\n";
    std::cout << "1. Start Session\n";
    std::cout << "2. Add Card\n";
    std::cout << "3. Delete Card\n";
    std::cout << "4. Exit\n";

    std::string input;
    std::cin >> input;

    if (input == "1")
    {
        // Start flashcard session
        context->setState(std::make_unique<StudySessionState>());
    }
    else if (input == "2")
    {
        // Add new card
        context->setState(std::make_unique<AddCardState>());
    }
    else if (input == "3")
    {
        // Delete card
        context->setState(std::make_unique<DeleteCardState>());
    }
    else if (input == "4")
    {
        // Exit program
        std::cout << "Goodbye!\n";
        context->cardManager->writeCards();
        context->exit();
    }
    else
    {
        std::cout << "Invalid option. Please try again.\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();

        context->setState(std::make_unique<IdleState>());
    }
}
/* IDLE State End*/

/*Study Session State start*/
void StudySessionState::handle(Context *context)
{
    std::string input;

    float threshold = context->cardManager->computeAverageConfidence();

    std::vector<Card>& allCards = context->cardManager->getCards();
    for (Card& temp_card : allCards)
    {
        if (temp_card.getConfidence() > threshold)
            continue;

        context->clearScreen();
        std::cout << "ID: " <<temp_card.getCardId();
        std::cout << "\n\n"
                  << temp_card.getCardFront();
        std::cout << "\n\nPress Enter to show back of card...";
        std::cin.ignore();
        std::cin.get();
        std::cout << "\n"
                  << temp_card.getCardBack();

        while (1)
        {
            std::cout << "\n\nHow well did you remember the card?"
                      << "\n1 = don't remember at all"
                      << "\n2 = somewhat remembered"
                      << "\n3 =  fully remembered\n";
            std::cin >> input;

            if (input == "1")
            {
                temp_card.decrementConfidence();
                break;
            }
            else if (input == "2")
            {
                // do nothing
                break;
            }
            else if (input == "3")
            {
                temp_card.incrementConfidence();
                break;
            }
            else
            {
                std::cout << "\nInvalid option. Please try again.\n";
                continue;
            }
        }
    }

    context->clearScreen();
    std::cout << "\nCongrats, you've completed the study session.\n";
    std::cout << "Press Enter to go to main menu...";
    std::cin.ignore();
    std::cin.get();

    context->cardManager->writeCards();
    context->setState(std::make_unique<IdleState>());
}
/*Study Session State end*/

/*Add Card State start*/
void AddCardState::handle(Context *context)
{
    std::string input, input2;

    std::cin.ignore();

    std::cout << "Please enter the front of the new card you want to create\n";
    std::getline(std::cin, input);

    std::cout << "Please enter the back of the new card you want to create\n";
    std::getline(std::cin, input2);

    context->cardManager->addCard(input, input2);

    std::cout << "\nPreview of the new card you created\n";
    std::cout << "Front:" << input;
    std::cout << "\nBack:" << input2;
    std::cout << "\n";
    std::cout << "Press Enter to go to main menu...";
    std::cin.ignore();
    std::cin.get();
    context->cardManager->writeCards();
    context->setState(std::make_unique<IdleState>());
}
/*Add Card State end*/

/*Delete Card State start*/
void DeleteCardState::handle(Context *context)
{
    auto allCards = context->cardManager->getCards();
    std::string input;

    std::cout << "\nDisplaying all cards...\n";

    for (Card& temp_card : allCards)
    {
        std::cout << "\n"
                  << temp_card.getCardId() << ". ";
        std::cout << "front: " << temp_card.getCardFront();
        std::cout << "back: " << temp_card.getCardBack();
    }

    std::cout << "\nInput the ID of the card you want to delete\n";
    std::cin >> input;

    int cardId = std::stoi(input);
    context->cardManager->removeCardById(cardId);
    context->cardManager->writeCards();
    context->setState(std::make_unique<IdleState>());
}
/*Delete Card State end*/
