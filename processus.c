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
    pid_t pid_fils;
    if(!(pid_fils==fork())) {
        if(proc->background != 1){
            dup2(proc->stdin,0);
            dup2(proc->stdout,1);
            dup2(proc->stderr,2);
            close(proc->stdin);
            close(proc->stdout);
            close(proc->stderr);
            execv (proc->argv[1],proc->argv);
        }
        else{
            execv (proc->argv[1],proc->argv);
        }
        return 0;
    }
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

int main(int argc, char const *argv[])
{
    processus_t proc;
    return 0;
}