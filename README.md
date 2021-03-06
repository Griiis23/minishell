# Projet PSI : minishell

Ce projet consiste en la réalisation d’un shell Unix très élémentaire, permettant au minimum :

* De se déplacer dans les répertoires
```bash
$ cd dir
```
* De quitter le shell
```bash
$ exit 1
```
* D'afficher le répertoire courant
```bash
$ pwd
```
* D'afficher les variables d'environnement
```bash
$ env
```
* D’exécuter des commandes simple, en "avant plan" et en "arrière plan"
```bash
$ commande
$ commande &
$ commande1 ; commande2 ; commande3 & commande4 ; ...
```
* De rediriger les entrées sorties des commandes
```bash
$ commande > file.output
$ commande 2> file.error
$ commande < file.input
$ commande >> file.appout
$ commande 2>> file.apperr
$ commande >&2
$ commande 2>&1
$ commande1 | commande2 | commande3 | ...
```
* De gérer les variables d’environnement
```bash
$ export VAR="ma variable"
$ echo $VAR
$ unset VAR
...
```
* De gérer les opérateurs !, && et || comme les gère le bash
```bash
$ cmd1 && cmd2
$ cmd1 || cmd2
$ cmd1 && cmd2 || cmd3 && ...
```
* Les combinaisons de toutes ces fonctionnalités élémentaires
```bash
$ echo $VAR | grep -o [0-9] | sed s/^0/1/ >&2 && ls test || cat < file ; ls -l && ...
...
```
