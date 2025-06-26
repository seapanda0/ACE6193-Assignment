#include "cardManager.hpp"


CardManager::CardManager(std::string a_path){
    path = a_path;
};

// Return the amount of time from unix time 
int64_t getCurrTimeStamp(){
    auto now = std::chrono::system_clock::now();
    int64_t seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return seconds;
}

// Split a string by delimiter
std::vector<std::string> split_by_delimiter (const std::string& line, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);
    while (std::getline(iss, token, delimiter)) {
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
void CardManager::readCards(){
    cardFile.open(path);

    if (!cardFile.is_open()) {
        std::cerr << "Error opening card file: " << path << std::endl;
    }

    std::string line;
    while (std::getline(cardFile, line)){
        if (line.empty()) continue; // Skip empty lines 

        std::vector <std::string> fields = split_by_delimiter(line, DATABASE_DELIMTER);
        if (fields.size() != 6){
            std::cerr << "Invalid line format: " << line << std::endl;
            continue; // Skip lines with incorrect format, more error handling can be added here
        }

        Card temp_card;

        try {
            temp_card.setCardId(std::stoi(fields[0]));
            temp_card.setCardFront(fields[1]);
            temp_card.setCardBack(fields[2]);
            temp_card.setHidden(std::stoi(fields[3]));
            temp_card.setConfidence(std::stoi(fields[4]));
            temp_card.setTimeStamp(std::stoll(fields[5]));

            allCards.push_back(temp_card);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            continue; // Skip lines with parsing errors
        }
        // std::cout << line << std::endl;
    }


}

void CardManager::closeFile(){
    cardFile.close();
}