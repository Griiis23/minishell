#include "builtin.h"
/*
    Fichier builtin.c : Implémentation des fonctions des commandes
                        internes du minishell
    Groupe : n° X
    Auteur :
    Dépendances :
 */

extern char **environ;

int cd(const char* path) {
  if(chdir(path) != 0) return 1;
  char s[1024];
  getcwd(s,1024);
  setenv("PWD",s,1);
  return 0;
}


int export(const char* env) {
  if(env==NULL) return 1;
  char s[1024];
  for (int i = 0; env[i]; ++i) s[i]=env[i];
  return putenv((char*)s);
}

int unset(const char* env, int fderr) {
  if(unsetenv(env) != 0) {
    write(fderr, "erreur\n", 7);
    return 1;
  }
  return 0;
}

int env(int fdout, int fderr) {
  if (environ == NULL) {
    write(fderr, "erreur\n", 7);
    return 1;
  }

  for (int i = 0; environ[i]; ++i)
  {
    write(fdout,environ[i],strlen(environ[i]));
    write(fdout,"\n",1);
  }

  return 0;
}

int myexit(int val, int fdout, int fderr){
  exit(0);
  exit(val);
  write(fderr, "erreur\n", 7);
  return 1;
}

int cwd(int fdout, int fderr) {
  char s[1024];
  if(getcwd(s,1024) == NULL) {
    write(fderr, "erreur\n", 7);
    return 1;
  }
  write(fdout,s,strlen(s));
  write(fdout,"\n",1);

  return 0;
  
}

