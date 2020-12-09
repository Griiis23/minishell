prog: parser.o builtin.o cmdline.o utils.o processus.o
	gcc parser.o builtin.o utils.o processus.o cmdline.o
builtin.o:builtin.c
	gcc builtin.c -c 
cmdline.o:cmdline.c
	gcc cmdline.c -c 
utils.o:utils.c
	gcc utils.c -c 
processus.o:processus.c
	gcc processus.c -c 
parser.o:parser.c
	gcc parser.c -c 
