#include "main.h"

int main()
{
    const char e = '\x82', a = '\x85' ; // e <=> 'é' ; ee <=> 'è' ; eee <=> 'ê' ; a <=> 'à'
    int i = 0, nb_track = 0 ;
    char buffer[100] = "", chemin_fichier[100] = "", nom_sortie[100] = "", stock = ' ' ;
    FILE *bpm = NULL, *liste = NULL ;

    /**INITIALISATIONS**/

    /**INFORMATIONS**/
    system ("CLS") ;
    printf ("\t\t\t\tBPM -> CSV\n\n") ;
    printf ("\n\n\tProgramme r%calis%c pour windows...\n\n", e, e) ;
    printf ("\tProgramme permettant d'envoyer les BPM calcul%cs avec le logiciel\nBPM Analyzer dans une feuille de calcul excel associ%c au titre et %c l'artiste.\n\n", e, e, a) ;
    printf ("\tPour cela, utiliser BPM Analyzer puis enregistrer les BPM dans\nun fichier texte. Placer ce fichier texte dans le dossier d'%cx%ccution du\nprogramme.\n", e, e) ;

    /**FICHIER A LIRE**/
    printf ("\n\tEntrez le nom du fichier (ex: BPM Club Rock.txt) :\n\t\t") ;
    fgets (buffer, 99, stdin) ;
    i = 0 ;
    while ((stock = buffer[i++]) != '\0' && stock != '\n' )
    {
        sprintf(chemin_fichier, "%s%c", chemin_fichier, stock) ;
    }
    bpm = fopen (chemin_fichier, "r") ;
    if (bpm == NULL)
        {
            printf ("\n\n\n\tImpossible d'ouvrir le fichier, veuillez v%crifier le nom et l'extension.\n\t%s\n\n", e, chemin_fichier) ;
            system ("PAUSE") ;
            exit (EXIT_FAILURE) ;
        }

    /**FICHIER A CREER**/
    printf ("\n\n\tEntrez %c pr%csent le nom de la feuille de calcul r%csultante :\n\t\t", a, e, e) ;
    fgets (buffer, 99, stdin) ;
    i = 0 ;
    while ((stock = buffer[i++]) != EOF && stock != '\n' )
    {
        sprintf(nom_sortie, "%s%c", nom_sortie, stock) ;
    }
    sprintf (nom_sortie, "%s.csv", nom_sortie) ;
    liste = fopen (nom_sortie, "w+") ;
    if (liste == NULL)
        {
            printf ("\n\n\n\tImpossible de cr%cer un fichier de sortie...\n\n", e) ;
            system ("PAUSE") ;
            exit (EXIT_FAILURE) ;
        }

    /**PROGRAMME PRINCIPAL**/
    fprintf (liste, "Artiste; Titre; BPM\n") ;
    nb_track = compter_tracks (bpm) ;
    rewind (bpm) ;
    for (i = 0 ; i < nb_track ; i++)
        {
            ecrire_tags (liste, bpm) ;
        }


    /**FIN DU PROGRAMME ET LIBERATIONS DE MEMOIRES**/
    fclose (bpm) ;
    fclose (liste) ;
    printf ("\n\nFin !!\n\n") ;
    system ("PAUSE") ;
    return EXIT_SUCCESS ;
}
