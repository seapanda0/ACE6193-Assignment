#include "Card.hpp"

void Card::setCardFront(std::string a_front) {
    front = a_front;
};

void Card::setCardBack(std::string a_back) {
    back = a_back;
};

std::string Card::getCardFront() {
    return front;
};

std::string Card::getCardBack() {
    return back;
};

int Card::getCardId() {
    return id;
};

void Card::setCardId(int a_id) {
    id = a_id;
};

void Card::setConfidence(int a_confidence) {
    confidence = a_confidence;
};

int Card::getConfidence() {
    return confidence;
};

int64_t Card::getTimeStamp() {
    return timeStamp;
};

int Card::isHidden() {
    return hidden;
};

void Card::setHidden(int a_hidden) {
    hidden = a_hidden;
};

void Card::setTimeStamp(int64_t a_timeStamp) {
    timeStamp = a_timeStamp;
};
