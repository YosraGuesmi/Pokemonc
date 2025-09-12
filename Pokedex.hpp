#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include "PokemonVector.hpp"
#include <string>

class Pokedex : public PokemonVector {
public:
    static Pokedex& get_instance();
    Pokedex(const Pokedex&) = delete;
    Pokedex& operator=(const Pokedex&) = delete;
    const Pokemon* get_pokemon(int index) const override;
    size_t size() const override { return pokemons_.size(); }
    Pokemon* clone_pokemon(int id);

private:
    Pokedex();
    void load_from_csv(const std::string& filename);
};

#endif // POKEDEX_HPP