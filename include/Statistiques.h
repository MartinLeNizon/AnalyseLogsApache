/*************************************************************************
                           Statistiques  -  description
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Statistiques> (fichier Statistiques.h) ----------------

#ifndef STATISTIQUES_H
#define STATISTIQUES_H

//--------------------------------------------------- Interfaces utilisées

#include <unordered_map>
#include <string>

using namespace std;

#include "LigneLog.h"

//------------------------------------------------------------------------
// Rôle de la classe <Statistiques>
// Permet de faire des statistiques sur des lignes de log :
// Stockage pour chaque cible de ses referer ainsi que du nombre de hits associés
//------------------------------------------------------------------------

class Statistiques{

//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    void ajoutLog(LigneLog ll);
    // Mode d'emploi :
    // Mettre le log à prendre en compte en paramètre
    // Contrat :
    // Le log doit nécessairement avoir un referer et une cible

    void faireGraphe(const string fichierDot) const;
    // Mode d'emploi :
    // Mettre en paramètre le nom du fichier de sortie (extension .dot)
    // Contrat :
    // Pas de contrainte spécifique

    void afficher();
    // Mode d'emploi :
    // Affichage des 10 cibles (ou nombre de logs, si <10) les plus consultées par nombre de hits décroissant
    // Le nombre de cibles (par défaut 10) peut être modifié grâce à la constante TAILLE_TOP dans Statistiques.cpp

//-------------------------------------------- Constructeurs - destructeur

    Statistiques(string baseURL);
    // Mode d'emploi :
    // Constructeur de Statistiques à partir de la base de l'URL
    // Permettra par la suite d'enlever cette base des URLs complètes
    // Contrat :
    // baseURL du type "http://intranet-if.insa-lyon.fr"

    virtual ~Statistiques();

//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Méthodes protégées

    int compterHits(const string cible);
    // Mode d'emploi :
    // Mettre le nnom d'une cible en paramètre
    // Contrat :
    // La cible doit avoir être présente en tant que clé de l'unordered_map hits

//----------------------------------------------------- Attributs protégés

string baseURL;                                             // Base de l'URL (ex : http://intranet-if.insa-lyon.fr)
unordered_map<string, unordered_map<string, int>> hits;     // Associe - le nombre de hits associé à chaque referer - pour chaque cible

};

#endif
