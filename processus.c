#include "processus.h"

/*
    Fichier process.h : En-tête des fonctions de gestion des
                        processus indépendants.
    Groupe : n° 17
    Auteur : 
    Dépendances :
 */

/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int exec_processus(processus_t* proc) {
  if(!(proc->pid==fork())) {
    dup2(proc->stdin,STDIN_FILENO);
    dup2(proc->stdout,STDOUT_FILENO);
    dup2(proc->stderr,STDERR_FILENO);
    close(proc->stdin);
    close(proc->stdout);
    close(proc->stderr);
    execvp(proc->argv[0],proc->argv);
    return 1;
  }
  if(proc->background == 0) wait(&proc->wstatus);

}

/*
 Fonction status_processus :  récupérer le status d'un processus (en cours,
                              terminé, ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne le "status" d'un processus lancé en arrière plan
 */
int status_processus(processus_t* proc) {
  if(proc->background == 1) return proc->wstatus;
  else return -1;
}