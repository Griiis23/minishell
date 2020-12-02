#include "utils.h"

/*
    Fichier utils.h : Implémentation des fonctions utilitaires
    Groupe : n° 17
    Auteur :
    Dépendances :
 */

/*
 Fonction count_tokens :  Compte le nombre de tokens dans le tableau
                          NULL-terminated
      Paramètre tokens :  tableau NULL-terminated de chaînes de caractères
      Retourne le nombre de chaînes dans le tableau.
 */
size_t count_tokens(char* tokens[]) {
    int i=0;
    while(tokens[i] != NULL) i++;
    return i;
}

/*
  Fonction clear_tokens : Vide le tableau tokens
      Paramètre tokens : le tableau à réinitialiser
      Retourne le pointeur sur le tableau ou NULL en cas d'erreur
 */
char** clear_tokens(char* tokens[]) {
    int i=0;
    //On remplace tous les éléments par NULL
    while(tokens[i] != NULL) {
        tokens[i]==NULL;
        i++;
    }
    return tokens;
}

/*
  Fonction insert : Insert les éléments de elts dans tokens à partir
                    de la position pos
      Paramètre tokens : le tableau dans lequel on insert les valeurs
      Paramètre elts : le tableau des éléments à insérer
      Paramètre pos : la position à laquelle on insert les éléments
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char** insert(char* tokens[], char* elts[], size_t pos) {
    size_t size_elts = count_tokens(elts);
    size_t size_tokens = count_tokens(tokens);
    //On déplace les élements de tokens entre pos et size_tokens à l'index pos+size_elts
    memmove(tokens+pos+size_elts,tokens+pos,(size_tokens-pos)*sizeof(char*));
    //On copie les éléments de elts dans tokens à l'index pos
    for (int i = 0; i < size_elts; ++i) tokens[i+pos]=elts[i];
    return tokens;
}

/*
  Fonction del_token : Supprime un élément dans tokens
      Paramètre tokens : le tableau duquel on veut retirer l'élément
      Paramètre pos : la position de l'élément à supprimer
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char** del_token(char* tokens[], size_t pos) {
    size_t size_tokens = count_tokens(tokens);
    //On déplace tous les élements de tokens à partir de pos+1 à l'index pos 
    memmove(tokens+pos,tokens+pos+1,(size_tokens-pos)*sizeof(char*));
    return tokens;
}
