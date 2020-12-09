#include "builtin.h"
/*
    Fichier builtin.c : Implémentation des fonctions des commandes
                        internes du minishell
    Groupe : n° 17, 28
    Auteur : BOUCHARD Quentin, GREMONT Quentin, JOUGLET Grégory
    Dépendances : unistd.h, stdlib.h, string.h
 */

extern char **environ;

/*
  Fonction cd : Change le current working directory
      Paramètre path : chaine du chemin
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int cd(const char* path) {
  // Essaye de changer le current directory
  if(chdir(path) != 0) return 1;
  // Met a jour la variable d'env PWD
  char s[1024];
  getcwd(s,1024);
  setenv("PWD",s,1);
  return 0;
}

/*
  Fonction export : Ajoute une variable d'environnement
      Paramètre env : chaine au format NOM_VAR=VAL
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int export(const char* env) {
  if(env==NULL) return 1;
  // Copie la variable sur le tas et l'ajoute au tableau d'env
  char* s = malloc(sizeof(char)*1024);
  for (int i = 0; env[i]; ++i) s[i]=env[i];
  return putenv((char*)s);
}

/*
  Fonction unset : Supprime une variable d'environnement
      Paramètre env : chaine du nom de la variable
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int unset(const char* env, int fderr) {
  // Essaye d'unset env
  if(unsetenv(env) != 0) {
    write(fderr, "erreur\n", 7);
    return 1;
  }
  return 0;
}


/*
  Fonction env : Affiche toute les variables d'environnement
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int env(int fdout, int fderr) {
  // Verifie si le tableau existe
  if (environ == NULL) {
    write(fderr, "erreur\n", 7);
    return 1;
  }

  // Ecrit toute les variables d'environnement
  for (int i = 0; environ[i]; ++i)
  {
    write(fdout,environ[i],strlen(environ[i]));
    write(fdout,"\n",1);
  }

  return 0;
}


/*
  Fonction myexit : Ferme le programme
      Paramètre val : valeur de retout du programme
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int myexit(int val, int fdout, int fderr){
  exit(val);
  write(fderr, "erreur\n", 7);
  return 1;
}

/*
  Fonction cwd : Affiche le path du current working directory
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int cwd(int fdout, int fderr) {
  char s[1024];
  // Recupère le path du cwd dans s
  if(getcwd(s,1024) == NULL) {
    write(fderr, "erreur\n", 7);
    return 1;
  }
  // Affiche
  write(fdout,s,strlen(s));
  write(fdout,"\n",1);

  return 0;
  
}

