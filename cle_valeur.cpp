#include "cle_valeur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map> // Ajout nécessaire pour unordered_map
#include <limits> // Pour numeric_limits


using namespace std;

void afficherMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Ajouter une paire (clé, valeur)\n";
    cout << "2. Récupérer une valeur\n";
    cout << "3. Supprimer une paire\n";
    cout << "4. Afficher toutes les paires\n";
    cout << "5. Sauvegarder les paires\n";
    cout << "6. Charger les paires\n";
    cout << "7. Quitter\n";
    cout << "Choisissez une option : ";
}

// ajouter des paires
void ajouterPaire(unordered_map<string, string>& base) {
    string cle, valeur;

    do{
        cout << "Entrez la clé (Ex : User2, la clé ne eput être vide.) : \n";
        getline(cin, cle);

        if (cle.empty()) {
            cout << "Erreur : La clé ne peut pas être vide.\n";
        }
    } while (cle.empty());
    
    // Vérification de la collision
    if (base.find(cle) != base.end()) { // Correction : base.find()cle -> base.find(cle)
        cout << "La clé \"" << cle << "\" existe déjà avec la valeur \"" << base[cle] << "\".\n";
        cout << "Voulez-vous mettre à jour la valeur ? (oui ou non) : ";
        
        string choix; // Utilisation de string au lieu de char
        getline(cin, choix);
        
        if (choix == "oui" || choix == "OUI") {
            do{
                cout << "Entrez la nouvelle valeur (admin) : \n";
                getline(cin, valeur);
                if (valeur.empty()){
                    cout << "Erreur : la valeur ne peut être vide. /n ";
                } 
            } while (valeur.empty());

            base[cle] = valeur;
            cout << "Valeur mise à jour avec succès.\n";
        } else {
            cout << "Aucune modification effectuée.\n";
        }
    } else {
        do{
            cout << "Entrez la valeur (Ex : admin, ne peut être vide) : \n";
            getline(cin, valeur);
            if (valeur.empty()){
                cout << "Erreur : La valeur ne peut pas être vide.\n";
            }   
        } while (valeur.empty());

        base[cle] = valeur;
        cout << "Paire ajoutée avec succès.\n";
    }
}

void recupererValeur(const unordered_map<string, string>& base) {
    string cle;
    cout << "Entrez la clé : ";
    cin >> cle;

    auto it = base.find(cle);
    if (it != base.end()) {
        cout << "Valeur associée : " << it->second << "\n";
    } else {
        cout << "Clé non trouvée.\n";
    }
}

void supprimerPaire(unordered_map<string, string>& base) {
    string cle;
    cout << "Entrez la clé : ";
    cin >> cle;

    if (base.erase(cle)) {
        cout << "Paire supprimée avec succès !\n";
    } else {
        cout << "Clé non trouvée.\n";
    }
}

void afficherPaires(const unordered_map<string, string>& base) {
    if (base.empty()) {
        cout << "La base de données est vide.\n";
    } else {
        cout << "Paires (clé, valeur) :\n";
        for (const auto& paire : base) {
            cout << "Clé : " << paire.first << ", Valeur : " << paire.second << "\n";
        }
    }
}

void sauvegarderPaires(const unordered_map<string, string>& base, const string& nomFichier) {
    ofstream fichier(nomFichier);
    if (!fichier) {
        cout << "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n";
        return;
    }

    for (const auto& paire : base) {
        fichier << paire.first << "," << paire.second << "\n";
    }

    fichier.close();
    cout << "Paires sauvegardées avec succès dans " << nomFichier << " !\n";
}

void chargerPaires(unordered_map<string, string>& base, const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cout << "Erreur lors de l'ouverture du fichier pour le chargement.\n";
        return;
    }

    base.clear();
    string ligne, cle, valeur;
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        if (getline(ss, cle, ',') && getline(ss, valeur)) {
            base[cle] = valeur;
        }
    }

    fichier.close();
    cout << "Paires chargées avec succès depuis " << nomFichier << " !\n";
}
