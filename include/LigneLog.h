/*************************************************************************
                           LigneLog  -  Interface
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe LigneLog (fichier LigneLog.h) ----------------

#ifndef LIGNELOG_H
#define LIGNELOG_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include <iostream>

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Ensemble>
// Permet de stocker les différents éléments d'un log dans des chaînes de caractères distinctes
//------------------------------------------------------------------------

typedef struct{

//-------------------------------------------------------------- Attributs

    string ip;
    string userLogname;
    string authUser;
    string date;
    string heure;
    string difGMT;
    string action;
    string cible;
    string http;
    string status;
    string nbDonnees;
    string referer;
    string client;

    bool estImageOuJsOuCss() const
    // Mode d'emploi :
    // Renvoie true si la cible est un fichier image, js ou css
    // Contrat :
    // Pas de contraintes spécifiques
    {
        if(cible.size()>3 && cible.substr(cible.size()-3) == ".js") return true;
        if(cible.size()>4 && (cible.substr(cible.size()-4) == ".jpg" || cible.substr(cible.size()-4) == ".png" || cible.substr(cible.size()-4) == ".css" || cible.substr(cible.size()-4) == ".gif" || cible.substr(cible.size()-4) == ".bmp") ) return true;
        if(cible.size()>5 && (cible.substr(cible.size()-5) == ".jpeg") ) return true;
        return false;
    }

}LigneLog;

#endif
