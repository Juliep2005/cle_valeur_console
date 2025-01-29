#ifndef CLE_VALEUR_H
#define CLE_VALEUR_H

#include <unordered_map>
#include <iostream>
#include <string>

void afficher();
void ecran();
void ajoutPaire(std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);
void rpValeur(const std::unordered_map<std::string, std::string>& base);
void supPaire(std::unordered_map<std::string, std::string>& base);
void afchePaires(const std::unordered_map<std::string, std::string>& base);
void savePaires(const std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);
void chagePaires(std::unordered_map<std::string, std::string>& base, const std::string& nomFichier);

#endif