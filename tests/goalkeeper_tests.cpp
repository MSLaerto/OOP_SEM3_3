#define CATCH_CONFIG_MAIN
#include "../include/player_types/goalkeeper.h"
#include "Catch/Catch.hpp"

TEST_CASE("Goalkeeper class tests", "[Goalkeeper]") {
    SECTION("Constructors and assignment operators") {
        prog::Goalkeeper goalkeeper1("John Doe", 45, 5, 10, 2);

        SECTION("Copy constructor") {
            prog::Goalkeeper goalkeeper2(goalkeeper1);
            REQUIRE(goalkeeper2.get_full_name() == "John Doe");
            REQUIRE(goalkeeper2.get_game_time() == 45);
            REQUIRE(goalkeeper2.get_penalty_time() == 5);
            REQUIRE(goalkeeper2.get_saves() == 10);
            REQUIRE(goalkeeper2.get_goals_conceded() == 2);
        }

        SECTION("Copy assignment operator") {
            prog::Goalkeeper goalkeeper2;
            goalkeeper2 = goalkeeper1;
            REQUIRE(goalkeeper2.get_full_name() == "John Doe");
            REQUIRE(goalkeeper2.get_game_time() == 45);
            REQUIRE(goalkeeper2.get_penalty_time() == 5);
            REQUIRE(goalkeeper2.get_saves() == 10);
            REQUIRE(goalkeeper2.get_goals_conceded() == 2);
        }

        SECTION("Move constructor") {
            prog::Goalkeeper goalkeeper2(std::move(goalkeeper1));
            REQUIRE(goalkeeper2.get_full_name() == "John Doe");
            REQUIRE(goalkeeper2.get_game_time() == 45);
            REQUIRE(goalkeeper2.get_penalty_time() == 5);
            REQUIRE(goalkeeper2.get_saves() == 10);
            REQUIRE(goalkeeper2.get_goals_conceded() == 2);
        }

        SECTION("Move assignment operator") {
            prog::Goalkeeper goalkeeper2;
            goalkeeper2 = std::move(goalkeeper1);
            REQUIRE(goalkeeper2.get_full_name() == "John Doe");
            REQUIRE(goalkeeper2.get_game_time() == 45);
            REQUIRE(goalkeeper2.get_penalty_time() == 5);
            REQUIRE(goalkeeper2.get_saves() == 10);
            REQUIRE(goalkeeper2.get_goals_conceded() == 2);
        }
    }

    SECTION("get_type function") {
        prog::Goalkeeper goalkeeper("John Doe", 45, 5, 10, 2);
        REQUIRE(goalkeeper.get_type() == "Goalkeeper");
    }

    SECTION("print function") {
        prog::Goalkeeper goalkeeper("John Doe", 45, 5, 10, 2);
        std::stringstream ss;
        ss << goalkeeper;

        std::string expected = "Player John Doe info:\nTime in the game: 45\nPenalty time:5\nGoals saved: 10\nGoals conceded: 2";
        REQUIRE(ss.str() == expected);
    }

    SECTION("set_saves and set_goals_conceded functions") {
        prog::Goalkeeper goalkeeper("John Doe", 45, 5, 10, 2);
        goalkeeper.set_saves(12);
        goalkeeper.set_goals_conceded(1);

        REQUIRE(goalkeeper.get_saves() == 12);
        REQUIRE(goalkeeper.get_goals_conceded() == 1);
    }
}