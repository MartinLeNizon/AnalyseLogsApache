/*************************************************************************
                           FluxLog  -  Interface
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <FluxLog> (fichier FluxLog.h) ----------------

#ifndef FLUXLOG_H
#define FLUXLOG_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>

#include "LigneLog.h"

//------------------------------------------------------------------------
// Rôle de la classe FluxLog
// Classe fille de ifstream
// Permet d'extraire les infos d'une ligne de log, et de les stocker dans une variable de type LigneLog
//------------------------------------------------------------------------

class FluxLog : public ifstream{

//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    bool getLog(LigneLog & ll);
    // Mode d'emploi :
    // Permet d'extraire les infos d'une ligne de log, et de les stocker dans une LigneLog
    // Passage par référence de la variable de type LigneLog où stocker les informations du log
    // Le retour indique si l'on est à la fin du fichier (retourne false si fin du fichier journal)
    // Contrat :
    // Pas de contraintes spécifiques

//-------------------------------------------- Constructeurs - destructeur

    FluxLog(const string & nomfichier): ifstream(nomfichier.c_str())
    // Mode d'emploi :
    // Le nom du fichier journal contenant les logs doit être entré en paramètre
    // Contrat :
    // Le fichier journal (habituellement un .txt ou un .log) doit contenir des log générés pas Apache, ayant ce format :
    // 192.168.0.0 - - [08/Sep/2012 :11:16:02 +0200] "GET /temps/4IF16.html HTTP/1.1" 200 12106 "http://intranet-if.insa-lyon.fr/temps/4IF15.html" "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1"
    {
        #ifdef MAP
            cout << "Appel au constructeur de <FluxLog>" << endl;
        #endif
    }

    virtual ~FluxLog(){
        #ifdef MAP
            cout << "Appel au destructeur de <FluxLog>" << endl;
        #endif
    }
};

#endif
