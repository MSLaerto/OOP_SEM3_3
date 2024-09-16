#include "../include/player.h"
namespace prog {
    Player::Player(std::string full_name, std::size_t game_time, std::size_t penalty_time)
            : full_name_(full_name), game_time_(game_time), penalty_time_(penalty_time) {}

    void Player::set_game_time(std::size_t new_time) {
        game_time_ = new_time;
    }

    void Player::set_penalty_time(std::size_t new_time) {
        penalty_time_ = new_time;
    }

    std::size_t Player::get_game_time() const {
        return game_time_;
    }

    std::size_t Player::get_penalty_time() const {
        return penalty_time_;
    }

    const std::string Player::print() const {
        std::stringstream ss;
        ss << "Player " << full_name_ << " info:" << std::endl
        << "Time in the game: " << game_time_ << std::endl
        << "Penalty time:" << penalty_time_ << std::endl;
        return ss.str();
    }

    std::ostream& operator<<(std::ostream& os, const Player& player){
        os << player.print();
        return os;
    }

    void Player::set_full_name(const std::string& name){
        full_name_ = name;
    }

    const std::string& Player::get_full_name() const{
        return full_name_;
    }
}