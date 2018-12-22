*********************************************************
*			NINJATTACK			*
*********************************************************


Projet réalisé dans le cadre de l'ue LIFAP4

///////// MEMBRES DU GROUPE /////////

-> KRIMI IMRAN P1610419
-> DEVILLERS ALEXANDRE P1608591
-> AZOUI AYMEN P1612255

///////// LIEN DU GIT /////////

https://forge.univ-lyon1.fr/p1612255/Ninjattack

///////// COMMANDE DE COMPILATION /////////

Depuis le fichier racine
Linux : 	make		pour toutes les versions
		make sdl	pour le jeu en graphique	./bin/Ninjattack.exx
		make txt	pour le jeu en txt		./bin/NinjattackTxt.exx
		make sanssdl	pour le jeu sans interface	./bin/NinjattackSansSDL.exx

Windows : 	Il faut lancer le projet code blocks (le .cbp)
		pour le jeu en graphique, il faut désactiver mainNonSDL et mainText et activer main
		pour le jeu en txt il faut désactiver mainNonSDL et main et activer mainText
		pour le jeu sanssdl il faut désactiver main et mainText et activer mainNonSDL
		il est possible qu'il faille aller dans Settings->Compiler->c++11 et cocher la case
		avant de compiler

//////// COMMANDES DU JEU /////////

-> Pour se déplacer à DROITE : [D]

-> Pour se déplacer à GAUCHE : [Q]

-> Pour SAUTER : [Z] ou [ESPACE]

-> Pour le DOUBLE SAUT : Appuyer deux fois ou laisser appuyer sur [Z] ou [ESPACE]

-> Pour lancer des shurikens à la suite : [CLIQUE_GAUCHE]

-> Pour lancer des shurikens en SPRAY : [CLIQUE_DROIT]

-> Pour DASH : [SHIFT] (Possibilité de re-DASH après avoir éleminer un ennemi)

//////// BUT DU JEU /////////

Le but du jeu est d'arriver à l'autre bout de la carte

en éleminant tout les ennemis sans perdre toute sa vie,

et avant que le score n'arrive à ZERO.

//////// FICHIERS /////////


-> Dossier src : Contient tout les .h et .cpp necéssaire pour le jeu

-> Dossier data : Contient toutes les images, maps et srpites

-> Dossier obj : Contient tout les .o

-> Dossier include : Contient la librairie SDL2

-> Dossier extern : Contient les extentions de SDL2


//////// CARTE ////////


Les cartes sont des fichiers texte ou les premiere ligne est constitué de :
DIMENSION_X DIMENSION_Y
CARACTERE_TUILES_DUR
CARACTERE_TUILES_LIQUIDE

Et ensuite la map représenté sous forme de caractere pour les textures

Exemple complet :
4 4
/
~
/~~/
/~~/
/~~/
////

Ici ça ferait une mini piscine avec 2*3 tuiles d'eau