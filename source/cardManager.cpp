#include "cardManager.hpp"

CardManager::CardManager(std::string a_path)
{
    path = a_path;
};

// Return the amount of time from unix time
int64_t getCurrTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    int64_t seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return seconds;
}

// Split a string by delimiter
std::vector<std::string> split_by_delimiter(const std::string &line, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);
    while (std::getline(iss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

/*
Format of database file: semicolon separate columns, newline separate rows
id;front;back;hidden;confidence;last_timestamp
id -> int
front -> string
back -> string
hidden -> int (0 or 1)
confidence -> int
timestamp -> int64_t (unix timestamp in seconds)
*/
void CardManager::readCards()
{
    cardFile.open(path, std::ios::in);

    if (!cardFile.is_open())
    {
        std::cerr << "Error opening card file: " << path << std::endl;
    }

    std::string line;
    while (std::getline(cardFile, line))
    {
        if (line.empty())
            continue; // Skip empty lines

        std::vector<std::string> fields = split_by_delimiter(line, DATABASE_DELIMTER);
        if (fields.size() != 6)
        {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue; // Skip lines with incorrect format, more error handling can be added here
        }

        Card temp_card;

        try
        {
            temp_card.setCardId(std::stoi(fields[0]));
            temp_card.setCardFront(fields[1]);
            temp_card.setCardBack(fields[2]);
            temp_card.setHidden(std::stoi(fields[3]));
            temp_card.setConfidence(std::stoi(fields[4]));
            temp_card.setTimeStamp(std::stoll(fields[5]));

            allCards.push_back(temp_card);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            continue; // Skip lines with parsing errors
        }
        // std::cout << line << std::endl;
    }
    reassignIDs();

    cardFile.close();
}

void CardManager::writeCards()
{

    reassignIDs();

    cardFile.open(path, std::ios::out | std::ios::trunc);

    if (!cardFile.is_open())
    {
        std::cerr << "Error opening card file: " << path << std::endl;
        return;
    }

    for (Card temp_card : allCards)
    {
        cardFile << temp_card.getCardId() << DATABASE_DELIMTER
                 << temp_card.getCardFront() << DATABASE_DELIMTER
                 << temp_card.getCardBack() << DATABASE_DELIMTER
                 << temp_card.isHidden() << DATABASE_DELIMTER
                 << temp_card.getConfidence() << DATABASE_DELIMTER
                 << temp_card.getTimeStamp() << std::endl;
    }

    cardFile.close();
}

void CardManager::addCard(std::string a_front, std::string a_back)
{

    reassignIDs();

    Card new_card;
    new_card.setCardFront(a_front);
    new_card.setCardBack(a_back);
    new_card.setHidden(0);
    new_card.setConfidence(0);
    new_card.setTimeStamp(getCurrTimeStamp());

    // Assign an ID to the card
    if (allCards.empty())
    {
        new_card.setCardId(1); // Start IDs from 1
    }
    else
    {
        new_card.setCardId(allCards.back().getCardId() + 1); // Increment last ID
    }

    allCards.push_back(new_card);
}

void CardManager::removeCardById(int a_id)
{

    size_t initialSize = allCards.size();

    auto newEnd = std::remove_if(allCards.begin(), allCards.end(),
                                 [a_id](const Card &card)
                                 { return card.getCardId() == a_id; });

    allCards.erase(newEnd, allCards.end());

    size_t newSize = allCards.size();
    if (newSize == initialSize)
    {
        std::cerr << "Card with ID " << a_id << " not found." << std::endl;
    }
    else
    {
        std::cout << "Card with ID " << a_id << " removed successfully." << std::endl;
    }
    reassignIDs();
}

void CardManager::reassignIDs()
{
    for (int i = 0; i < allCards.size(); ++i)
    {
        allCards[i].setCardId(i + 1); // IDs start from 1
    }
}

void CardManager::closeFile()
{
    cardFile.close();
}

const std::vector<Card> &CardManager::getCards() const
{
    return allCards;
}

float CardManager::computeAverageConfidence() const
{
    float sum = 0;
    for (Card temp_card : allCards)
    {
        sum += temp_card.getConfidence();
    }

    return sum / (allCards.size());
}