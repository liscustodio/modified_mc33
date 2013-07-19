SOURCE=MarchingCubes.cpp MarchingCubes.h ply.c ply.h fparser.cpp fparser.h LookUpTable.h main.cpp defs.h
MYPROGRAM=ModifiedMC33

MYINCLUDES=/Users/liscustodio/Documents/workspace/modified_mc33/src/include 
#MYLIBRARIES=fltk

CC=g++

#------------------------------------------------------------------------------

all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)
	$(CC) -I$(MYINCLUDES) $(SOURCE) -o $(MYPROGRAM)
#$(CC) -I$(MYINCLUDES) $(SOURCE) -o $(MYPROGRAM) -l$(MYLIBRARIES)

clean:
	rm -f $(MYPROGRAM)
