#include "arbre.h"
#include <stdio.h>

void Afficher_arbre(Arbre *arbre, int indent)
{
  int i;
  for(i = 0; i < (!indent? 3: indent) ; ++i) printf(" ");

  if(indent) printf("|__");
  switch(arbre->valeur.type)
    {
    case FLOAT: printf("%.2f\n", arbre->valeur.valeur.nombre); break;
    case CHAR: printf("%c\n", arbre->valeur.valeur.operateur); break;
    }


  int ajout = 3 ;

  if(arbre->gauche) Afficher_arbre(arbre->gauche, indent + ajout);
  if(arbre->droit) Afficher_arbre(arbre->droit, indent + ajout);
}
