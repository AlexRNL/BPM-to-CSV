#include "main.h"

//Fonction qui renvoie le nombre de chansons dans le fichier BPM :
int compter_tracks (FILE *bpm)
{
    int nb_tracks = 0 ;
    char stok = ' ' ;
    rewind (bpm) ;
    while ( (stok = getc (bpm)) != EOF)
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
    int n_bpm = 0 ;
    float f_bpm = 0.0 ;
    char titre[1000] = "", artiste[1000] = "" ;

    avancer_fichier (bpm) ; //On fait avancer le curseur virtuel jusqu'à avoir passer le chemin du mp3.
    fscanf_tab (bpm, titre) ; //On scanne le titre.
    fscanf_tab (bpm, artiste) ; //On scanne l'artiste.
    fscanf (bpm, "%f\n", &f_bpm) ; //On scanne le BPM.
    arrondir (&f_bpm, 2) ; //On arrondit les BPM.
    n_bpm = (int) f_bpm ;
    fprintf (liste, "%s; %s; %f\n", artiste, titre, f_bpm) ; //On écrit le tout dans le fichier .csv.
}

//Fonction qui arrondit un float :
void arrondir (float *mise, int precision)
{
    float test = pow (10, precision) * *mise ;
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
            stock[i] = getc (fichier) ;
        }
    stock[4] = '\0' ;

    while (strcmp (".mp3", stock))
        {
            for (i = 0 ; i < 3 ; i++)
                {
                    stock[i] = stock[i+1] ;
                }
            stock[3] = getc (fichier) ;
        }
    stock[0] = getc (fichier) ;
}

//Fonction qui scanne le titre (ou l'artiste) en entier jusqu'à la pochaine tabulation
void fscanf_tab (FILE *fichier, char champs[])
{
    char stock = ' ' ;
    while ( (stock = getc (fichier)) != '\t')
        {
            sprintf (champs, "%s%c", champs, stock) ;
        }
}
