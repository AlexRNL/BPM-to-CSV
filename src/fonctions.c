#include "fonctions.h"
#include <math.h>
#include <string.h>

//Fonction qui renvoie le nombre de chansons dans le fichier BPM :
int compter_tracks (FILE *bpm)
{
    int nb_tracks = 0 ;
    char stok = ' ' ;
    rewind (bpm) ;
    while ( (stok = (char) getc (bpm)) != EOF)
        {
            if (stok == '\n')
                {
                    nb_tracks++ ;
                }
        }
    return nb_tracks ;
}

//Fonction qui écrit les tags d'un chanson dans le .csv :
void ecrire_tags (FILE *liste, FILE *bpm)
{
    double f_bpm = 0.0 ;
    char titre[1000] = "", artiste[1000] = "" ;

    avancer_fichier (bpm) ; //On fait avancer le curseur virtuel jusqu'à avoir passer le chemin du mp3.
    fscanf_tab (bpm, titre) ; //On scanne le titre.
    fscanf_tab (bpm, artiste) ; //On scanne l'artiste.
    fscanf (bpm, "%lf\n", &f_bpm) ; //On scanne le BPM.
    arrondir (&f_bpm, 2) ; //On arrondit les BPM.
    fprintf (liste, "%s; %s; %f\n", artiste, titre, f_bpm) ; //On écrit le tout dans le fichier .csv.
}

//Fonction qui arrondit un double :
void arrondir (double *mise, int precision)
{
    double test = pow (10, precision) * *mise ;
    if (test - (int) test >= 0.5)
        {
            *mise = ( (int) test + 1) / pow (10, precision) ;
        }
    else
        {
            *mise = ( (int) test) / pow (10, precision) ;
        }
}

//Fonction qui fait avancer le curseur jusqu'après le chemin (après le ".mp3" :
void avancer_fichier (FILE *fichier)
{
    int i ;
    char stock[5] = "" ;

    //On prends les premier caractères pour tester une première fois :
    for (i = 0 ; i < 4 ; i++)
        {
            stock[i] = (char) getc (fichier) ;
        }
    stock[4] = '\0' ;

    while (strcmp (".mp3", stock))
        {
            for (i = 0 ; i < 3 ; i++)
                {
                    stock[i] = stock[i+1] ;
                }
            stock[3] = (char) getc (fichier) ;
        }
    stock[0] = (char) getc (fichier) ;
}

//Fonction qui scanne le titre (ou l'artiste) en entier jusqu'à la pochaine tabulation
void fscanf_tab (FILE *fichier, char champs[])
{
    char stock = ' ' ;
    while ( (stock = (char) getc (fichier)) != '\t')
        {
            append_char (champs, stock) ;
        }
}

// Fonction qui ajoute un caractère à une chaîne
void append_char(char *dest, char c)
{
    size_t len = strlen(dest) ;
    dest[len] = c ;
    dest[len+1] = '\0' ;
}
