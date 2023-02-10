# Analyse de logs Apache

## Utilisation

bin/analog nomfichier.log -u url [options]

Liste les 10 documents les plus consultés par ordre décroissant de popularité.

### Options :

[-g nomfichier.dot] Génère un fichier au format GraphViz du graphe analysé

[-e] Exclut les documents de type image, css ou javascript

[-t heure] Prends uniquement les hits dans le créneau horaire [heure, heure+1[

## Variables d'environnement

Pour exécuter l'application en mode debug, modifier le Makefile et modifier la variable DEBUG = yes.

## Auteurs

- Aziza BELLAHBIB
    aziza.bellahbib@insa-lyon.fr

- Martin NIZON-DELADOEUILLE
    martin.nizon-deladoeuille@insa-lyon.fr
    [@MartinLeNizon](https://github.com/MartinLeNizon)
