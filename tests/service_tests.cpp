#define CATCH_CONFIG_MAIN
#include "../include/service.h"
#include "../include/player_types/forward.h"
#include "../include/player_types/defender.h"
#include "../include/player_types/goalkeeper.h"
#include "Catch/Catch.hpp"

TEST_CASE("Service: get_most_active_players_single_threaded") {
    // Создаем команду
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto defender1 = std::make_shared<prog::Defender>("Defender 1", 10, 1);
    auto defender2 = std::make_shared<prog::Defender>("Defender 2", 20, 2);
    auto goalkeeper1 = std::make_shared<prog::Goalkeeper>("Goalkeeper 1", 30, 3);
    auto forward1 = std::make_shared<prog::Forward>("Forward 1", 40, 4);
    auto forward2 = std::make_shared<prog::Forward>("Forward 2", 50, 5);

    auto game1 = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent 1", 3);
    game1->add_player(defender1);
    game1->add_player(goalkeeper1);
    game1->add_player(forward1);

    auto game2 = std::make_shared<prog::Game>(std::chrono::system_clock::now() + std::chrono::hours(1), "Opponent 2", 3);
    game2->add_player(defender2);
    game2->add_player(goalkeeper1);
    game2->add_player(forward2);

    team.add_game(game1);
    team.add_game(game2);

    // Получаем самых активных игроков
    auto most_active_players = service.get_most_active_players_single_threaded();

    // Проверяем результаты
    REQUIRE(most_active_players["Defender"].first == "Defender 2");
    REQUIRE(most_active_players["Defender"].second == 20);
    REQUIRE(most_active_players["Goalkeeper"].first == "Goalkeeper 1");
    REQUIRE(most_active_players["Goalkeeper"].second == 60);
    REQUIRE(most_active_players["Forward"].first == "Forward 2");
    REQUIRE(most_active_players["Forward"].second == 50);
}

TEST_CASE("Service: get_most_active_players_multithreaded") {
    // Создаем команду
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    // Создаем игроков
    auto defender1 = std::make_shared<prog::Defender>("Defender 1", 10, 1);
    auto defender2 = std::make_shared<prog::Defender>("Defender 2", 20, 2);
    auto goalkeeper1 = std::make_shared<prog::Goalkeeper>("Goalkeeper 1", 30, 3);
    auto forward1 = std::make_shared<prog::Forward>("Forward 1", 40, 4);
    auto forward2 = std::make_shared<prog::Forward>("Forward 2", 50, 5);

    // Создаем игры
    auto game1 = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent 1", 3);
    game1->add_player(defender1);
    game1->add_player(goalkeeper1);
    game1->add_player(forward1);

    auto game2 = std::make_shared<prog::Game>(std::chrono::system_clock::now() + std::chrono::hours(1), "Opponent 2", 3);
    game2->add_player(defender2);
    game2->add_player(goalkeeper1);
    game2->add_player(forward2);

    // Добавляем игры в команду
    team.add_game(game1);
    team.add_game(game2);

    // Получаем самых активных игроков
    auto most_active_players = service.get_most_active_players_multithreaded();

    // Проверяем результаты
    REQUIRE(most_active_players["Defender"].first == "Defender 2");
    REQUIRE(most_active_players["Defender"].second == 20);
    REQUIRE(most_active_players["Goalkeeper"].first == "Goalkeeper 1");
    REQUIRE(most_active_players["Goalkeeper"].second == 60);
    REQUIRE(most_active_players["Forward"].first == "Forward 2");
    REQUIRE(most_active_players["Forward"].second == 50);
}

TEST_CASE("Service: add_game") {
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent", 1);
    service.add_game(game->get_date(), "Opponent", 1);

    REQUIRE(team.get_games().size() == 1);
}

TEST_CASE("Service: remove_game") {
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent", 1);
    team.add_game(game);

    service.remove_game(game->get_date());

    REQUIRE(team.get_games().size() == 0);
}

TEST_CASE("Service: modify_game") {
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent", 1);
    team.add_game(game);

    service.modify_game(game->get_date(), "New Opponent", 2);

    REQUIRE(team.get_games().size() == 1);
    REQUIRE(team.get_games().begin()->second->get_opponent_team() == "New Opponent");
    REQUIRE(team.get_games().begin()->second->get_quantity() == 2);
}

TEST_CASE("Service: calculate_total_penalty_time") {
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent", 3);
    game->add_player(std::make_shared<prog::Defender>("Defender", 1, 10));
    game->add_player(std::make_shared<prog::Goalkeeper>("Goalkeeper", 2, 20, 10));
    game->add_player(std::make_shared<prog::Forward>("Forward", 3, 30, 30));

    team.add_game(game);

    auto total_penalty_time = service.calculate_total_penalty_time(game->get_date());

    REQUIRE(total_penalty_time == 60);
}

TEST_CASE("Service: print_players_info") {
    prog::Team team("Test Team", "Test Trainer");
    prog::Service service(team);

    auto game = std::make_shared<prog::Game>(std::chrono::system_clock::now(), "Opponent", 3);
    game->add_player(std::make_shared<prog::Defender>("Defender", 1, 10));
    game->add_player(std::make_shared<prog::Goalkeeper>("Goalkeeper", 2, 20, 10));
    game->add_player(std::make_shared<prog::Forward>("Forward", 3, 30, 30));

    team.add_game(game);

    auto players_info = service.print_players_info();
    std::cout << players_info;
}