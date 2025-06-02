#include <vector>
#include <string>

#ifndef CARD_HPP
#define CARD_HPP

class Card {
private: 
    std::string front, back;
    int id = -1;
    bool hidden = false;

public:
    Card() = default;
<<<<<<< HEAD
    Card(std::string a_front, std::string a_back, int a_id);

    ~Card();

    int getID() const;
=======
    Card(std::string a_front, std::string a_back);

    ~Card();

    int getCardId();
>>>>>>> 08cfaed (header declarations for Card and CardManager classes)
    void setCardFront(std::string a_front);
    void setCardBack(std::string a_back);
    std::string getCardFront();
    std::string getCardBack();
    bool isHidden();
    void setHidden(bool a_hidden);
    // void toggleHidden();
};

#endif