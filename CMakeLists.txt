cmake_minimum_required(VERSION 3.21)
project(PokemonProject)

set(CMAKE_CXX_STANDARD 17)

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
)

# Définir les fichiers en-têtes (optionnel pour l'IDE)
set(HEADERS
        include/pokemon.hpp
        include/pokemon_vector.hpp
        include/pokedex.hpp
        include/pokemon_party.hpp
        include/pokemon_attack.hpp
)

# Créer l'exécutable
add_executable(PokemonProject ${SOURCES})

# Lier les bibliothèques SFML
target_link_libraries(PokemonProject sfml-graphics sfml-window sfml-system sfml-audio)

# Inclure le dossier des en-têtes du projet
target_include_directories(PokemonProject PRIVATE include)

# Copier le dossier data dans le répertoire de build
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})