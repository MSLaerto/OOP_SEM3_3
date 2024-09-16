#include "../../include/player_types/defender.h"
namespace prog{
    Defender::Defender(std::string full_name, std::size_t game_time, std::size_t penalty_time)
            : Player(full_name, game_time, penalty_time) {}

    const std::string Defender::get_type() const {
        return "Defender";
    }

    Defender::Defender(const Defender& other)
            : Player(other.full_name_, other.game_time_, other.penalty_time_){}

    Defender& Defender::operator=(const Defender& other) {
        if (this != &other) {
            full_name_ = other.full_name_;
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
        }
        return *this;
    }

    Defender::Defender(Defender&& other) noexcept{
        full_name_ = std::move(other.full_name_);
        game_time_ = other.game_time_;
        penalty_time_ = other.penalty_time_;
        other.game_time_ = 0;
        other.penalty_time_ = 0;
    }

    Defender& Defender::operator=(Defender&& other) noexcept {
        if (this != &other) {
            full_name_ = std::move(other.full_name_);
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
            other.game_time_ = 0;
            other.penalty_time_ = 0;
        }
        return *this;
    }
}