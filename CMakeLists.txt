cmake_minimum_required(VERSION 3.21)
project(pokemon)
set(CMAKE_CXX_STANDARD 17)
add_executable(pokemon main.cpp
        pokemon.cpp
        PokemonVector.cpp
        PokemonVector.hpp
        Pokedex.hpp
        Pokedex.cpp
        Pokedex.hpp
        PokemonParty.hpp
        PokemonParty.cpp
        PokemonAttack.hpp
        PokemonAttack.cpp
)
target_link_libraries(pokemon
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)
