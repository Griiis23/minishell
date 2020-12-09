#include "cmdline.h"

/*
    Fichier cmdline.c : Implémentation des fonctions de gestion de
                        la ligne de commande.
    Groupe : n° X
    Auteur :
    Dépendances :
 */


/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
      Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int init_process(processus_t* proc, char* tokens[]) {
  for (int i=0;i< MAX_ARGS;++i)
  {
    clear_tokens(proc[i].argv);
    proc[i].stdin=0;
    proc[i].stdout=1;
    proc[i].stderr=2;
    proc[i].next=NULL;
    proc[i].next_success=NULL;
    proc[i].next_failure=NULL;
    proc[i].background=0;
  }
  int proc_idx=0;
  int tok_idx=0;
  int i=0;

  while(tokens[tok_idx] != NULL)
  {
    if(strcmp(tokens[tok_idx],"<") == 0){
      int fd = open (tokens[tok_idx+1],O_RDONLY);
      proc[proc_idx].stdin = fd;
      tok_idx+=2;
      continue;
    }

    if(strcmp(tokens[tok_idx],">") == 0){
      int fd = open (tokens[tok_idx+1],O_WRONLY | O_CREAT | O_TRUNC, 00664);
      proc[proc_idx].stdout = fd;
      tok_idx+=2;
      continue;
    }


    if(strcmp(tokens[tok_idx],">>") == 0){
      int fd = open (tokens[tok_idx+1],O_WRONLY | O_CREAT | O_APPEND, 00664);
      proc[proc_idx].stdout = fd;
      tok_idx+=2;
      continue;
    }

    if(strcmp(tokens[tok_idx],"2>") == 0){
      int fd = open (tokens[tok_idx+1],O_WRONLY | O_CREAT | O_TRUNC, 00664);
      proc[proc_idx].stderr = fd;
      tok_idx+=2;
      continue;
    }

    if(strcmp(tokens[tok_idx],"2>>") == 0){
      int fd = open (tokens[tok_idx+1],O_WRONLY | O_CREAT | O_APPEND, 00664);
      proc[proc_idx].stderr = fd;
      tok_idx+=2;
      continue;
    }

    if(strcmp(tokens[tok_idx],">&2") == 0){
      proc[proc_idx].stdout = proc[proc_idx].stderr;
      tok_idx++;
      continue;
    }

    if(strcmp(tokens[tok_idx],"2>&1") == 0){
      proc[proc_idx].stderr = proc[proc_idx].stdout;
      tok_idx++;
      continue;
    }

    if(strcmp(tokens[tok_idx], "|") == 0)
    {
      proc[proc_idx].background = 1;
      int fd[2];
      pipe(fd);
      proc[proc_idx].stdout = fd[1];
      proc[proc_idx+1].stdin = fd[0];
      proc[proc_idx].next = & proc[proc_idx+1];
      ++proc_idx;
      i=0;
      ++tok_idx;
      continue;
    }

    if(strcmp(tokens[tok_idx], "&&") == 0)
    {
      proc[proc_idx].next_success = & proc[proc_idx+1];
      ++proc_idx;
      i=0;
      ++tok_idx;
      continue;
    }

    if(strcmp(tokens[tok_idx], "||") == 0)
    {
      proc[proc_idx].next_failure = & proc[proc_idx+1];
      ++proc_idx;
      i=0;
      ++tok_idx;
      continue;
    }

    if(strcmp(tokens[tok_idx], ";") == 0)
    {
      proc[proc_idx].next = & proc[proc_idx+1];
      ++proc_idx;
      i=0;
      ++tok_idx;
      continue;
    }

    if(strcmp(tokens[tok_idx], "&") == 0)
    {
      proc[proc_idx].background = 1;
      proc[proc_idx].next = & proc[proc_idx+1];
      ++proc_idx;
      i=0;
      ++tok_idx;
      continue;
    }

    proc[proc_idx].argv[i++] = tokens[tok_idx++];
  }
}

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */

int exec_cmdline(processus_t* proc) {
  processus_t* p = proc;

  while(p != NULL && p->argv[0] != NULL) {
    exec_processus(p);

    if(p->next_success!=NULL && WEXITSTATUS(p->wstatus)==0) {
      p=p->next_success;
      continue;
    }

    if(p->next_failure!=NULL && WEXITSTATUS(p->wstatus)>=1 ) {
      p=p->next_failure;
      continue;
    }

    p=p->next;
  }

}


int main(int argc, char const *argv[])
{
  
  char buffer[MAX_LINE_SIZE];
  char* tokens[MAX_ARGS];
  processus_t proc[MAX_ARGS];


  while(1) {
    printf("%s$ ", getenv("PWD"));
    fgets(buffer, MAX_LINE_SIZE, stdin);
    trim_str(buffer);
    clean_str(buffer);
    tokenize_str(buffer,tokens);
    env_str(tokens);
    init_process(proc,tokens);
    exec_cmdline(proc);
    clear_tokens(tokens);

  }


  return 0;
}