#include "arbre.h"

int estOperateur(char c);

Noeud Suivant_expression(char *expr, int* pos);

Arbre* Construire_arbre(char *expression);

float Calculer_expression(Arbre *arbre);
