#ifndef FONCTIONSH
#define FONCTIONSH

#include <stdio.h>

// Prototype des fonctions :
int compter_tracks (FILE *bpm) ;
void ecrire_tags (FILE *liste, FILE *bpm) ;
void arrondir (float *mise, int precision) ;
void avancer_fichier(FILE *fichier) ;
void fscanf_tab (FILE *fichier, char champs[]) ;

#endif
