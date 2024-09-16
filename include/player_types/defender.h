/**
 * @file defender.h
 * @brief This file contains the Defender class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */

#ifndef MLAB3_DEFENDER_H
#define MLAB3_DEFENDER_H

#include "../player.h"

namespace prog {

    /**
     * @class Defender
     * @brief Represents a defender player in a soccer game.
     */
    class Defender : public Player {
    public:
        /**
         * @brief Constructs a Defender object with the given full name, game time, and penalty time.
         * @param full_name The full name of the defender.
         * @param game_time The game time of the defender (in seconds).
         * @param penalty_time The penalty time of the defender (in seconds).
         */
        Defender(std::string full_name, std::size_t game_time = 0, std::size_t penalty_time = 0);

        /**
         * @brief Default constructor for the Defender class.
         */
        Defender() = default;

        /**
         * @brief Copy constructor for the Defender class.
         * @param other The Defender object to copy.
         */
        Defender(const Defender& other);

        /**
         * @brief Copy assignment operator for the Defender class.
         * @param other The Defender object to copy.
         * @return A reference to the copied Defender object.
         */
        Defender& operator=(const Defender& other);

        /**
         * @brief Move constructor for the Defender class.
         * @param other The Defender object to move.
         */
        Defender(Defender&& other) noexcept;

        /**
         * @brief Move assignment operator for the Defender class.
         * @param other The Defender object to move.
         * @return A reference to the moved Defender object.
         */
        Defender& operator=(Defender&& other) noexcept;

        /**
         * @brief Returns the type of the player ("Defender").
         * @return A string containing the type of the player.
         */
        const std::string get_type() const override;
    };
}

#endif //MLAB3_DEFENDER_H
