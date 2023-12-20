
#this is a simple makefile that I have made with help of the provided makefile by Barbara Johnson and
# henry walker, and also from help and explanations prof. Johnson gave me

CC = clang

CFLAGS = -ansi -g -Wall -std=gnu99

#----------------------------------------

main:  main.o homework2.o
	clang -o main main.o homework2.o

main.o:  main.c homework2.c homework2.h
	clang -c main.c

homework2.o:  homework2.c homework2.h
	clang -c homework2.c

#----------------------------------------------------------------------------
# cleanup rules: To invoke this command, type "make clean".
# Use this target to clean up your directory, deleting (without warning) 
#   the built program, object files, old emacs source versions, and core dumps.

clean:
	rm -f list *.o *~ core*