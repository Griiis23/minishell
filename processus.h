#ifndef PROCESSUS_H
#define PROCESSUS_H

/*
    Fichier process.h : En-tête des fonctions de gestion des
                        processus indépendants.
    Groupe : n° X
    Auteur :
    Dépendances :
 */

/*
 Structure processus_t permettant de décrire les paramètres d'un
 processus lancé ou à lancer (PID, stdin, stdout, status, ...)
    Champs XXX :
    ...
 */
typedef struct processus_t {
  
  
} processus_t;

/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int exec_processus(processus_t* proc);

/*
 Fonction status_processus :  récupérer le status d'un processus (en cours,
                              terminé, ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne le "status" d'un processus lancé en arrière plan
 */
int status_processus(processus_t* proc);

#endif
