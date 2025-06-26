#ifndef CARD_HPP
#define CARD_HPP

#include <vector>
#include <string>
#include <chrono>

class Card {
private: 
    int id = -1;
    std::string front, back;
    int hidden = 0;
    int confidence = 0;
    int64_t timeStamp = 0;
    

public:
    Card() = default;
    ~Card() = default;

    int getCardId();
    void setCardId(int a_id);

    void setCardFront(std::string a_front);
    void setCardBack(std::string a_back);

    std::string getCardFront();
    std::string getCardBack();

    int isHidden();
    void setHidden(int a_hidden);

    void setConfidence(int a_confidence);
    int getConfidence();

    int64_t getTimeStamp();
    void setTimeStamp(int64_t a_timeStamp);
    // void toggleHidden();
};

#endif