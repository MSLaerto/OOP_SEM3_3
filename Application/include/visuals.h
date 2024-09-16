/**
 * @file visuals.h
 * @brief This file contains the Visuals class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_VISUALS_H
#define MLAB3_VISUALS_H

#include <iostream>
#include <string>
#include <map>
#include "../../include/funcs.h"

/**
 * @class Visuals
 * @brief The Visuals class provides methods to handle user input and display output.
 *
 * This class contains methods to display the main menu, get user choices, get date, get opponent team, get quantity, display most active players, display service info, and get player type.
 */
class Visuals {
public:
    /**
     * @brief Displays the main menu to the user.
     */
    void displayMainMenu();

    /**
     * @brief Gets the user's choice from the main menu.
     *
     * @return int The user's choice
     */
    int getUserChoice();

    /**
     * @brief Gets a date from the user.
     *
     * @return std::chrono::system_clock::time_point The date entered by the user
     */
    std::chrono::system_clock::time_point getDate();

    /**
     * @brief Gets the name of the opponent team from the user.
     *
     * @return std::string The name of the opponent team entered by the user
     */
    std::string getOpponentTeam();

    /**
     * @brief Gets the quantity of players from the user.
     *
     * @return std::size_t The quantity of players entered by the user
     */
    std::size_t getQuantity();

    /**
     * @brief Displays the most active players.
     *
     * @param mostActivePlayers A map containing the most active players
     * @param title The title to display
     */
    void displayMostActivePlayers(const std::map<std::string, std::pair<std::string, std::size_t>>& mostActivePlayers, const std::string& title);

    /**
     * @brief Displays service information.
     *
     * @param info The service information to display
     */
    void displayServiceInfo(const std::string& info);

    /**
     * @brief Gets the player type from the user.
     *
     * @return std::string The player type entered by the user
     */
    std::string getPlayerType();
};

#endif //MLAB3_VISUALS_H
