#define CATCH_CONFIG_MAIN
#include "../include/player_types/defender.h"
#include "Catch/Catch.hpp"

TEST_CASE("Defender class tests", "[Defender]") {
    SECTION("Constructors and assignment operators") {
        prog::Defender defender1("John Doe", 45, 5);

        SECTION("Copy constructor") {
            prog::Defender defender2(defender1);
            REQUIRE(defender2.get_full_name() == "John Doe");
            REQUIRE(defender2.get_game_time() == 45);
            REQUIRE(defender2.get_penalty_time() == 5);
        }

        SECTION("Copy assignment operator") {
            prog::Defender defender2;
            defender2 = defender1;
            REQUIRE(defender2.get_full_name() == "John Doe");
            REQUIRE(defender2.get_game_time() == 45);
            REQUIRE(defender2.get_penalty_time() == 5);
        }

        SECTION("Move constructor") {
            prog::Defender defender2(std::move(defender1));
            REQUIRE(defender2.get_full_name() == "John Doe");
            REQUIRE(defender2.get_game_time() == 45);
            REQUIRE(defender2.get_penalty_time() == 5);
        }

        SECTION("Move assignment operator") {
            prog::Defender defender2;
            defender2 = std::move(defender1);
            REQUIRE(defender2.get_full_name() == "John Doe");
            REQUIRE(defender2.get_game_time() == 45);
            REQUIRE(defender2.get_penalty_time() == 5);
        }
    }

    SECTION("get_type function") {
        prog::Defender defender("John Doe", 45, 5);
        REQUIRE(defender.get_type() == "Defender");
    }
}

TEST_CASE("Player class tests", "[Player]") {
    prog::Defender player("John Doe", 45, 5);

    SECTION("set_game_time and set_penalty_time") {
        player.set_game_time(60);
        player.set_penalty_time(10);

        REQUIRE(player.get_game_time() == 60);
        REQUIRE(player.get_penalty_time() == 10);
    }

    SECTION("print and << operator") {
        std::stringstream ss;
        ss << player;

        std::string expected = "Player John Doe info:\nTime in the game: 45\nPenalty time:5\n";
        REQUIRE(ss.str() == expected);
    }

    SECTION("set_full_name") {
        player.set_full_name("Jane Doe");

        REQUIRE(player.get_full_name() == "Jane Doe");
    }
}

