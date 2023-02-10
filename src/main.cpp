/*************************************************************************
                                    main
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

using namespace std;

//------------------------------------------------------ Include personnel

#include "../include/FluxLog.h"
#include "../include/LigneLog.h"
#include "../include/Statistiques.h"

//---------------------- Déclarations des variables définies dans <getopt>

extern char *optarg;
extern int optind;

//------------------------------------------------------------------ Types

//-------------------------------------------------- Déclarations méthodes

int lectureOptions(int argc, char * argv[], int & option, string & fichierLog, string & baseURL, bool & gFlag, string & fichierDot, bool & eFlag, bool & tFlag, string & heure);
// Mode d'emploi :
// Permet de lire les différentes options
// Retourne 1 en cas d'options incorrectes
// Contrat :
// fichierLog doit être un fichier journal existant contenant des logs Apache.
// Il faut spécifier tous les arguments.
// Il n'y a pas d'ordre spécifique dans les options

//------------------------------------------------------------------- main

int main(int argc, char * argv[]){

    int option;
    string fichierLog;
    string baseURL;
    bool gFlag = false;
    string fichierDot;
    bool tFlag = false;
    string heure = "";
    bool eFlag = false;

    if(lectureOptions(argc, argv, option, fichierLog, baseURL, gFlag, fichierDot, eFlag, tFlag, heure)!=0) return 1;

    // Permet de mettre l'option -t 7 au lieu de -t 07
    if (heure.length() == 1){
        heure = "0" + heure;
    }

    FluxLog f(fichierLog.c_str());
    if(!f){
        cerr << "ERREUR : Fichier introuvable" << endl;
        return 1;
    }

    Statistiques s(baseURL);
    LigneLog log;

    bool logAAnalyser;      // Indique si le log actuel doit être analysé ou non (en fonction des différentes options)

    while(f.getLog(log)){
        logAAnalyser = true;
        if( (eFlag && log.estImageOuJsOuCss()) || (tFlag && log.heure.find(heure)!=0) ) logAAnalyser = false;
        if(logAAnalyser) s.ajoutLog(log);
    }

    if(gFlag) s.faireGraphe(fichierDot);

    s.afficher();

    f.close();

    return 0;
}

//--------------------------------------------------- Définitions méthodes

int lectureOptions(int argc, char * argv[], int & option, string & fichierLog, string & baseURL, bool & gFlag, string & fichierDot, bool & eFlag, bool & tFlag, string & heure)
// Algorithme :
// Utilisation de <getopt.h>
{
    if(argc < 2 || argc > 9){
        cerr << "Le programme doit être utilisé de cette manière : ./analog [-g nomfichier.dot] [-e] [-t heure] -u baseURL nomfichier.log" << endl;
        return 1;
    }

    while( (option = getopt(argc, argv, "g:et:u:")) != -1 ){
        switch(option){
        case 'g':
            fichierDot = optarg;
            gFlag = true;
            break;
        case 'e': 
            eFlag = true;
            break;
        case 't':
            heure = optarg; 
            tFlag = true;
            break;
        case 'u': baseURL = optarg; break;
        default: cerr << "Le programme doit être utilisé de cette manière : ./analog [-g nomfichier.dot] [-e] [-t heure] nomfichier.log" << endl; return 1;
        }
    }

    if(optind < argc) fichierLog = argv[optind];
    else{
        cerr << "Le programme doit être utilisé de cette manière : ./analog [-g nomfichier.dot] [-e] [-t heure] nomfichier.log" << endl;
        return 1;
    }

    return 0;

}
