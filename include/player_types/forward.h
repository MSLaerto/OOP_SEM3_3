/**
 * @file forward.h
 * @brief This file contains the Forward class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_FORWARD_H
#define MLAB3_FORWARD_H
#include"../player.h"

namespace prog {

    /**
     * @class Forward
     * @brief The Forward class represents a forward player in a game.
     *
     * This class is derived from the Player class and adds functionality specific to a forward player.
     */
    class Forward : public Player {
    public:
        /**
         * @brief Construct a new Forward object
         *
         * @param full_name The full name of the player
         * @param game_time The total game time of the player (default is 0)
         * @param penalty_time The total penalty time of the player (default is 0)
         * @param shots_on_target The number of shots on target by the player (default is 0)
         * @param shots_off_target The number of shots off target by the player (default is 0)
         */
        Forward(std::string full_name, std::size_t game_time = 0, std::size_t penalty_time = 0,
                std::size_t shots_on_target = 0, std::size_t shots_off_target = 0);

        /**
         * @brief Default constructor for the Forward class
         */
        Forward() = default;

        /**
         * @brief Copy constructor for the Forward class
         *
         * @param other The Forward object to copy
         */
        Forward(const Forward& other);

        /**
         * @brief Copy assignment operator for the Forward class
         *
         * @param other The Forward object to copy
         * @return Forward& A reference to the copied Forward object
         */
        Forward& operator=(const Forward& other);

        /**
         * @brief Move constructor for the Forward class
         *
         * @param other The Forward object to move
         */
        Forward(Forward&& other) noexcept;

        /**
         * @brief Move assignment operator for the Forward class
         *
         * @param other The Forward object to move
         * @return Forward& A reference to the moved Forward object
         */
        Forward& operator=(Forward&& other) noexcept;

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
         * @brief Get the number of shots on target by the player
         *
         * @return std::size_t The number of shots on target
         */
        std::size_t get_shots_on_target() const;

        /**
         * @brief Get the number of shots off target by the player
         *
         * @return std::size_t The number of shots off target
         */
        std::size_t get_shots_off_target() const;

        /**
         * @brief Set the number of shots on target by the player
         *
         * @param shots_on_target The number of shots on target
         */
        void set_shots_on_target(std::size_t shots_on_target);

        /**
         * @brief Set the number of shots off target by the player
         *
         * @param shots_off_target The number of shots off target
         */
        void set_shots_off_target(std::size_t shots_off_target);

    private:
        std::size_t shots_on_target_;    /**< The number of shots on target by the player */
        std::size_t shots_off_target_;   /**< The number of shots off target by the player */
    };

}

#endif //MLAB3_FORWARD_H
