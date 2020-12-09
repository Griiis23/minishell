#include "processus.h"

/*
    Fichier process.c : En-tête des fonctions de gestion des
                        processus indépendants.
    Groupe : n° 17, 28
    Auteur : BOUCHARD Quentin, GREMONT Quentin, JOUGLET Grégory
    Dépendances : unistd.h, sys/types.h, sys/wait.h, parser.h, builtin.h
 */

/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int exec_processus(processus_t* proc) {

  // Commandes builtin
  if(strcmp(proc->argv[0],"cd") == 0) {
    return cd(proc->argv[1]);
  }

  if(strcmp(proc->argv[0],"export") == 0) {
    return export(proc->argv[1]);
  }

  if(strcmp(proc->argv[0],"unset") == 0) {
    return unset(proc->argv[1], proc->stderr);
  }

  if(strcmp(proc->argv[0],"env") == 0) {
    return env(proc->stdout, proc->stderr);
  }

  if(strcmp(proc->argv[0],"exit") == 0) {
    if(proc->argv[1] == NULL) return myexit(0, proc->stdout, proc->stderr);
    return myexit(atoi(proc->argv[1]), proc->stdout, proc->stderr);
  }

  if(strcmp(proc->argv[0],"pwd") == 0) {
    return cwd(proc->stdout, proc->stderr);
  }

  // Si n'est pas une commande builtin
  if(!(proc->pid=fork())) { //Fils
    // Remplace les fd si necessaire
    if(proc->stdin != STDIN_FILENO) {
      dup2(proc->stdin,STDIN_FILENO);
      if(proc->stdin > 2) close(proc->stdin);
    }
    if(proc->stdout != STDOUT_FILENO) {
      dup2(proc->stdout,STDOUT_FILENO);
      if(proc->stdout > 2) close(proc->stdout);
    }
    if(proc->stderr != STDERR_FILENO) {
      dup2(proc->stderr,STDERR_FILENO);
      if(proc->stderr > 2) close(proc->stderr);
    } 

    // Essaye de lancer le programme
    execvp(proc->argv[0],proc->argv);
    write(proc->stderr,"commande introuvable\n",21);
    exit(1);
  }

  // Fermeture des fd ouvert autre que les standards
  if(proc->stdin > 2) close(proc->stdin);
  if(proc->stdout > 2) close(proc->stdout);
  if(proc->stderr > 2) close(proc->stderr);

  // Si pas en arrière plan
  // Attendre la fin du fils avant de rendre la main
  if(proc->background != 1) {
    do {
      waitpid(proc->pid,&proc->wstatus, 0);
      // Tant que status n'est pas égale à terminé
    } while (!WIFEXITED(proc->wstatus) && !WIFSIGNALED(proc->wstatus));
  }

}

/*
 Fonction status_processus :  récupérer le status d'un processus (en cours,
                              terminé, ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne le "status" d'un processus lancé en arrière plan
 */
int status_processus(processus_t* proc) {
  // Met à jour proc.wstatus sans attendre
  waitpid(proc->pid,&proc->wstatus, WNOHANG);
  return proc->wstatus;
}