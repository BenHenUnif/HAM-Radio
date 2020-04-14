
// fichier .h : contient seulement l'entête des fonctions ('h'eader en anglais)

/*
Explications en français ici :
  https://fr.wikibooks.org/wiki/Programmation_C%2B%2B/Le_pr%C3%A9processeur     (Exemple 3)
  https://fr.wikipedia.org/wiki/Include_guard
Explanation in english here https://www.deviceplus.com/arduino/arduino-preprocessor-directives-tutorial/
*/

#ifndef BIBI_H
#define BIBI_H

// prototypes de fonctions : ici on défini seulement le nom de la fonction et le type des arguments (pas le nom des arguments)
int somme_bibi(int, int);
int multi_bibi(int, int);
void affiche_page(int);   // 'void' veut dire que la fonction ne retourne PAS de valeur après avoir fait le traitement
double robot_avance(int,int,int,int,float,float);

#endif
