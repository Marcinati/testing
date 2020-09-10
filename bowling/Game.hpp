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
    char getFirstRoll() const { return firstRoll; };
    char getSecondRoll() const { return secondRoll; };
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
    bool isLastFrame(int frameCount) const;
    bool isStrike(char currentRoll) const;
    bool isStrike(Frame& frame) const;
    bool isSpare(char nextRoll) const;
    size_t countFramesWithoutStrikeOrSpare(std::vector<Frame>& rolls);
    size_t countOnlyStrikeFrames(std::vector<Frame>& rolls);
    size_t countOnlySpareFrames(std::vector<Frame>& rolls);
    std::string getOutputString(int laneNumber) const;
    int getPlayerScore(const PlayerData& player) const;
    

   public:
    Game(){};
    void loadFromFile(const std::string& filePath);
    const std::vector<PlayerData>& getPlayers() const { return players; };
    size_t countPoints(std::vector<Frame>& rolls);
    Status getGameStatus() const;
    void printOutput(std::ostream& os, int laneNumber) const;
};
