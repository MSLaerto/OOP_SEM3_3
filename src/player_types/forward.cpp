#include "../../include/player_types/forward.h"
namespace prog {

    Forward::Forward(std::string full_name, std::size_t game_time, std::size_t penalty_time,
                     std::size_t shots_on_target, std::size_t shots_off_target)
            : Player(full_name, game_time, penalty_time), shots_on_target_(shots_on_target),
              shots_off_target_(shots_off_target) {}

    const std::string Forward::get_type() const {
        return "Forward";
    }

    Forward::Forward(const Forward& other)
            : Player(other.full_name_, other.game_time_, other.penalty_time_),
              shots_on_target_(other.shots_on_target_), shots_off_target_(other.shots_off_target_) {}

    Forward& Forward::operator=(const Forward& other) {
        if (this != &other) {
            full_name_ = other.full_name_;
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
            shots_on_target_ = other.shots_on_target_;
            shots_off_target_ = other.shots_off_target_;
        }
        return *this;
    }

    Forward::Forward(Forward&& other) noexcept
            : Player(std::move(other.full_name_), other.game_time_, other.penalty_time_),
              shots_on_target_(other.shots_on_target_), shots_off_target_(other.shots_off_target_) {
        other.shots_on_target_ = 0;
        other.shots_off_target_ = 0;
        other.game_time_ = 0;
        other.penalty_time_ = 0;
    }

    Forward& Forward::operator=(Forward&& other) noexcept {
        if (this != &other) {
            full_name_ = std::move(other.full_name_);
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
            shots_on_target_ = other.shots_on_target_;
            shots_off_target_ = other.shots_off_target_;
            other.game_time_ = 0;
            other.penalty_time_ = 0;
            other.shots_on_target_ = 0;
            other.shots_off_target_ = 0;
        }
        return *this;
    }

    const std::string Forward::print() const{
        std::stringstream ss;
        ss << Player::print();
        ss << "Shots on target: " << shots_on_target_ << std::endl;
        ss << "Shots off target: " << shots_off_target_ << std::endl;
        return ss.str();
    }

    std::size_t Forward::get_shots_on_target() const {
        return shots_on_target_;
    }

    std::size_t Forward::get_shots_off_target() const {
        return shots_off_target_;
    }

    void Forward::set_shots_on_target(std::size_t shots_on_target) {
        shots_on_target_ = shots_on_target;
    }

    void Forward::set_shots_off_target(std::size_t shots_off_target) {
        shots_off_target_ = shots_off_target;
    }

}