#include "../../include/player_types/goalkeeper.h"
namespace prog {

    Goalkeeper::Goalkeeper(std::string full_name, std::size_t game_time, std::size_t penalty_time,
                           std::size_t saves, std::size_t goals_conceded)
            : Player(full_name, game_time, penalty_time), saves_(saves), goals_conceded_(goals_conceded) {}

    const std::string Goalkeeper::get_type() const {
        return "Goalkeeper";
    }

    Goalkeeper::Goalkeeper(const Goalkeeper& other)
            : Player(other.full_name_, other.game_time_, other.penalty_time_), saves_(other.saves_), goals_conceded_(other.goals_conceded_) {}

    Goalkeeper& Goalkeeper::operator=(const Goalkeeper& other) {
        if (this != &other) {
            full_name_ = other.full_name_;
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
            saves_ = other.saves_;
            goals_conceded_ = other.goals_conceded_;
        }
        return *this;
    }

    Goalkeeper::Goalkeeper(Goalkeeper&& other) noexcept
            : Player(std::move(other.full_name_), other.game_time_, other.penalty_time_), saves_(other.saves_), goals_conceded_(other.goals_conceded_) {
        other.saves_ = 0;
        other.goals_conceded_ = 0;
        other.game_time_ = 0;
        other.penalty_time_ = 0;
    }

    Goalkeeper& Goalkeeper::operator=(Goalkeeper&& other) noexcept {
        if (this != &other) {
            full_name_ = std::move(other.full_name_);
            game_time_ = other.game_time_;
            penalty_time_ = other.penalty_time_;
            saves_ = other.saves_;
            goals_conceded_ = other.goals_conceded_;
            other.game_time_ = 0;
            other.penalty_time_ = 0;
            other.saves_ = 0;
            other.goals_conceded_ = 0;
        }
        return *this;
    }

    std::size_t Goalkeeper::get_saves() const {
        return saves_;
    }

    std::size_t Goalkeeper::get_goals_conceded() const {
        return goals_conceded_;
    }

    void Goalkeeper::set_saves(std::size_t saves) {
        saves_ = saves;
    }

    void Goalkeeper::set_goals_conceded(std::size_t goals_conceded) {
        goals_conceded_ = goals_conceded;
    }

    const std::string Goalkeeper::print() const {
        std::stringstream ss;
        ss << Player::print();
        ss << "Goals saved: " << saves_ << std::endl;
        ss << "Goals conceded: " << goals_conceded_;
        return ss.str();
    }

}