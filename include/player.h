/**
 * @file player.h
 * @brief This file contains the Player class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */

#ifndef MLAB3_PLAYER_H
#define MLAB3_PLAYER_H

#include <string>
#include <iostream>
#include <sstream>

namespace prog {

    /**
     * @class Player
     * @brief The base class representing a player in a soccer game.
     */
    class Player {
    protected:
        std::string full_name_; /**< The full name of the player. */
        std::size_t game_time_; /**< The game time of the player (in seconds). */
        std::size_t penalty_time_; /**< The penalty time of the player (in seconds). */

    public:
        /**
         * @brief Default constructor for the Player class.
         */
        Player() = default;

        /**
         * @brief Constructs a Player object with the given full name, game time, and penalty time.
         * @param full_name The full name of the player.
         * @param game_time The game time of the player (in seconds).
         * @param penalty_time The penalty time of the player (in seconds).
         */
        Player(std::string full_name, std::size_t game_time = 0, std::size_t penalty_time = 0);

        /**
         * @brief Virtual destructor for the Player class.
         */
        virtual ~Player() = default;

        /**
         * @brief Sets the game time of the player.
         * @param new_time The new game time (in seconds).
         */
        void set_game_time(std::size_t new_time);

        /**
         * @brief Sets the penalty time of the player.
         * @param new_time The new penalty time (in seconds).
         */
        void set_penalty_time(std::size_t new_time);

        /**
         * @brief Sets the full name of the player.
         * @param name The new full name of the player.
         */
        void set_full_name(const std::string& name);

        /**
         * @brief Gets the game time of the player.
         * @return The game time (in seconds).
         */
        std::size_t get_game_time() const;

        /**
         * @brief Gets the penalty time of the player.
         * @return The penalty time (in seconds).
         */
        std::size_t get_penalty_time() const;

        /**
         * @brief Gets the full name of the player.
         * @return The full name of the player.
         */
        const std::string& get_full_name() const;

        /**
         * @brief Returns a string representation of the player's information.
         * @return A string containing the player's information.
         */
        virtual const std::string print() const;

        /**
         * @brief Returns the type of the player.
         * @return A string containing the type of the player.
         */
        virtual const std::string get_type() const = 0;

        /**
         * @brief Overloads the output operator for the Player class.
         * @param os The output stream.
         * @param player The Player object to output.
         * @return The output stream with the Player object's information.
         */
        friend std::ostream& operator<<(std::ostream& os, const Player& player);
    };
}

#endif //MLAB3_PLAYER_H
