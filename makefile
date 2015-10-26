project:mlibrary.o
	cc mlibrary.c -o project
main.o:mlibrary.c
	cc -c mlibrary.c
