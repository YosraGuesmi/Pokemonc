cmake_minimum_required(VERSION 3.21)
project(PokemonStorage/pokemon)
set(CMAKE_CXX_STANDARD 17)
add_executable(pokemon main.cpp
        PokemonStorage/pokemon.cpp
        PokemonStorage/PokemonVector.cpp
        PokemonStorage/PokemonVector.hpp
        PokemonStorage/Pokedex.hpp
        PokemonStorage/Pokedex.cpp
        PokemonStorage/Pokedex.hpp
        PokemonBat/PokemonParty.hpp
        PokemonBat/PokemonParty.cpp
        PokemonBat/PokemonAttack.hpp
        PokemonBat/PokemonAttack.cpp
)
target_link_libraries(pokemon
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)
