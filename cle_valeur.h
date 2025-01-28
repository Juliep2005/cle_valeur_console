#ifndef CLE_VALEUR_H
#define CLE_VALEUR_H

#include <unordered_map>
#include <iostream>
#include <string>

void afficherMenu();
void nettoyerBuffer();
void ajouterPaire(std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);
void recupererValeur(const std::unordered_map<std::string, std::string>& base);
void supprimerPaire(std::unordered_map<std::string, std::string>& base);
void afficherPaires(const std::unordered_map<std::string, std::string>& base);
void sauvegarderPaires(const std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);
void chargerPaires(std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);

#endif