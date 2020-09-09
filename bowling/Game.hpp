#pragma once

#include <iostream>
#include <string>
#include <vector>

class Frame {
    char firstRoll;
    char secondRoll;

   public:
    Frame() : firstRoll(' '), secondRoll(' ') {}
    Frame(char first, char second) : firstRoll(first), secondRoll(second) {}
    bool operator==(const Frame& rhs) const { return firstRoll == rhs.firstRoll && secondRoll == rhs.secondRoll; }
    friend std::ostream& operator<<(std::ostream& os, const Frame& frame);
    char getFirstRoll() { return firstRoll; };
    char getSecondRoll() { return secondRoll; };
};

inline std::ostream& operator<<(std::ostream& os, const Frame& frame) {
    os << "{" << frame.firstRoll << ", " << frame.secondRoll << "}";
    return os;
}

class Game {
   public:
    enum class Status {
        NO_GAME,
        IN_PROGRESS,
        FINISHED,
    };

   private:
    struct PlayerData {
        std::string name;
        std::vector<Frame> rolls;
    };
    std::vector<PlayerData> players;
    void loadPlayerRolls(std::ifstream& file, std::vector<Frame>& playerRolls);
    bool isLastFrame(int frameCount);
    bool isStrike(char currentRoll);
    bool isSpare(char nextRoll);
    size_t countFramesWithoutStrikeOrSpare(std::vector<Frame>& rolls);
    size_t countOnlyStrikeFrames(std::vector<Frame>& rolls);

   public:
    Game(){};
    void loadFromFile(const std::string& filePath);
    const std::vector<PlayerData>& getPlayers() { return players; };
    Status getGameStatus();
    size_t countPoints(std::vector<Frame>& rolls);
};
