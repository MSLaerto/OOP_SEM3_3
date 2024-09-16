#define CATCH_CONFIG_MAIN
#include "../include/team.h"
#include "Catch/Catch.hpp"

TEST_CASE("Team class tests", "[Team]") {
    SECTION("Constructor test") {
        prog::Team team("Team A", "John Doe");
        REQUIRE(team.get_name() == "Team A");
        REQUIRE(team.get_coach_full_name() == "John Doe");
        REQUIRE(team.get_games().empty());
    }

    SECTION("Add game test") {
        prog::Team team("Team A", "John Doe");
        auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Team B", 11);
        team.add_game(game);
        REQUIRE(team.get_games().size() == 1);
        REQUIRE(team.get_games().begin()->second == game);
    }

    SECTION("Remove game test") {
        prog::Team team("Team A", "John Doe");
        auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Team B", 11);
        team.add_game(game);
        team.remove_game(game->get_date());
        REQUIRE(team.get_games().empty());
    }

    SECTION("Find game test") {
        prog::Team team("Team A", "John Doe");
        auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Team B", 11);
        team.add_game(game);
        auto found_game = team.find_game(game->get_date());
        REQUIRE(found_game != nullptr);
        REQUIRE(found_game == game);
    }

    SECTION("Print test") {
        prog::Team team("Team A", "John Doe");
        auto game1 = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Team B", 11);
        auto game2 = std::make_shared<prog::Game>(std::chrono::system_clock::now() + std::chrono::hours(1), "Team C", 11);
        team.add_game(game1);
        team.add_game(game2);
        std::stringstream ss;
        ss << team;
        REQUIRE(ss.str() == game1->print() + game2->print() + "\n");
    }
}