#ifndef CMDLINE_H
#define CMDLINE_H

/*
    Fichier cmdline.h : En-tête des fonctions de gestion de
                        la ligne de commande.
    Groupe : n° 17, 28
    Auteur : BOUCHARD Quentin, GREMONT Quentin, JOUGLET Grégory
    Dépendances : fcntl.h, stdio.h, processus.h, parser.h, utils.h
 */

#include <fcntl.h>
#include <stdio.h>

#include "processus.h"
#include "parser.h"
#include "utils.h"



/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
      Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int init_process(processus_t* proc, char* tokens[]);

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */
int exec_cmdline(processus_t* proc);



#endif

