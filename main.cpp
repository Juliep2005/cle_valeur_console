#include <iostream>
#include <unordered_map>
#include "cle_valeur.h"

using namespace std;

int main() {
    unordered_map<string, string> baseDeDonnees;
    string nomFichier = "base_donnees.txt";
    int choix;

    do {
        afficherMenu();
        cin >> choix;

        switch (choix) {
            case 1:
                ajouterPaire(baseDeDonnees);
                break;
            case 2:
                recupererValeur(baseDeDonnees);
                break;
            case 3:
                supprimerPaire(baseDeDonnees);
                break;
            case 4:
                afficherPaires(baseDeDonnees);
                break;
            case 5:
                sauvegarderPaires(baseDeDonnees, nomFichier);
                break;
            case 6:
                chargerPaires(baseDeDonnees, nomFichier);
                break;
            case 7:
                cout << "Au revoir !\n";
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer.\n";
        }
    } while (choix != 7);

    return 0;
}
