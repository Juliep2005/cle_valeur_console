#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>
#include "cle_valeur.h"

using namespace std;

int main() {
    unordered_map<string, string> baseDeDonnees;
    std::string nomFichier = "base_donnees.txt";

    int choix;

    do {
        afficher();
        cin >> choix;

        switch (choix) {
            case 1:
                ajoutPaire(baseDeDonnees, nomFichier);
                break;
            case 2:
                rpValeur(baseDeDonnees);
                break;
            case 3:
                supPaire(baseDeDonnees);
                break;
            case 4:
                afchePaires(baseDeDonnees);
                break;
            case 5:
                savePaires(baseDeDonnees, nomFichier);
                break;
            case 6:
                chagePaires(baseDeDonnees, nomFichier);
                break;
            case 7:
                cout << "Au revoir !\n";
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer.\n";

                
        }
    } 
    while (choix != 7 ); {

        
    }
    return 0;
}