#pragma once
#include <string>

class Pokemon {
private:
    int numero;
    std::string nom;
    int evolution = 0;
    int pv_max;
    int pv_actuel;
    int attaque_points;  // Renommé pour éviter conflit
    int defense;

public:
    Pokemon(int num, const std::string& n, int evo = 0, int pvM = 100, int pvA = 100, int atk = 50, int def = 50);
    ~Pokemon() = default;
    void attaque(Pokemon& cible);  // Méthode OK maintenant

    // Getters mis à jour
    int getNumero() const { return numero; }
    std::string getNom() const { return nom; }
    int getEvolution() const { return evolution; }
    int getPvMax() const { return pv_max; }
    int getPvActuel() const { return pv_actuel; }
    void setPvActuel(int pv) { pv_actuel = pv; }
    int getAttaque() const { return attaque_points; }
    int getDefense() const { return defense; }
};