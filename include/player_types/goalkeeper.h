/**
 * @file goalkeeper.h
 * @brief This file contains the Goalkeeper class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_GOALKEEPER_H
#define MLAB3_GOALKEEPER_H
#include "../player.h"

namespace prog {

    /**
     * @class Goalkeeper
     * @brief The Goalkeeper class represents a goalkeeper player in a game.
     *
     * This class is derived from the Player class and adds functionality specific to a goalkeeper player.
     */
    class Goalkeeper : public Player {
    public:
        /**
         * @brief Construct a new Goalkeeper object
         *
         * @param full_name The full name of the player
         * @param game_time The total game time of the player (default is 0)
         * @param penalty_time The total penalty time of the player (default is 0)
         * @param saves The number of saves made by the goalkeeper (default is 0)
         * @param goals_conceded The number of goals conceded by the goalkeeper (default is 0)
         */
        Goalkeeper(std::string full_name, std::size_t game_time = 0, std::size_t penalty_time = 0,
                   std::size_t saves = 0, std::size_t goals_conceded = 0);

        /**
         * @brief Default constructor for the Goalkeeper class
         */
        Goalkeeper() = default;

        /**
         * @brief Copy constructor for the Goalkeeper class
         *
         * @param other The Goalkeeper object to copy
         */
        Goalkeeper(const Goalkeeper& other);

        /**
         * @brief Copy assignment operator for the Goalkeeper class
         *
         * @param other The Goalkeeper object to copy
         * @return Goalkeeper& A reference to the copied Goalkeeper object
         */
        Goalkeeper& operator=(const Goalkeeper& other);

        /**
         * @brief Move constructor for the Goalkeeper class
         *
         * @param other The Goalkeeper object to move
         */
        Goalkeeper(Goalkeeper&& other) noexcept;

        /**
         * @brief Move assignment operator for the Goalkeeper class
         *
         * @param other The Goalkeeper object to move
         * @return Goalkeeper& A reference to the moved Goalkeeper object
         */
        Goalkeeper& operator=(Goalkeeper&& other) noexcept;

        /**
         * @brief Get the type of the player
         *
         * @return const std::string The type of the player
         */
        const std::string get_type() const override;

        /**
         * @brief Print the details of the player
         *
         * @return const std::string The details of the player
         */
        const std::string print() const override;

        /**
         * @brief Get the number of saves made by the goalkeeper
         *
         * @return std::size_t The number of saves
         */
        std::size_t get_saves() const;

        /**
         * @brief Get the number of goals conceded by the goalkeeper
         *
         * @return std::size_t The number of goals conceded
         */
        std::size_t get_goals_conceded() const;

        /**
         * @brief Set the number of saves made by the goalkeeper
         *
         * @param saves The number of saves
         */
        void set_saves(std::size_t saves);

        /**
         * @brief Set the number of goals conceded by the goalkeeper
         *
         * @param goals_conceded The number of goals conceded
         */
        void set_goals_conceded(std::size_t goals_conceded);

    private:
        std::size_t saves_;    /**< The number of saves made by the goalkeeper */
        std::size_t goals_conceded_;   /**< The number of goals conceded by the goalkeeper */
    };

}

#endif //MLAB3_GOALKEEPER_H
