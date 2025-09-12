### Code Improvements
- Logic Correction for Health Points: Updated the logic to prevent negative health points in pokemon.cpp, specifically in lines 23 to 30.
- Unified add_pokemon Method: The add_pokemon method is consistent across the PokemonParty and Pokedex classes, and it is only overridden in PokemonAttack.
    - Therefore, I added a definition for add_pokemon in PokemonVector.cpp, specifically in lines 3 to 5.
    - Unnecessary definitions have been removed.

### Code Organization
- Missing README: There is no README file available.
- File Organization: The files are not well-organized into folders, which would improve structure and navigation.
- .gitignore Configuration: The .gitignore file should exclude all files that can be regenerated through compilation or within the IDE.