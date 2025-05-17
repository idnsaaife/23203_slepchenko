#include "headers/console.h"
#include <string>
#include <iostream>

std::string Console::getInput()
{
    std::string str;
    std::getline(std::cin, str);
    return str;
}

bool Console::waitQuit()
{
    std::cout << "Press ENTER to continue, type quit to end the match" << std::endl;
    std::string str;
    std::getline(std::cin, str);
    return (str != "quit");
}

void Console::printHelp()
{
    std::cout << "Usage: blackjack [OPTIONS]\n"
              << "Options:\n"
              << "  --mode=[detailed|fast|tournament]   Simulation mode (default: detailed)\n"
              << "  --configs=<dirname>                 Directory with strategy configs\n"
              << "  --strategies=<s1,s2,...>            List of strategies to compete\n"
              << "  --deck=[rand|simple|N]              Type of deck (default: simple)\n";
}

void Console::printWinner(const Player &player)
{
    std::cout << player.getName() + " winner!" << std::endl;
}

void Console::printFirstCard(const Player &player) {
    std::cout << player.getName() + "'s first card: ";
    player.getFirstCard().showCard();
}

void Console::printHand(const Player &player)
{
    std::cout << player.getName() + "'s hand:" << std::endl;
    for (const auto &card : player.getHand())
    {
        card.showCard();
    }
}

void Console::printScore(const Player &player){
    std::cout << player.getName() << "'s score now : ";
    std::cout << player.countScore() << std::endl;
}

void Console::printStand(const Player &player) {
    std::cout << player.getName() + " stand" << std::endl;
}
void Console::printHit(const Player &player){
    std::cout << player.getName() + " decides to take card" << std::endl;
}

void Console::printMatchPlayers(std::vector<Player> &players, size_t num1, size_t num2)
{
    std::cout << players[num1].getName() + " vs " + players[num2].getName() << std::endl;
}

void Console::printWinnerMatch(std::vector<Player> &players, size_t winNum)
{
    std::cout << players[winNum].getName() + " won match" << std::endl;
}

void Console::printNotEnoughPlayers() {
    std::cout << "Not enough players. Try again" << std::endl;
    printHelp();
}
