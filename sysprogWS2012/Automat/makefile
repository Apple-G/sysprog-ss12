# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Automat.o \
	$(OBJDIR)/TestAutomat.o

## hier alle Object Files eintragen, die in der shared library enthalten sein sollen 
OBJSFORAUTOMATLIB =  \
	$(LIBDIR)/Automat.o #\


#
#		Targets zum Bauen des Tests
#

CFLAGS=-I../Symboltable/src -I../Buffer/src 
LDFLAGS=-L../sharedlib -lBuffer -lSymboltable

makeTestAutomat: $(OBJS)
	@echo "MakeTestAutomat init"
	g++ -g $^ $(LDFLAGS) -o $(BINDIR)/AutomatTest
	@echo "MakeTestAutomat finish"
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	@echo "komisches start"
	g++ $(CFLAGS) -g  -c -Wall  -o $@  $<
	@echo "komisches finish"
# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanAutomat:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestAutomat
	
	
#
# erstellen der shared library
#

AutomatLib:$(OBJSFORAUTOMATLIB)
		g++ -shared $(LDFLAGS) -o $(SHAREDLIB)/libAutomat.so $^ 

	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ $*.cpp"
	g++ $(CFLAGS) -g  -c -fPIC  -o $@  $<