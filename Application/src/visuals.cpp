#include "../include/visuals.h"

void Visuals::displayMainMenu() {
    std::cout << "-------------------------\n";
    std::cout << "|       Main menu       |\n";
    std::cout << "-------------------------\n";
    std::cout << "| 1. Add game           |\n";
    std::cout << "| 2. Remove game        |\n";
    std::cout << "| 3. Modify game        |\n";
    std::cout << "| 4. Calculate penalty  |\n";
    std::cout << "| 5. Get players info   |\n";
    std::cout << "| 6. Single-threaded    |\n";
    std::cout << "| 7. Multi-threaded     |\n";
    std::cout << "| 0. Exit               |\n";
    std::cout << "-------------------------\n";
}

int Visuals::getUserChoice() {
    return getNum<int>(0, 7);
}

std::chrono::system_clock::time_point Visuals::getDate() {
    int year, month, day, hour, minute, second;

    std::cout << "Enter year (YYYY): ";
    year = getNum<int>();

    std::cout << "Enter month (MM): ";
    month = getNum<int>(1, 12);

    std::cout << "Enter day (DD): ";
    day = getNum<int>(1, 31);

    std::cout << "Enter hour (HH, 24-hour format): ";
    hour = getNum<int>(0, 23);

    std::cout << "Enter minute (mm): ";
    minute = getNum<int>(0, 59);

    std::cout << "Enter second (ss): ";
    second = getNum<int>(0, 59);

    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    std::time_t t = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(t);
}

std::string Visuals::getOpponentTeam() {
    std::cout << "Enter opponent team: ";
    return readLine();
}

std::size_t Visuals::getQuantity() {
    std::cout << "Enter quantity: ";
    return getNum<std::size_t>();
}

void Visuals::displayMostActivePlayers(const std::map<std::string, std::pair<std::string, std::size_t>>& mostActivePlayers, const std::string& title) {
    std::cout << "-----------------------------------\n";
    std::cout << "|         " << title << "         |\n";
    std::cout << "-----------------------------------\n";
    for (const auto& player : mostActivePlayers) {
        std::cout << "| " << player.first << ": " << player.second.first << " (" << player.second.second << " sec) |\n";
    }
    std::cout << "-----------------------------------\n";
}

void Visuals::displayServiceInfo(const std::string& info) {
    std::cout << "-------------------------\n";
    std::cout << "|   Service info        |\n";
    std::cout << "-------------------------\n";
    std::cout << info << "\n";
    std::cout << "-------------------------\n";
}

std::string Visuals::getPlayerType() {
    std::cout << "Choose the player type:" << std::endl;
    std::cout << "1. Defender" << std::endl;
    std::cout << "2. Forward" << std::endl;
    std::cout << "3. Goalkeeper" << std::endl;
    std::cout << "Enter your choice: ";

    int choice = getNum<int>(1, 3);

    switch (choice) {
        case 1:
            return "Defender";
        case 2:
            return "Forward";
        case 3:
            return "Goalkeeper";
        default:
            throw std::runtime_error("Invalid choice");
    }
}
