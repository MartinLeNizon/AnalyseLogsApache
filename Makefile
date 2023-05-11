# /*************************************************************************
#                           		 Makefile
#                              -------------------
#     début                : 20 janvier 2023
#     copyright            : (C) 2023 par Aziza Ballahbib & Martin Nizon-Deladoeuille
#     e-mails              : aziza.bellahbib@insa-lyon.fr ; martin.nizon-deladoeuille@insa-lyon.fr
# *************************************************************************/

# Pour modifier les répertoires, il faut penser à rajouter / à la fin
# Si pas de répertoire précisé dans le variable -> Utilisation racine du projet

# option debug : yes/no
# permet utilisation gdb et affichage méthodes appelées
DEBUG = no

CXX = g++
ifeq ($(DEBUG),yes)
	CXXFLAGS = -ansi -pedantic -Wall -std=c++11 -g -DMAP
	LDFLAGS = -DMAP
else
	CXXFLAGS = -ansi -pedantic -Wall -std=c++11
	LDFLAGS =
endif

EXECDIR = bin/
EXEC = $(EXECDIR)analog
INCLUDEDIR = include/
SRCDIR = src/
SRC = $(wildcard $(SRCDIR)*.cpp)
OBJDIR = obj/
OBJ = $(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Mode debug"
else
	@echo "Mode release"
endif

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/FluxLog.o: $(INCLUDEDIR)LigneLog.h

$(OBJDIR)/main.o: $(INCLUDEDIR)FluxLog.h $(INCLUDEDIR)LigneLog.h $(INCLUDEDIR)Statistiques.h

$(OBJDIR)%.o: $(SRCDIR)%.cpp Makefile
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY:clean mrproper

clean:
	@rm -rf $(OBJ)

mrproper: clean
	@rm -rf $(EXEC)
