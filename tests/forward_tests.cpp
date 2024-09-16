#define CATCH_CONFIG_MAIN
#include "../include/player_types/forward.h"
#include "Catch/Catch.hpp"

TEST_CASE("Forward class tests", "[Forward]") {
    SECTION("Constructors and assignment operators") {
        prog::Forward forward1("John Doe", 45, 5, 10, 2);

        SECTION("Copy constructor") {
            prog::Forward forward2(forward1);
            REQUIRE(forward2.get_full_name() == "John Doe");
            REQUIRE(forward2.get_game_time() == 45);
            REQUIRE(forward2.get_penalty_time() == 5);
            REQUIRE(forward2.get_shots_on_target() == 10);
            REQUIRE(forward2.get_shots_off_target() == 2);
        }

        SECTION("Copy assignment operator") {
            prog::Forward forward2;
            forward2 = forward1;
            REQUIRE(forward2.get_full_name() == "John Doe");
            REQUIRE(forward2.get_game_time() == 45);
            REQUIRE(forward2.get_penalty_time() == 5);
            REQUIRE(forward2.get_shots_on_target() == 10);
            REQUIRE(forward2.get_shots_off_target() == 2);
        }

        SECTION("Move constructor") {
            prog::Forward forward2(std::move(forward1));
            REQUIRE(forward2.get_full_name() == "John Doe");
            REQUIRE(forward2.get_game_time() == 45);
            REQUIRE(forward2.get_penalty_time() == 5);
            REQUIRE(forward2.get_shots_on_target() == 10);
            REQUIRE(forward2.get_shots_off_target() == 2);
        }

        SECTION("Move assignment operator") {
            prog::Forward forward2;
            forward2 = std::move(forward1);
            REQUIRE(forward2.get_full_name() == "John Doe");
            REQUIRE(forward2.get_game_time() == 45);
            REQUIRE(forward2.get_penalty_time() == 5);
            REQUIRE(forward2.get_shots_on_target() == 10);
            REQUIRE(forward2.get_shots_off_target() == 2);
        }
    }

    SECTION("get_type function") {
        prog::Forward forward("John Doe", 45, 5, 10, 2);
        REQUIRE(forward.get_type() == "Forward");
    }

    SECTION("print function") {
        prog::Forward forward("John Doe", 45, 5, 10, 2);
        std::stringstream ss;
        ss << forward;

        std::string expected = "Player John Doe info:\nTime in the game: 45\nPenalty time:5\nShots on target: 10\nShots off target: 2\n";
        REQUIRE(ss.str() == expected);
    }

    SECTION("set_shots_on_target and set_shots_off_target functions") {
        prog::Forward forward("John Doe", 45, 5, 10, 2);
        forward.set_shots_on_target(12);
        forward.set_shots_off_target(1);

        REQUIRE(forward.get_shots_on_target() == 12);
        REQUIRE(forward.get_shots_off_target() == 1);
    }
}