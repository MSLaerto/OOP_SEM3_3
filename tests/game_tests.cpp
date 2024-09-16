#define CATCH_CONFIG_MAIN
#include "../include/game.h"
#include "../include/player_types/forward.h"
#include "../include/player_types/defender.h"
#include "../include/player_types/goalkeeper.h"
#include "Catch/Catch.hpp"

TEST_CASE("Game class tests", "[Game]") {
    using namespace std::chrono;
    using namespace prog;

    SECTION("Constructors and assignment operators") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game1(date, opponent_team, quantity);

        SECTION("Copy constructor") {
            Game game2(game1);
            REQUIRE(game2.get_date() == date);
            REQUIRE(game2.get_opponent_team() == opponent_team);
            REQUIRE(game2.get_quantity() == quantity);
            REQUIRE(game2.get_players().empty());
        }

        SECTION("Copy assignment operator") {
            Game game2;
            game2 = game1;
            REQUIRE(game2.get_date() == date);
            REQUIRE(game2.get_opponent_team() == opponent_team);
            REQUIRE(game2.get_quantity() == quantity);
            REQUIRE(game2.get_players().empty());
        }

        SECTION("Move constructor") {
            Game game2(std::move(game1));
            REQUIRE(game2.get_date() == date);
            REQUIRE(game2.get_opponent_team() == opponent_team);
            REQUIRE(game2.get_quantity() == quantity);
            REQUIRE(game2.get_players().empty());
        }

        SECTION("Move assignment operator") {
            Game game2;
            game2 = std::move(game1);
            REQUIRE(game2.get_date() == date);
            REQUIRE(game2.get_opponent_team() == opponent_team);
            REQUIRE(game2.get_quantity() == quantity);
            REQUIRE(game2.get_players().empty());
        }
    }

    SECTION("set_date function") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game(date, opponent_team, quantity);
        game.set_date(date + hours(1));
        REQUIRE(game.get_date() == date + hours(1));
    }

    SECTION("set_opponent_team function") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game(date, opponent_team, quantity);
        game.set_opponent_team("Team B");
        REQUIRE(game.get_opponent_team() == "Team B");
    }

    SECTION("add_player function") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game(date, opponent_team, quantity);
        auto player = std::make_shared<Defender>("John Doe", 45, 5);
        game.add_player(player);
        REQUIRE(game.get_players().size() == 1);
        REQUIRE(game.get_players()[0]->get_full_name() == "John Doe");
    }

    SECTION("remove_player function") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game(date, opponent_team, quantity);
        auto player = std::make_shared<Defender>("John Doe", 45, 5);
        game.add_player(player);
        game.remove_player("John Doe");
        REQUIRE(game.get_players().empty());
    }

    SECTION("print function") {
        system_clock::time_point date = system_clock::now();
        std::string opponent_team = "Team A";
        std::size_t quantity = 10;
        Game game(date, opponent_team, quantity);
        auto player = std::make_shared<Defender>("John Doe", 45, 5);
        game.add_player(player);
        std::stringstream ss;
        ss << game;
        std::string expected = format_date(date) + " - Opponent: Team A\n" + player->print() + "\n";
        REQUIRE(ss.str() == expected);
    }
}