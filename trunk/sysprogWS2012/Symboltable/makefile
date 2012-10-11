# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Symboltable.o \
	$(OBJDIR)/TestSymboltable.o
	#$(OBJDIR)/xx1.o \
	#$(OBJDIR)/xxn.o

OBJSFORSYMBOLTABLELIB =  \
	$(LIBDIR)/Symboltable.o #\


#
#		Targets zum Bauen des Tests
#

makeTestSymboltable: SymboltableTest


SymboltableTest: $(OBJS)
	g++ -g $^ -o $(BINDIR)/SymboltableTest
	
	# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanSymboltable:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) SymboltableTest
	
#	
# erstellen der shared library
#

SymboltableLib:$(OBJSFORSYMBOLTABLELIB)
		g++ -shared  -o $(SHAREDLIB)/libSymboltable.so $^ 

	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ $*.cpp"
	g++ -g  -c -fPIC  -o $@  $<

	