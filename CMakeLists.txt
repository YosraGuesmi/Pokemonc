cmake_minimum_required(VERSION 3.21)
project(PokemonStorage/pokemon)
set(CMAKE_CXX_STANDARD 17)
<<<<<<< HEAD
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
=======

# Définir les fichiers sources
set(SOURCES
        src/pokemon.cpp
        src/pokemon_vector.cpp
        src/pokedex.cpp
        src/pokemon_party.cpp
        src/pokemon_attack.cpp
        main.cpp
        include/GameContext.hpp
        include/state.hpp
        include/ExplorationState.hpp
        include/AccueilState.hpp
        src/GameContext.cpp
        src/state.cpp
        src/ExplorationState.cpp
        src/AccueilState.cpp
        include/RencontreState.hpp
        src/RencontreState.cpp
        include/CaptureSuccesState.hpp
        src/CaptureSuccesState.cpp
        include/CombatState.hpp
        src/CombatState.cpp
        include/GameOverState.hpp
        src/GameOverState.cpp
        include/BattleState.hpp
        src/BattleState.cpp
        include/BattleSystem.hpp
        src/BattleSystem.cpp
>>>>>>> 8c74afb (Sauvegarde avant pull)
)
target_link_libraries(pokemon
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)
