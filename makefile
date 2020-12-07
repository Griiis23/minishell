prog: cmdline.o utils.o processus.o
	gcc cmdline.o utils.o processus.o
cmdline.o:cmdline.c
	gcc cmdline.c -c 
utils.o:utils.c
	gcc utils.c -c 
processus.o:processus.c
	gcc processus.c -c 
