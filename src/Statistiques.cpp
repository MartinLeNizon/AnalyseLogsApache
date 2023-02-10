/*************************************************************************
                           Statistiques  -  description
                             -------------------
    début                : 20 janvier 2023
    copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
    e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Statistiques> (fichier Statistiques.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

//------------------------------------------------------ Include personnel

#include "../include/Statistiques.h"
#include "../include/LigneLog.h"

//------------------------------------------------------------- Constantes

#define TAILLE_TOP 10

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Statistiques::ajoutLog(LigneLog ll)
// Algorithme :
// Enlève les informations inutiles de la cible et du referer, puis mets à jour l'attribut de type unordered_map<string, unordered_map<string, int>> hits
{
    #ifdef MAP
        cout << "Appel à sansOption de <Statistiques>" << endl;
    #endif

    // Traitement cible
    ll.cible = ll.cible.substr(0, ll.cible.find(';'));
    ll.cible = ll.cible.substr(0, ll.cible.find('?'));

    // Traitement referer (utile uniquement si besoin du graphe)
    if (ll.referer.find(baseURL) == 0) ll.referer.erase(0, baseURL.length());

    ll.referer = ll.referer.substr(0, ll.referer.find('?'));

    // Evolution hits
    hits[ll.cible][ll.referer]++;
}

void Statistiques::faireGraphe(const string fichierDot) const
// Algorithme :
// Premier parcours complet de hits. Si le noeud relatif à la cible ou au referer n'a pas encore été traité, on rajoute la ligne "nodei [label="nomCibleOuReferer"]; dans le fichier de sortie .dot"
// Deuxième parcours complet, afin de rajouter chaque flèche : "nodei -> nodej [label="nbHits" avec nodei le noeud associé au referer, nodej associé à la cible"
{
    #ifdef MAP
        cout << "Appel a faireGraphe de <Statistiques>" << endl;
    #endif

    ofstream fichier(fichierDot);

    fichier << "digraph{" << endl;

    // Itérateurs sur hits
    unordered_map<string, unordered_map<string, int>>::const_iterator itCible = hits.begin();
    unordered_map<string, unordered_map<string, int>>::const_iterator endCible = hits.end();

    // Itérateur sur hits[cible] -> double parcours
    unordered_map<string, int>::const_iterator itReferer;
    unordered_map<string, int>::const_iterator endReferer;

    int compteurNoeuds = 0;

    unordered_set<string> noeudsFaits;      // Besoin de stocker les cibles/referer déjà traités (noeud déclaré)

    unordered_map<string, int> noeuds;

    // Premier parcours
    while(itCible != endCible){
        // Prise en compte de chaque cible
        if(noeudsFaits.count(itCible->first) == 0){
            noeuds[itCible->first] = compteurNoeuds;
            fichier << "node" << compteurNoeuds++ << " [label=\"" << itCible->first << "\"];" << endl;
            noeudsFaits.insert(itCible->first);
        }

        itReferer = itCible->second.begin();
        endReferer = itCible->second.end();

        while(itReferer != endReferer){
            // Prise en compte de chaque referer associé à chaque cible
            if(noeudsFaits.count(itReferer->first) == 0){
                noeuds[itReferer->first] = compteurNoeuds;
                fichier << "node" << compteurNoeuds++ << " [label=\"" << itReferer->first << "\"];" << endl;
                noeudsFaits.insert(itReferer->first);
            }
            itReferer++;
        }

        itCible++;
    }

    itCible = hits.begin();
    endCible = hits.end();

    // Deuxième parcours
    while(itCible != endCible){

        itReferer = itCible->second.begin();
        endReferer = itCible->second.end();

        while(itReferer != endReferer){
            fichier << "node" << noeuds[itReferer->first] << " -> node" << noeuds[itCible->first] << " [label=\"" << itReferer->second << "\"];" << endl;
            itReferer++;
        }

        itCible++;
    }

    fichier << "}";

    fichier.close();
}

int Statistiques::compterHits(const string cible)
// Algorithme :
// Parcours de hits[cible] et somme des hits pour chaque referer
{
    #ifdef MAP
        cout << "Appel à nbHits de <Statistiques>" << endl;
    #endif

    unordered_map<string, int>::const_iterator it = hits[cible].begin();
    unordered_map<string, int>::const_iterator end = hits[cible].end();

    int sum = 0;

    while(it != end){
        sum += it->second;
        it++;
    }

    return sum;
}

void Statistiques::afficher()
// Algorithme :
// On cherche la cible ayant le maximum de hits. On stocke cette cible.
// On réalise TAILLE_TOP - 1 fois :
// On cherche la cible ayant le maximum de hits n'ayant pas déjà été stockée
{
    #ifdef MAP
        cout << "Appel à afficher de <Statistiques>" << endl;
    #endif

    string topCible[TAILLE_TOP];
    int topHits[TAILLE_TOP];
    int max;
    bool inTop;

    unordered_map<string, unordered_map<string, int>>::const_iterator it;
    unordered_map<string, unordered_map<string, int>>::const_iterator end = hits.end();
    int nombreHits;

    for(int i=0; i<TAILLE_TOP; i++){
        it = hits.begin();
        max=0;
        while(it != end){
            inTop = false;

            nombreHits = compterHits(it->first);

            if(nombreHits > max){
                for(int j=0; j<TAILLE_TOP; j++){
                    if(it->first == topCible[j]){
                        inTop = true;
                    }
                }
                if(!inTop){
                    max = nombreHits;
                    topCible[i] = it->first;
                    topHits[i] = nombreHits;
                }
            }
            it++;
        }
    }

    if(topCible[0]=="") cout << "Aucun log à analyser"<< endl;

    for(int i=0; i<TAILLE_TOP; i++){
        if(topCible[i] != "") cout << i+1 << " : " << topCible[i] << " (" << topHits[i] << " hits)" << endl;
    }
}


Statistiques::Statistiques(string baseURL){
    #ifdef MAP
        cout << "Appel au constructeur de <Statistiques>" << endl;
    #endif

    this->baseURL = baseURL;
}


Statistiques::~Statistiques(){
    #ifdef MAP
        cout << "Appel au destructeur de <Statistiques>" << endl;
    #endif
}
