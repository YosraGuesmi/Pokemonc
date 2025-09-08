#include "Pokemon.hpp"
#include <cstdlib>
#include <ctime>

Pokemon::Pokemon(int id, const std::string& name, int evolution, int max_hp, int attack, int defense)
    : id_(id), name_(name), evolution_(evolution), max_hp_(max_hp), current_hp_(max_hp),
      attack_(attack), defense_(defense) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int Pokemon::get_id() const { return id_; }
std::string Pokemon::get_name() const { return name_; }
int Pokemon::get_evolution() const { return evolution_; }
int Pokemon::get_max_hp() const { return max_hp_; }
int Pokemon::get_current_hp() const { return current_hp_; }
int Pokemon::get_attack() const { return attack_; }
int Pokemon::get_defense() const { return defense_; }

int Pokemon::attack(Pokemon& other) {
    int damage = (attack_ - other.defense_ / 2) + (std::rand() % 5);
    if (damage < 0) damage = 0;
    other.current_hp_ = (other.current_hp_ - damage > 0) ? other.current_hp_ - damage : 0;
    return damage;
}