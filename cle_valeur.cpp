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

void nettoyerBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// ajouter des paires
void ajouterPaire(unordered_map<string, string>& base, const string& nomFichier) {
    string cle, valeur;

    nettoyerBuffer();
    cout << "Entrez la clé (Ex : User2. Attention: la clé ne peut pas être vide) : ";
    while (true) {
        getline(cin, cle); // Lecture de l'entrée utilisateur

        if (cle.empty()) {
            cout << "Erreur : La clé ne peut pas être vide. Veuillez réessayer : ";
        } else if (base.find(cle) != base.end()) {
            cout << "Erreur : La clé \"" << cle << "\" existe déjà. Veuillez entrer une clé différente de celle que vous avez entré : ";
        } else {
            break;
        }
    }

    cout << "Entrez la valeur (Ex : admin. Attention: la valeur ne peut pas être vide) :" ;  
    while (true) {
        getline(cin, valeur);
                    
        if (valeur.empty()) {
            cout << "Erreur : La valeur ne peut pas être vide. Veuillez réessayer : ";
        } else {
            break;
        }
    }

    // Vérification de la collision
    if (base.find(cle) != base.end()) {
        cout << "La clé \"" << cle << "\" existe déjà avec la valeur \"" << base[cle] << "\".\n";
        cout << "Voulez-vous mettre à jour la valeur ? (oui ou non) : ";
        
        string choix;
        nettoyerBuffer();
        getline(cin, choix); // Lecture de la réponse oui/non
            
        if (choix == "oui" || choix == "OUI") {
            base[cle] = valeur;
            cout << "Valeur mise à jour avec succès.\n";
        } else {
            cout << "Aucune modification effectuée.\n";
        } 
            
    } else {
        base[cle] = valeur;
        cout << "Clé et valeur ajoutées avec succès ! \n";
        cout << "Résumé : \n";
        cout << "La clé " << cle << " a été ajouté avec succès.\n";
        cout << "La valeur " << valeur << " a été ajouté avec succès \n";
    }
    sauvegarderPaires(base, nomFichier); 
    ofstream fichier(nomFichier, std::ios::app);
    if (fichier.is_open()) {
        fichier << cle << "," << valeur << "\n";
        fichier.close();
        cout << "Clé/valeur ajoutée et sauvegardée dans " << nomFichier << ".\n";
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
