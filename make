#wordSearch.make
# working make file for use of the class Account
# files: source files:
#        header files:
# executable file: wordSearch.out
#

# first define target file : account 
#              dependencies are the object files that build the program

wordPuzzle.out:  main.o wordPuzzle.o trieTree.o
	g++ -o wordSearch.out main.o wordPuzzle.o trieTree.o

# define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

#main.o: main.cpp trieTree.h wordPuzzle.h avlTree.h
#	g++ -c main.cpp

#trieTree.o:trieTree.cpp trieTree.h
#	g++ -c trieTree.cpp

#wordPuzzle.o: wordPuzzle.h wordPuzzle.cpp avlTree.h
#clean:
#	rm *.cpp~ *.h~ *.o *.out

#wordSearch.out: main.cpp wordPuzzle.cpp trieTree.cpp avlTree.h
g++ -g -Wall -ansi main.cpp wordPuzzle.cpp trieTree.cpp avlTree.h -o wordSearch.out
