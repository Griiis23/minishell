#include "parser.h"

/*
    Fichier parcer.c : Implémentation des fonctions de traitement de
                       la ligne de commande
    Groupe : n° 17
    Auteur :
    Dépendances :
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
    if(len > MAX_LINE_SIZE) return 1;
    
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
    while(str[i]!='\0') {
        //On ajoute un token
        tokens[nbr_token++]=str+i;
        //On deplace aux prochain caractère d'espacement 
        while(!isblank(str[i]) && str[i]!='\0') i++;
        //On met un caractère de fin de chaine
        str[i]='\0';
        i++;
    }
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
    while(tokens[i]!=NULL) {
        if(*(tokens[i])=='$') tokens[i]=getenv(tokens[i]+1);
        i++;
    }
    return 0;
}

