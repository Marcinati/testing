#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

void Game::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios_base::in);
    if (!file.good()) {
        std::cerr << "file " << filePath << " could not be opened!\n";
        abort();
    }
    while (!file.eof()) {
        PlayerData player;
        std::getline(file, player.name, ':');
        loadPlayerRolls(file, player.rolls);
        if (!file.eof()) {
            players.push_back(player);
        }
    }
    file.close();
}

void Game::loadPlayerRolls(std::ifstream& file, std::vector<Frame>& playerRolls) {
    std::string rolls{};
    Frame currentFrame{};
    int frameCount = 1;
    std::getline(file, rolls);
    for (int currentRoll = 0; currentRoll < rolls.size(); ++currentRoll) {
        if (isStrike(rolls[currentRoll])) {
            currentFrame = Frame('X', ' ');
            currentRoll++;
            if (isLastFrame(frameCount)) {
                currentRoll++;
            }
        } else if (isSpare(rolls[currentRoll + 1])) {
            currentFrame = Frame(rolls[currentRoll], '/');
            currentRoll += 2;
            if (isLastFrame(frameCount)) {
                currentRoll++;
            }
        } else {
            currentFrame = Frame(rolls[currentRoll], rolls[currentRoll + 1]);
            currentRoll += 2;
        }
        frameCount++;
        playerRolls.push_back(currentFrame);
    }
}

bool Game::isLastFrame(int frameCount) {
    return frameCount == 10;
}

bool Game::isStrike(char currentRoll) {
    return currentRoll == 'X';
}

bool Game::isSpare(char nextRoll) {
    return nextRoll == '/';
}

Game::Status Game::getGameStatus() {
    if (players.size() == 0) {
        return Game::Status::NO_GAME;
    }
    if (std::any_of(players.begin(), players.end(), [](PlayerData& player) {
            return !(player.rolls.size() == 10 || player.rolls.size() == 11);
        })) {
        return Game::Status::IN_PROGRESS;
    }
    if (std::all_of(players.begin(), players.end(), [](PlayerData& player) {
            return player.rolls.size() == 10 || player.rolls.size() == 11;
        })) {
        return Game::Status::FINISHED;
    }
    return Game::Status::NO_GAME;
}

size_t Game::countFramesWithoutStrikeOrSpare(std::vector<Frame>& rolls) {
    size_t totalPointsWithoutStrikeNorSpare = 0;
    for (size_t i = 0; i < rolls.size(); i++) {
        if (!isStrike(rolls[i].getFirstRoll()) && !isSpare(rolls[i].getSecondRoll())) {
            totalPointsWithoutStrikeNorSpare += (rolls[i].getFirstRoll() + rolls[i].getSecondRoll());
        } 
    }
    return totalPointsWithoutStrikeNorSpare;
}

size_t Game::countOnlyStrikeFrames(std::vector<Frame>& rolls) {
    size_t totalOnlyStrikePoints = 0;
    for (size_t i = 0; i < rolls.size(); i++) {
        if (isStrike(rolls[i].getFirstRoll())) {
            totalOnlyStrikePoints += 10;
            if ((i + 1) != rolls.size()) {
                if (isStrike(rolls.at(i + 1).getFirstRoll()) || isSpare(rolls.at(i + 1).getSecondRoll())) {
                    totalOnlyStrikePoints += 10;
                } else {
                    totalOnlyStrikePoints += (rolls[i + 1].getFirstRoll() + rolls[i + 1].getSecondRoll());
                }
            }
        }
    }
    return totalOnlyStrikePoints;
}

size_t Game::countPoints(std::vector<Frame>& rolls) {
    size_t totalPoints = 0;
    totalPoints += countFramesWithoutStrikeOrSpare(rolls);
    totalPoints += countOnlyStrikeFrames(rolls);
    return totalPoints;
}
