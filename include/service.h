/**
 * @file service.h
 * @brief This file contains the Service class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_SERVICE_H
#define MLAB3_SERVICE_H

#include <algorithm>
#include "team.h"
#include <future>
#include <thread>

namespace prog {

    /**
     * @class Service
     * @brief The Service class provides services related to a team.
     *
     * This class contains a reference to a Team object and provides methods to add, remove, and modify games, calculate total penalty time, print player information, and get the most active players.
     */
    class Service {
    public:
        /**
         * @brief Construct a new Service object with a reference to a Team object.
         *
         * @param team The Team object to reference
         */
        Service(Team &team);

        /**
         * @brief Add a game to the team's list of games.
         *
         * @param date The date and time of the game
         * @param opponent_team The name of the opponent team
         * @param quantity The number of players in the game
         * @param players The players who participated in the game (default is an empty vector)
         */
        void add_game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team,
                      std::size_t quantity, const std::vector<std::shared_ptr<Player>> &players = std::vector<std::shared_ptr<Player>>());

        /**
         * @brief Remove a game from the team's list of games.
         *
         * @param date The date and time of the game to remove
         */
        void remove_game(const std::chrono::system_clock::time_point &date);

        /**
         * @brief Modify a game in the team's list of games.
         *
         * @param date The date and time of the game to modify
         * @param opponent_team The new name of the opponent team
         * @param quantity The new number of players in the game
         */
        void modify_game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team,
                         std::size_t quantity);

        /**
         * @brief Calculate the total penalty time for all players in a game.
         *
         * @param date The date and time of the game
         * @return std::size_t The total penalty time for all players in the game
         */
        std::size_t calculate_total_penalty_time(const std::chrono::system_clock::time_point &date) const;

        /**
         * @brief Print the information of all players in the team.
         *
         * @return std::string The information of all players in the team
         */
        std::string print_players_info() const;

        /**
         * @brief Overload the output operator for the Service class.
         *
         * @param os The output stream
         * @param service The Service object to output
         * @return std::ostream& The output stream
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Service& service);

        /**
         * @brief Get the most active players in the team using a single thread.
         *
         * @return std::map<std::string, std::pair<std::string, std::size_t>> A map containing the most active players in the team, where the key is the position of the player, the first element of the pair is the name of the player, and the second element of the pair is the total game time of the player
         */
        std::map<std::string, std::pair<std::string, std::size_t>> get_most_active_players_single_threaded() const;

        /**
         * @brief Get the most active players in the team using multiple threads.
         *
         * @param num_threads The number of threads to use (default is the number of hardware concurrency)
         * @return std::map<std::string, std::pair<std::string, std::size_t>> A map containing the most active players in the team, where the key is the position of the player, the first element of the pair is the name of the player, and the second element of the pair is the total game time of the player
         */
        std::map<std::string, std::pair<std::string, std::size_t>> get_most_active_players_multithreaded(std::size_t num_threads = std::thread::hardware_concurrency()) const;

    private:
        Team &team_;    /**< The Team object referenced by the Service object */
    };

    /**
     * @brief Overload the output operator for the Service class.
     *
     * @param os The output stream
     * @param service The Service object to output
     * @return std::ostream& The output stream
     */
    std::ostream& operator<<(std::ostream& os, const Service& service){
        os << service.print_players_info();
        return os;
    }

}

#endif //MLAB3_SERVICE_H
