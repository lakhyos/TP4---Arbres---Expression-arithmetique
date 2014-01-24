#include "expression.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int estOperateur(char c)
{
  return c == '+' || c== '-' || c == '/' || c == '*' ;
}

Noeud Suivant_expression(char *expr, int* pos)
{
  // Type d'element qui va etre lu
  Noeud noeud;
  static TypeNeoud typeCourant = FLOAT;
  noeud.type = typeCourant;

  switch (typeCourant) {
    // Operateur
    case CHAR:
      if(!estOperateur(expr[*pos]))
        {
          printf("Erreur: expression invalide\n");
          exit(1);
        }
      noeud.valeur.operateur = expr[(*pos)++];
      break;
      // Nombre
    case FLOAT:
      {
        char *pEnd; // L'indice de la fin du nombre lu
        noeud.valeur.nombre = strtof(expr + *pos, &pEnd);
        *pos = pEnd - expr;
        break;
      }
    }

  // Changement du type
  if(expr[*pos] == '\0') typeCourant = FLOAT;
  else typeCourant = (typeCourant == FLOAT)? CHAR : FLOAT;

  return noeud;
}

Arbre* Malloc_arbre()
{
  Arbre *arbre = malloc(sizeof(Arbre));
  if(!arbre)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }
  arbre->droit = arbre->gauche = NULL;
  return arbre;
}

Arbre* Construire_arbre(char *expr)
{
  int pos = 0; // position
  Noeud noeud; // element actuel
  Arbre *courant = NULL, *racine = NULL;

  // Premier nombre
  noeud = Suivant_expression(expr, &pos);
  racine = Malloc_arbre();
  racine->valeur = noeud;

  // Premier operateur
  if(expr[pos] != '\0')
    {
      noeud = Suivant_expression(expr, &pos);
      Arbre *premier_nombre = racine;
      courant = racine = Malloc_arbre();
      racine->valeur = noeud;
      racine->gauche = premier_nombre;
    }

  while(expr[pos] != '\0')
    {
      // Nombre
      noeud = Suivant_expression(expr, &pos);
      Arbre *nombre = Malloc_arbre();
      nombre->valeur = noeud;

      // Operateur
      if(expr[pos] != '\0')
        {
          // L'operateur lu devient courant
          Arbre *ancien_courant = courant;
          noeud = Suivant_expression(expr, &pos);
          courant = Malloc_arbre();
          courant->valeur = noeud;

          if(noeud.valeur.operateur == '-' ||
             noeud.valeur.operateur == '+' )
            {
              // courant devient la nouvelle racine
              Arbre *ancien_racine = racine;
              racine = courant;
              racine->gauche = ancien_racine;

              // Mettre le nombre comme fils de ancien_courant
              if(!ancien_courant->gauche) ancien_courant->gauche = nombre;
              else ancien_courant->droit = nombre;
            }
          else // L'opérateur est '*' ou '/'
            {
              // Courant devient fils de ancien_courant
              if(!ancien_courant->gauche) ancien_courant->gauche = courant;
              else ancien_courant->droit = courant;

              // Le nombre devient fils de courant
              courant->gauche = nombre;
            }
        }
      else // Pas d'opérateur après le nombre lu
        if(!courant->gauche) courant->gauche = nombre;
        else courant->droit = nombre;
    }

  return racine;
}

float Calcule(float a, char operateur, float b)
{
  switch(operateur)
    {
    case '-': return a - b;
    case '+': return a + b;
    case '/': return a / b;
    default: return a * b;
    }
}

float Calculer_expression(Arbre *arbre)
{
  if(arbre->valeur.type == FLOAT )
    return arbre->valeur.valeur.nombre;
  else
    {
      return Calcule(Calculer_expression(arbre->gauche),
                     arbre->valeur.valeur.operateur,
                     Calculer_expression(arbre->droit));
    }
}
