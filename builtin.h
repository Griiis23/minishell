#ifndef BUILTIN_H
#define BUILTIN_H

/*
    Fichier builtin.h : En-tête des fonctions des commandes
                        internes du minishell
    Groupe : n° 17, 28
    Auteur : BOUCHARD Quentin, GREMONT Quentin, JOUGLET Grégory
    Dépendances : unistd.h, stdlib.h, string.h
 */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
  Fonction cd : Change le current working directory
      Paramètre path : chaine du chemin
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int cd(const char* path);

/*
  Fonction export : Ajoute une variable d'environnement
      Paramètre env : chaine au format NOM_VAR=VAL
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int export(const char* env);

/*
  Fonction unset : Supprime une variable d'environnement
      Paramètre env : chaine du nom de la variable
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int unset(const char* env, int fderr);

/*
  Fonction env : Affiche toute les variables d'environnement
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int env(int fdout, int fderr);

/*
  Fonction myexit : Ferme le programme
      Paramètre val : valeur de retout du programme
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int myexit(int val, int fdout, int fderr);

/*
  Fonction cwd : Affiche le path du current working directory
      Paramètre fdout : descripteur du fichier de la sortie standard
      Paramètre fderr : descripteur du fichier de la sortie d'erreur
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int cwd(int fdout, int fderr);

#endif
