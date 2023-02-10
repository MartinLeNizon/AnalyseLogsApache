/*************************************************************************
                           FluxLog  -  description
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <FluxLog> (fichier FluxLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <istream>

using namespace std;

//------------------------------------------------------ Include personnel

#include "../include/FluxLog.h"
#include "../include/LigneLog.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool FluxLog::getLog(LigneLog & ll)
// Algorithme :
// Distinction des différents éléments grâce aux éléments remarquables dans le format des logs Apache
{
    #ifdef MAP
        cout << "Appel à getLog de <FluxLog>" << endl;
    #endif


    string poubelle;    // Permet de lire les caractère "inutiles" (ne contenant pas d'informations essentielles sur le log)

    std::getline(*this, ll.ip, ' ');
    std::getline(*this, ll.userLogname, ' ');
    std::getline(*this, ll.authUser, ' ');
    std::getline(*this, poubelle, '[');
    std::getline(*this, ll.date, ':');
    std::getline(*this, ll.heure, ' ');
    std::getline(*this, ll.difGMT, ']');
    std::getline(*this, poubelle, '"');
    std::getline(*this, ll.action, ' ');
    std::getline(*this, ll.cible, ' ');
    std::getline(*this, ll.http, '"');
    std::getline(*this, poubelle, ' ');
    std::getline(*this, ll.status, ' ');
    std::getline(*this, ll.nbDonnees, ' ');
    std::getline(*this, poubelle, '"');
    std::getline(*this, ll.referer, '"');
    std::getline(*this, poubelle, '"');
    std::getline(*this, ll.client, '"');
    std::getline(*this, poubelle);

    if(this->eof()) return false;

    return true;
}
