#include "Pokedex.hpp"
#include "PokemonParty.hpp"
#include "PokemonAttack.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        Pokedex& pokedex = Pokedex::get_instance();
        PokemonParty party;
        Pokemon* bulbasaur = pokedex.clone_pokemon(1);
        Pokemon* charmander = pokedex.clone_pokemon(4);
        if (bulbasaur && charmander) {
            party.add_pokemon(*bulbasaur);
            party.add_pokemon(*charmander);
            delete bulbasaur;
            delete charmander;
        } else {
            std::cerr << "Error: Unable to clone Pokemon from Pokedex.\n";
            return 1;
        }

        std::cout << "PokemonParty size: " << party.size() << "\n";
        for (size_t i = 0; i < party.size(); ++i) {
            const Pokemon* p = party.get_pokemon(i);
            if (p) {
                std::cout << "Pokemon " << i << ": " << p->get_name()
                          << ", HP: " << p->get_current_hp() << "/" << p->get_max_hp()
                          << ", Attack: " << p->get_attack()
                          << ", Defense: " << p->get_defense() << "\n";
            }
        }

        std::vector<int> indices = {0, 1};
        PokemonAttack attack_team(party, indices);

        const Pokemon* p1_const = attack_team.get_pokemon(0);
        const Pokemon* p2_const = attack_team.get_pokemon(1);
        if (p1_const && p2_const) {
            Pokemon p1(*p1_const);
            Pokemon p2(*p2_const);
            std::cout << "\n" << p1.get_name() << " attacks " << p2.get_name() << "!\n";
            int damage = p1.attack(p2);
            std::cout << p2.get_name() << " takes " << damage << " damage, HP now: "
                      << p2.get_current_hp() << "/" << p2.get_max_hp() << "\n";
        } else {
            std::cerr << "Error: Unable to retrieve Pokemon for attack.\n";
            return 1;
        }

        attack_team.reintegrate_to_party(party);
        std::cout << "\nPokemonParty size after reintegration: " << party.size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}