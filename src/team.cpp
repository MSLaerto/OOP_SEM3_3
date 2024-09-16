#include "../include/team.h"
namespace prog{
    Team::Team(const std::string &name, const std::string &coach_full_name)
            : name_(name), coach_full_name_(coach_full_name) {}

    const std::string &Team::get_name() const {
        return name_;
    }

    const std::string &Team::get_coach_full_name() const {
        return coach_full_name_;
    }

    const std::map<std::chrono::system_clock::time_point, std::shared_ptr<Game>> &Team::get_games() const {
        return games_;
    }

    void Team::add_game(std::shared_ptr<Game> game) {
        games_.insert({game->get_date(), game});
    }

    void Team::remove_game(const std::chrono::system_clock::time_point &date) {
        auto it = games_.find(date);
        if (it != games_.end()) {
            games_.erase(it);
        } else {
            throw std::runtime_error("Game not found");
        }
    }

    std::shared_ptr<Game> Team::find_game(const std::chrono::system_clock::time_point &date) const {
        auto it = games_.find(date);
        if (it != games_.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    const std::string Team::print() const{
        std::stringstream ss;
        for(const auto &game: games_) ss << *game.second;
        return ss.str();
    }

}