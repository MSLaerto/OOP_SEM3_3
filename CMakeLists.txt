cmake_minimum_required(VERSION 3.22)
project(MLab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(MLab3 main.cpp include/player_types/forward.h include/player.h tests/Catch/Catch.hpp
        src/player_types/forward.cpp src/player.cpp include/player_types/goalkeeper.h src/player_types/goalkeeper.cpp
        include/player_types/defender.h src/player_types/defender.cpp include/game.h src/game.cpp include/team.h src/team.cpp
        include/service.h src/service.cpp Application/include/visuals.h Application/src/visuals.cpp Application/include/controller.h
        Application/src/controller.cpp)

add_executable(defender_tests tests/defender_tests.cpp include/player_types/defender.h include/player.h tests/Catch/Catch.hpp
        src/player_types/defender.cpp src/player.cpp)

add_executable(goalkeeper_tests tests/goalkeeper_tests.cpp include/player_types/goalkeeper.h include/player.h tests/Catch/Catch.hpp
        src/player_types/goalkeeper.cpp src/player.cpp)

add_executable(forward_tests tests/forward_tests.cpp include/player_types/forward.h include/player.h tests/Catch/Catch.hpp
        src/player_types/forward.cpp src/player.cpp)

add_executable(game_tests tests/game_tests.cpp include/player_types/forward.h include/player.h tests/Catch/Catch.hpp
        src/player_types/forward.cpp src/player.cpp include/player_types/goalkeeper.h src/player_types/goalkeeper.cpp
        include/player_types/defender.h src/player_types/defender.cpp include/game.h src/game.cpp)

add_executable(team_tests tests/team_tests.cpp include/player_types/forward.h include/player.h tests/Catch/Catch.hpp
        src/player_types/forward.cpp src/player.cpp include/player_types/goalkeeper.h src/player_types/goalkeeper.cpp
        include/player_types/defender.h src/player_types/defender.cpp include/game.h src/game.cpp include/team.h src/team.cpp)

add_executable(service_tests tests/service_tests.cpp include/player_types/forward.h include/player.h tests/Catch/Catch.hpp
        src/player_types/forward.cpp src/player.cpp include/player_types/goalkeeper.h src/player_types/goalkeeper.cpp
        include/player_types/defender.h src/player_types/defender.cpp include/game.h src/game.cpp include/team.h src/team.cpp
        include/service.h src/service.cpp)

add_executable(map_tests tests/map_tests.cpp map/map.h)