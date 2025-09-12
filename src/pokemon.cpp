#include "pokemon.hpp"
#include <algorithm>

Pokemon::Pokemon(int num, const std::string& n, int evo, int pvM, int pvA, int atk, int def)
    : numero(num), nom(n), evolution(evo), pv_max(pvM), pv_actuel(pvA), attaque_points(atk), defense(def) {  // Renommé
    pv_actuel = std::clamp(pv_actuel, 0, pv_max);
}

void Pokemon::attaque(Pokemon& cible) {
    int degats = static_cast<int>((getAttaque() - cible.getDefense()) * 0.5f);  // Utilise getter
    if (degats > 0) {
        cible.pv_actuel -= degats;
        cible.pv_actuel = std::clamp(cible.pv_actuel, 0, cible.pv_max);
    }
}