#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>

class Pokemon {
public:
    Pokemon(int id, const std::string& name, int evolution, int max_hp, int attack, int defense);
    int get_id() const;
    std::string get_name() const;
    int get_evolution() const;
    int get_max_hp() const;
    int get_current_hp() const;
    int get_attack() const;
    int get_defense() const;
    int attack(Pokemon& other);

private:
    int id_;
    std::string name_;
    int evolution_;
    int max_hp_;
    int current_hp_;
    int attack_;
    int defense_;
};

#endif // POKEMON_HPP