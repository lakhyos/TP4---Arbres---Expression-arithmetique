#ifndef ARBRE_H
#define ARBRE_H

/*
 * Type de données stocké dans les noeud de l'arbre
 */
typedef union
{
    float nombre;
    char operateur;
} ValeurNoeud;

/* Indique le type stocker dans un noeud de l'arbre
 * Float pour un nombre et char pour un opérateur
 */
typedef enum {FLOAT, CHAR} TypeNeoud;

/*
 * Noeud de l'arbre
 */
typedef struct
{
    ValeurNoeud valeur;
    TypeNeoud type;
}Noeud;

/*
 *  Structure de l'arbre
 */
typedef struct Arbre
{
  Noeud valeur;
  struct Arbre *gauche, *droit;
}Arbre;

/*
 * Nom de la fonction: Malloc_arbre
 * Sorties :
 *    Arbre *arbre : L'arbre alloué
 * Description:
 *    Fait l'allocation et l'initialisation d'une variable Arbre
 */
Arbre* Malloc_arbre();

/*
 * Nom de la fonction: Afficher_arbre
 * Entrées :
 *    Arbre *arbre : Un arbre binaire
 *    int indent : Indentation
 * Description:
 *    Affiche un arbre binaire
 */
void Afficher_arbre(Arbre *arbre, int indent);
#endif
