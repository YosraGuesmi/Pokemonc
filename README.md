## Overview
This project is a Pokémon selection and battle simulator built using SFML (Simple and Fast Multimedia Library) in C++. It allows users to select up to 6 Pokémon from a Pokedex, view their team, and engage in a battle against an opponent party.

## Dependencies
- **SFML**: Version 2.x (for graphics, window management, and input handling).
- **C++ Standard Library**: Includes `<iostream>`, `<vector>`, `<cmath>`, `<random>`, `<map>`, `<string>`, and `<algorithm>`.

## Project Structure
- **include/**: Header files for the project.
    - `pokedex.hpp`: Manages the Pokedex instance and Pokémon data.
    - `pokemon_party.hpp`: Handles the player's and opponent's Pokémon party.
    - `pokemon_attack.hpp`: Defines Pokémon attack mechanics.
    - `BattleSystem.hpp`: Manages the battle system logic.
- **src/**: Source files for implementation.
    - Corresponding `.cpp` files for each header in `include/`.
- **data/images/**: Directory containing Pokémon images (e.g., `1.png`, `background.png`).
- **pokedex.csv**: CSV file containing Pokémon data.

## How to Run
1. Ensure SFML is installed and configured in your development environment.
2. Compile the project using a C++ compiler (e.g., g++ or Clang) with SFML linked.
3. Run the executable. The program will:
    - Load the Pokedex and initialize a window.
    - Allow selection of up to 6 Pokémon using mouse clicks.
    - Display the selected team and start a battle mode upon pressing Enter (with 6 selections) and Space.

## Features
- **Pokedex Loading**: Loads Pokémon data and displays the total count.
- **Selection Interface**: Scrollable grid to select Pokémon, with a maximum of 6 selections.
- **Battle System**: Simulates a turn-based battle with random opponent Pokémon.
- **Graphics**: Uses SFML for rendering Pokémon images, text, and backgrounds, with fallback textures if loading fails.
- **Error Handling**: Includes try-catch blocks for exception handling and fallback mechanisms for missing assets.

## Controls
- **Mouse**: Click to select/deselect Pokémon; scroll to navigate the grid.
- **Keyboard**:
    - `Space`: Proceed from welcome screen or start battle.
    - `Enter`: Confirm selection (requires 6 Pokémon).
    - `Up/Down`: Scroll the Pokémon grid.
- **Mouse Wheel**: Scroll the Pokémon grid.

## Notes
- Ensure all image files (e.g., `.png` files in `data/images/`) and font files (e.g., `arial.ttf`) are in the correct paths.
- The program uses a fallback color (magenta) for missing textures and a default font if specified fonts are unavailable.
- Memory management is handled with manual deletion of `BattleSystem` and `Pokedex` instances.

## Troubleshooting
- If textures or fonts fail to load, check file paths and permissions.
- Errors during execution will be printed to `std::cerr` with details.

For further development or modifications, refer to the source files in `src/` and headers in `include/`.