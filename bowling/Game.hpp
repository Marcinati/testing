#pragma once

#include "Frame.hpp"
#include "PlayerData.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

class Game {
   public:
    enum class Status {
        NO_GAME,
        IN_PROGRESS,
        FINISHED,
    };

   private:
    std::vector<PlayerData> players{};

    void loadPlayerRolls(std::ifstream& file, std::vector<Frame>& playerRolls);
    bool isLastFrame(int frameCount) const;
    bool isStrike(char currentRoll) const;
    bool isStrike(const Frame& frame) const;
    bool isSpare(char nextRoll) const;
    bool isSpare(const Frame& frame) const;
    bool isBadCharacter(char) const;
    std::vector<Frame> conversionCharNumbersToInt(const std::vector<Frame>& rolls) const;
    size_t countFramesWithoutStrikeOrSpare(const std::vector<Frame>& rolls) const;
    size_t countOnlyStrikeFrames(const std::vector<Frame>& rolls) const;
    size_t countOnlySpareFrames(const std::vector<Frame>& rolls) const;

   public:
    Game() = default;
    Game(const std::filesystem::path& filePath);
    void loadFromFile(const std::string& filePath);
    const std::vector<PlayerData>& getPlayers() const { return players; };
    size_t countPoints(const std::vector<Frame>& rolls) const;
    Status getGameStatus() const;
    std::string getOutputString(int laneNumber) const;
    bool operator==(const Game& rhs) const;
};
