#include "parser.h"

/*
    Fichier parcer.c : Implémentation des fonctions de traitement de
                       la ligne de commande
    Groupe : n° 17, 28
    Auteur : BOUCHARD Quentin, GREMONT Quentin, JOUGLET Grégory
    Dépendances : string.h, ctype.h, stdlib.h
*/


/*
  Fonction trim_str : Supprime les caractères d'espacement (' ' et '\t') au
                      début et à la fin de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int trim_str(char* str) {
  int i=0;
  int len = strlen(str);

  //On compte le nombre de blanc au debut
  while(isblank(str[i])) i++;
  //On deplace de i caractère vers la gauche
  memmove(str,str+i,len-i+1);

  //On remplace tous les blancs par des \0 a la fin
  i=strlen(str)-1;
  while(isblank(str[i])) str[i--]='\0';

  return 0;

}

/*
  Fonction clean_str :  Supprime les doublons de caractères d'espacement (' '
                        et '\t') à l'intérieur de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int clean_str(char* str) { 
  char temp[MAX_LINE_SIZE];
  int j=0;

  // Recopie la ligne sans les doublons
  for(int i=0; i<strlen(str); i++) {
    if(!(isblank(str[i]) && isblank(str[i+1]))) temp[j++]=str[i];
  }
  temp[j]='\0';
  strcpy(str, temp);
  return 0;
}

/*
  Fonction tokenize_str : Découpe la ligne sur les caractères d'espacement
                          (' ' et '\t') et enregistre les pointeurs sur le
                          début de chaque mot dans tokens (NULL-terminated)
      Paramètre str : la chaîne à découper
      Paramètre tokens : le tableau dans lequel stocker les éléments de str
      Retourne le nombre de chaînes dans tokens
 */
int tokenize_str(char* str, char* tokens[]) {
  int nbr_token = 0;
  int i = 0;
  while(str[i]!='\0' && str[i]!='\n') {
    //On ajoute un token
    tokens[nbr_token++]=str+i;
    //On deplace i aux prochain caractère d'espacement 
    while(!isblank(str[i]) && str[i]!='\0' && str[i]!='\n') i++;
    //On remplace par un caractère de fin de chaine
    str[i]='\0';
    //On passe au prochain token
    i++;
  }
  // On ajoute NULL a la fin
  tokens[nbr_token]=NULL;

  return nbr_token;
}



/*
  Fonction env_str :  Remplace les noms des variables d'environnement par
                      leur contenu dans tokens (terminé par NULL)
      Paramètre tokens : le tableau dans lequel les substitutions sont faites
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int env_str(char* tokens[]) {
  int i=0;
  // Pour chaque token
  while(tokens[i]!=NULL) {
    // Si le 1 charactère est $ remplace par le token par var
    if(*(tokens[i])=='$') tokens[i]=getenv(tokens[i]+1);
    i++;
  }
  return 0;
}

