#ifndef POKEDEX_H
#define POKEDEX_H

#include "pokemon.hpp"
#include <vector>
#include <map>
#include <string>

class Pokedex {
public:
    static Pokedex& getInstance();
    static void destroyInstance();
    ~Pokedex();
    Pokemon* clone(int num) const;
    size_t size() const { return pokemons.size(); }

private:
    Pokedex();
    std::vector<Pokemon*> pokemons;
    std::map<int, Pokemon*> lookup;
    static Pokedex* instance;
};

#endif // POKEDEX_H