#include "cle_valeur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>

using namespace std;

void afficher() {
    cout << "\n=== Menu ===\n";
    cout << "1. Ajoute une paire (cle, valeur)\n";
    cout << "2. Récuperer une valeur\n";
    cout << "3. Supprimer une paire\n";
    cout << "4. Afficher toutes les paires\n";
    cout << "5. Sauvegarder les paires\n";
    cout << "6. Charger les paires\n";
    cout << "7. Quitter\n";
    cout << "Choisissez une option : ";
}

void ecran() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ajoutPaire(unordered_map<string, string>& base, const string& nomFichier) {
    string cle, valeur;

    ecran();
    cout << "Entrez la cle : ";
    while (true) {
        getline(cin, cle);
        if (cle.empty()) {
            cout << "Erreur : La cle ne peut pas etre vide  Veuillez reessayer : ";
        } else if (base.find(cle) != base.end()) {
            cout << "Erreur : La cle \"" << cle << "\" existe deja. Veuillez entrer une cle differente : ";
        } else {
            break;
        }
    }

    cout << "Entrez la valeur : ";
    while (true) {
        getline(cin, valeur);
        if (valeur.empty()) {
            cout << "Erreur : La valeur ne peut pas etre vide. Veuillez reessayer : ";
        } else {
            break;
        }
    }

    base[cle] = valeur;
    cout << "Cle et valeur ajoutes avec succes !\n";

    ofstream fichier(nomFichier, ios::app);
    if (fichier.is_open()) {
        fichier << cle << "," << valeur << "\n";
        cout << "Cle / valeur sauvegarde dans " << nomFichier << "\n";
        fichier.close();
    } else {
        cout << "Erreur : impossible d'ouvrir le fichier " << nomFichier << ".\n";
    }
}

void rpValeur(const unordered_map<string, string>& base) {
    string cle;
    cout << "Entrez la cle : ";
    cin >> cle;

    auto it = base.find(cle);
    if (it != base.end()) {
        cout << "Valeur associee : " << it->second << "\n";
    } else {
        cout << "Cle non trouve.\n";
    }
}

void supPaire(unordered_map<string, string>& base) {
    string cle;
    cout << "Entrez la cle : ";
    cin >> cle;

    if (base.erase(cle)) {
        cout << "Paire supprime avec succes !\n";
    } else {
        cout << "Cle non trouve \n";
    }
}

void afchePaires(const unordered_map<string, string>& base) {
    if (base.empty()) {
        cout << "La base de donne est vide.\n";
    } else {
        cout << "Paires (cle, valeur) :\n";
        for (const auto& paire : base) {
            cout << "Cle : " << paire.first << ", Valeur : " << paire.second << "\n";
        }
    }
}

void savePaires(const unordered_map<string, string>& base, const string& nomFichier) {
    ofstream fichier(nomFichier);
    if (!fichier) {
        cout << "Erreur lors de l'ouverture du fichier pour la sauvegarde \n";
        return;
    }

    for (const auto& paire : base) {
        fichier << paire.first << "," << paire.second << "\n";
    }
}

void chagePaires(unordered_map<string, string>& base, const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cout << "Erreur lors de l ouverture du fichier pour le chargement \n";
        return;
    }

    base.clear();
    string ligne, cle, valeur;
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);       
         if (getline(ss, cle, ",") && getline(ss, valeur)) {
            base[cle] = valeur;
        }
    }

    fichier.close();
    cout << "Paires charger avec succe depuis " << nomFichier << " \n";
}