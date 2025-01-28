#include "cle_valeur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>

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

void nettoyerBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ajouterPaire(unordered_map<string, string>& base, const string& nomFichier) {
    string cle, valeur;

    nettoyerBuffer();
    cout << "Entrez la clé : ";
    while (true) {
        getline(cin, cle);

        if (cle.empty()) {
            cout << "Erreur : La clé ne peut pas être vide. Veuillez réessayer : ";
        } else if (base.find(cle) != base.end()) {
            cout << "Erreur : La clé \"" << cle << "\" existe déjà. Veuillez entrer une clé différente : ";
        } else {
            break;
        }
    }

    cout << "Entrez la valeur : ";
    while (true) {
        getline(cin, valeur);
        if (valeur.empty()) {
            cout << "Erreur : La valeur ne peut pas être vide. Veuillez réessayer : ";
        } else {
            break;
        }
    }

    // Ajouter la paire clé-valeur
    base[cle] = valeur;
    cout << "Clé et valeur ajoutées avec succès !\n";

    // Vérification pour éviter d'écrire des doublons dans le fichier
    ofstream fichier(nomFichier, std::ios::app);
    if (fichier.is_open()) {
        // Vérifier si la clé existe déjà dans le fichier
        string ligne;
        bool existeDeja = false;
        ifstream fichierExist(nomFichier);
        while (getline(fichierExist, ligne)) {
            if (ligne.substr(0, ligne.find(',')) == cle) {
                existeDeja = true;
                break;
            }
        }
        fichierExist.close();

        // Écrire dans le fichier seulement si la clé n'existe pas déjà
        if (!existeDeja) {
            fichier << cle << "," << valeur << "\n";
            cout << "Clé/valeur sauvegardée dans " << nomFichier << ".\n";
        } else {
            cout << "La clé \"" << cle << "\" existe déjà dans le fichier. Aucune sauvegarde effectuée.\n";
        }

        fichier.close();
    } else {
        cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << ".\n";
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