/**
 * @file game.h
 * @brief This file contains the Game class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_GAME_H
#define MLAB3_GAME_H
#include "player.h"
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace prog {

    /**
     * @class Game
     * @brief The Game class represents a game played by a team.
     *
     * This class contains information about the date of the game, the opponent team, the number of players in the game, and the players who participated in the game.
     */
    class Game {
    public:
        /**
         * @brief Construct a new Game object with the specified date, opponent team, number of players, and players.
         *
         * @param date The date and time of the game
         * @param opponent_team The name of the opponent team
         * @param quantity The number of players in the game
         * @param players The players who participated in the game (default is an empty vector)
         */
        Game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team, std::size_t quantity,
             const std::vector<std::shared_ptr<Player>> &players = std::vector<std::shared_ptr<Player>>());

        /**
         * @brief Construct a new Game object with the specified date, opponent team, number of players, and players.
         *
         * @param year The year of the game
         * @param month The month of the game
         * @param day The day of the game
         * @param hour The hour of the game
         * @param minute The minute of the game
         * @param opponent_team The name of the opponent team
         * @param quantity The number of players in the game
         * @param players The players who participated in the game (default is an empty vector)
         */
        Game(std::size_t year, std::size_t month, std::size_t day, std::size_t hour, std::size_t minute,
             const std::string &opponent_team, std::size_t quantity,
             const std::vector<std::shared_ptr<Player>> &players = std::vector<std::shared_ptr<Player>>());

        /**
         * @brief Default constructor for the Game class
         */
        Game() = default;

        /**
         * @brief Copy constructor for the Game class
         *
         * @param other The Game object to copy
         */
        Game(const Game &other);

        /**
         * @brief Copy assignment operator for the Game class
         *
         * @param other The Game object to copy
         * @return Game& A reference to the copied Game object
         */
        Game &operator=(const Game &other);

        /**
         * @brief Move constructor for the Game class
         *
         * @param other The Game object to move
         */
        Game(Game &&other) noexcept;

        /**
         * @brief Move assignment operator for the Game class
         *
         * @param other The Game object to move
         * @return Game& A reference to the moved Game object
         */
        Game &operator=(Game &&other) noexcept;

        /**
         * @brief Destructor for the Game class
         */
        ~Game();

        /**
         * @brief Get the date of the game
         *
         * @return const std::chrono::system_clock::time_point& The date of the game
         */
        const std::chrono::system_clock::time_point &get_date() const;

        /**
         * @brief Get the name of the opponent team
         *
         * @return const std::string& The name of the opponent team
         */
        const std::string &get_opponent_team() const;

        /**
         * @brief Get the players who participated in the game
         *
         * @return const std::vector<std::shared_ptr<Player>>& The players who participated in the game
         */
        const std::vector<std::shared_ptr<Player>> &get_players() const;

        /**
         * @brief Get the number of players in the game
         *
         * @return std::size_t The number of players in the game
         */
        std::size_t get_quantity() const;

        /**
         * @brief Set the date of the game
         *
         * @param date The date of the game
         */
        void set_date(const std::chrono::system_clock::time_point &date);

        /**
         * @brief Set the number of players in the game
         *
         * @param quantity The number of players in the game
         */
        void set_quantity(std::size_t quantity);

        /**
         * @brief Set the name of the opponent team
         *
         * @param opponent_team The name of the opponent team
         */
        void set_opponent_team(const std::string &opponent_team);

        /**
         * @brief Add a player to the game
         *
         * @param player The player to add
         */
        void add_player(std::shared_ptr<Player> player);

        /**
         * @brief Remove a player from the game
         *
         * @param name The name of the player to remove
         */
        void remove_player(const std::string& name);

        /**
         * @brief Print the details of the game
         *
         * @return const std::string The details of the game
         */
        const std::string print() const;

        /**
         * @brief Overload the output operator for the Game class
         *
         * @param os The output stream
         * @param game The Game object to output
         * @return std::ostream& The output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

    private:
        std::chrono::system_clock::time_point date_;    /**< The date and time of the game */
        std::string opponent_team_;                      /**< The name of the opponent team */
        std::size_t quantity_;                           /**< The number of players in the game */
        std::vector<std::shared_ptr<Player>> players_;   /**< The players who participated in the game */
    };

    /**
     * @brief Overload the output operator for the Game class
     *
     * @param os The output stream
     * @param game The Game object to output
     * @return std::ostream& The output stream
     */
    inline std::ostream& operator<<(std::ostream& os, const Game& game){
        os << game.print();
        return os;
    }

    /**
     * @brief Format a system_clock::time_point object as a string
     *
     * @param date The system_clock::time_point object to format
     * @return std::string The formatted string
     */
    inline std::string format_date(const std::chrono::system_clock::time_point& date) {
        std::time_t t = std::chrono::system_clock::to_time_t(date);
        std::tm* tm = std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

}

#endif //MLAB3_GAME_H
