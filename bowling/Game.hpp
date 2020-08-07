#pragma once

#include <string>
#include <vector>

struct Frame {
    char firstRoll;
    char secondRoll;
    Frame() : firstRoll(' '), secondRoll(' ') {}
    Frame(char first, char second) : firstRoll(first), secondRoll(second) {}
};

struct PlayerData {
    std::string name;
    std::vector<Frame> rolls;
};

class Game {
    std::vector<PlayerData> players;
    void loadPlayerRolls(std::ifstream& file, std::vector<Frame>& playerRolls);
    bool lineEnds(const std::string& text);
    void putBackCharacters(std::ifstream& file, int count);
    bool spare(const std::vector<Frame>& playerRolls);
    bool lastFrame(const std::vector<Frame>& playerRolls);

        public : Game(){};
    void loadFromFile(const std::string& fileName);
    const std::vector<PlayerData>& getPlayers() { return players; };
};
