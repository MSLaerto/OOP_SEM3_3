#include "../include/game.h"

namespace prog {

    Game::Game(const std::chrono::system_clock::time_point &date, const std::string &opponent_team,
               std::size_t quantity, const std::vector<std::shared_ptr<Player>> &players)
            : date_(date), opponent_team_(opponent_team), quantity_(quantity), players_(players) {}

    Game::Game(std::size_t year, std::size_t month, std::size_t day, std::size_t hour, std::size_t minute,
               const std::string &opponent_team, std::size_t quantity, const std::vector<std::shared_ptr<Player>> &players)
            : opponent_team_(opponent_team),
              quantity_(quantity), players_(players) {
        if (quantity_ == 0) {
            throw std::invalid_argument("Quantity cannot be zero");
        }

        std::tm tm = {};
        tm.tm_year = static_cast<int>(year) - 1900;
        tm.tm_mon = static_cast<int>(month) - 1;
        tm.tm_mday = static_cast<int>(day);
        tm.tm_hour = static_cast<int>(hour);
        tm.tm_min = static_cast<int>(minute);
        tm.tm_sec = 0;
        tm.tm_isdst = -1;

        std::time_t t = std::mktime(&tm);
        if (t == -1) {
            throw std::invalid_argument("Invalid date or time");
        }

        date_ = std::chrono::system_clock::from_time_t(t);
    }

    Game::Game(const Game &other)
            : date_(other.date_), opponent_team_(other.opponent_team_), quantity_(other.quantity_), players_(other.players_) {}

    Game& Game::operator=(const Game &other) {
        if (this != &other) {
            date_ = other.date_;
            opponent_team_ = other.opponent_team_;
            quantity_ = other.quantity_;
            players_ = other.players_;
        }
        return *this;
    }

    Game::Game(Game &&other) noexcept
            : date_(std::move(other.date_)), opponent_team_(std::move(other.opponent_team_)), quantity_(other.quantity_), players_(std::move(other.players_)) {}

    Game& Game::operator=(Game &&other) noexcept {
        if (this != &other) {
            date_ = std::move(other.date_);
            opponent_team_ = std::move(other.opponent_team_);
            quantity_ = other.quantity_;
            players_ = std::move(other.players_);
        }
        return *this;
    }

    Game::~Game() = default;

    const std::chrono::system_clock::time_point &Game::get_date() const {
        return date_;
    }

    const std::string &Game::get_opponent_team() const {
        return opponent_team_;
    }

    const std::vector<std::shared_ptr<Player>> &Game::get_players() const {
        return players_;
    }

    std::size_t Game::get_quantity() const {
        return quantity_;
    }

    void Game::set_date(const std::chrono::system_clock::time_point &date) {
        date_ = date;
    }

    void Game::set_opponent_team(const std::string &opponent_team) {
        opponent_team_ = opponent_team;
    }

    void Game::add_player(std::shared_ptr<Player> player) {
        if (players_.size() >= quantity_) {
            throw std::runtime_error("Cannot add more players to the game: maximum quantity reached");
        }
        players_.push_back(player);
    }

    void Game::remove_player(const std::string& name) {
        auto it = std::find_if(players_.begin(), players_.end(),
                               [&name](const std::shared_ptr<Player>& player) {
                                   return player->get_full_name() == name;
                               });
        if (it == players_.end()) {
            throw std::runtime_error("Cannot find player with name " + name);
        }
        players_.erase(it);
    }

    void Game::set_quantity(std::size_t quantity){
        quantity_ = quantity;
    }

    const std::string Game::print() const {
        std::stringstream ss;
        ss << format_date(date_) << " - Opponent: " << opponent_team_ << std::endl;
        for (const auto &player: players_) ss << *player;
        return ss.str();
    }

}