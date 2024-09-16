/**
 * @file team.h
 * @brief This file contains the Team class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_TEAM_H
#define MLAB3_TEAM_H

#include "game.h"
#include <map>

namespace prog {

    /**
     * @class Team
     * @brief The Team class represents a team that plays games.
     *
     * This class contains the name of the team, the full name of the coach, and a map of games played by the team, where the key is the date and time of the game and the value is a shared pointer to a Game object.
     */
    class Team {
    public:
        /**
         * @brief Construct a new Team object with a name and a coach full name.
         *
         * @param name The name of the team
         * @param coach_full_name The full name of the coach
         */
        Team(const std::string &name, const std::string &coach_full_name);

        /**
         * @brief Get the name of the team.
         *
         * @return const std::string& The name of the team
         */
        const std::string &get_name() const;

        /**
         * @brief Get the full name of the coach.
         *
         * @return const std::string& The full name of the coach
         */
        const std::string &get_coach_full_name() const;

        /**
         * @brief Get the map of games played by the team.
         *
         * @return const std::map<std::chrono::system_clock::time_point, std::shared_ptr<Game>>& The map of games played by the team
         */
        const std::map<std::chrono::system_clock::time_point, std::shared_ptr<Game>> &get_games() const;

        /**
         * @brief Add a game to the map of games played by the team.
         *
         * @param game The game to add
         */
        void add_game(std::shared_ptr<Game> game);

        /**
         * @brief Remove a game from the map of games played by the team.
         *
         * @param date The date and time of the game to remove
         */
        void remove_game(const std::chrono::system_clock::time_point &date);

        /**
         * @brief Find a game in the map of games played by the team.
         *
         * @param date The date and time of the game to find
         * @return std::shared_ptr<Game> The game if found, otherwise nullptr
         */
        std::shared_ptr<Game> find_game(const std::chrono::system_clock::time_point &date) const;

        /**
         * @brief Print the details of the team.
         *
         * @return const std::string The details of the team
         */
        const std::string print() const;

        /**
         * @brief Overload the output operator for the Team class.
         *
         * @param os The output stream
         * @param team The Team object to output
         * @return std::ostream& The output stream
         */
        inline friend std::ostream& operator<<(std::ostream& os, const Team& team);

    private:
        std::string name_;                   /**< The name of the team */
        std::string coach_full_name_;        /**< The full name of the coach */
        std::map<std::chrono::system_clock::time_point, std::shared_ptr<Game>> games_;  /**< The map of games played by the team */
    };

    /**
     * @brief Overload the output operator for the Team class.
     *
     * @param os The output stream
     * @param team The Team object to output
     * @return std::ostream& The output stream
     */
    std::ostream& operator<<(std::ostream& os, const Team& team){
        os << team.print() << std::endl;
        return os;
    }

}

#endif //MLAB3_TEAM_H
