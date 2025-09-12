#pragma once
#include "pokemon.hpp"
#include <vector>

class PokemonVector {
protected:
    std::vector<Pokemon*> pokemons;

public:
    virtual ~PokemonVector();
    virtual void add(Pokemon* p) = 0;
    virtual Pokemon* remove(int index) = 0;
    size_t size() const { return pokemons.size(); }
    Pokemon* get(int i) const {
        if (i >= 0 && static_cast<size_t>(i) < pokemons.size()) return pokemons[i];
        return nullptr;
    }
};