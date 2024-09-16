#include "../include/service.h"
namespace prog {
    Service::Service(Team &team)
            : team_(team) {}

    void Service::add_game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team,
                           std::size_t quantity, const std::vector<std::shared_ptr<Player>> &players) {
        auto game = std::make_shared<Game>(date, opponent_team, quantity, players);
        team_.add_game(game);
    }

    void Service::remove_game(const std::chrono::system_clock::time_point &date) {
        team_.remove_game(date);
    }

    void Service::modify_game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team,
                              std::size_t quantity) {
        auto game = team_.find_game(date);
        if (game != nullptr) {
            game->set_opponent_team(opponent_team);
            game->set_quantity(quantity);
        } else {
            throw std::runtime_error("Game not found");
        }
    }

    std::size_t Service::calculate_total_penalty_time(const std::chrono::system_clock::time_point &date) const {
        auto game = team_.find_game(date);
        if (game != nullptr) {
            std::size_t total_penalty_time = 0;
            for (const auto &player : game->get_players()) {
                total_penalty_time += player->get_penalty_time();
            }
            return total_penalty_time;
        } else {
            throw std::runtime_error("Game not found");
        }
    }

    std::string Service::print_players_info() const {
        std::stringstream ss;
        ss << "Team: " << team_.get_name() << std::endl;
        ss << "Trainer: " << team_.get_coach_full_name() << std::endl;
        ss << team_;
        return ss.str();
    }

    std::map<std::string, std::pair<std::string, std::size_t>> Service::get_most_active_players_single_threaded() const {
        std::map<std::string, std::pair<std::string, std::size_t>> player_times;

        for (const auto& game : team_.get_games()) {
            for (const auto& player : game.second->get_players()) {
                auto name = player -> get_full_name();
                if(player_times.contains(name)){
                    player_times[name].second += player->get_game_time();
                }
                else player_times[name] = {player->get_type(), player->get_game_time()};
            }
        }

        std::map<std::string, std::pair<std::string, std::size_t>> most_active_players{
                {"Defender", {"", 0}},
                {"Goalkeeper", {"", 0}},
                {"Forward", {"", 0}}
        };

        for (const auto& player_time : player_times) {
            if(most_active_players[player_time.second.first].second < player_time.second.second)
                most_active_players[player_time.second.first] = {player_time.first, player_time.second.second};
        }

        return most_active_players;
    }

    std::map<std::string, std::pair<std::string, std::size_t>> Service::get_most_active_players_multithreaded(std::size_t num_threads) const {
        if (num_threads == 0) {
            throw std::invalid_argument("Number of threads must be greater than 0");
        }

        std::map<std::chrono::system_clock::time_point, std::shared_ptr<Game>> games = team_.get_games();

        std::size_t game_count = games.size();
        std::size_t chunk_size = game_count / num_threads;

        std::vector<std::future<std::map<std::string, std::pair<std::string, std::size_t>>>> futures;
        std::vector<std::thread> threads;

        auto it = games.begin();
        for (std::size_t i = 0; i < num_threads; ++i) {
            std::size_t chunk_games_count = (i == num_threads - 1) ? game_count - i * chunk_size : chunk_size;
            auto chunk_end = std::next(it, chunk_games_count);

            std::packaged_task<std::map<std::string, std::pair<std::string, std::size_t>>()> task(
                    [begin = it, end = chunk_end]() {
                        std::map<std::string, std::pair<std::string, std::size_t>> player_times;
                        for (auto it = begin; it != end; ++it) {
                            for (const auto &player : it->second->get_players()) {
                                auto name = player->get_full_name();
                                if (player_times.contains(name)) {
                                    player_times[name].second += player->get_game_time();
                                } else {
                                    player_times[name] = {player->get_type(), player->get_game_time()};
                                }
                            }
                        }
                        return player_times;
                    }
            );

            futures.push_back(task.get_future());
            threads.push_back(std::thread(std::move(task)));

            it = chunk_end;
        }

        // Объединяем все словари, суммируя игроков, если они уже встречались
        std::map<std::string, std::pair<std::string, std::size_t>> combined_player_times;
        for (std::size_t i = 0; i < num_threads; ++i) {
            threads[i].join();
            auto player_times = futures[i].get();
            for (const auto &player_time : player_times) {
                if (combined_player_times.contains(player_time.first)) {
                    combined_player_times[player_time.first].second += player_time.second.second;
                } else {
                    combined_player_times[player_time.first] = player_time.second;
                }
            }
        }

        std::map<std::string, std::pair<std::string, std::size_t>> most_active_players{
                {"Defender", {"", 0}},
                {"Goalkeeper", {"", 0}},
                {"Forward", {"", 0}}
        };

        for (const auto &player_time : combined_player_times) {
            if (most_active_players[player_time.second.first].second < player_time.second.second) {
                most_active_players[player_time.second.first] = {player_time.first, player_time.second.second};
            }
        }

        return most_active_players;
    }
}