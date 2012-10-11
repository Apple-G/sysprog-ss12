

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/TestScanner.o

#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORSCANNERLIB =  \
	$(LIBDIR)/Scanner.o
	




makeTestScanner: $(OBJS)
	g++ -g $^ -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
	
	
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanScanner:
	rm -rf $(OBJDIR)/*
	
	
## erstellen der shared library

# erst wichtig fuer den Parser Teil
#
#ScannerLib:$(OBJSFORSCANNERLIB)
#		g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 
#
#	
#$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
##	@mkdir -p `dirname $(OBJDIR)/$*.o`
#	@echo "g++ $*.cpp"
#	g++ -g  -c -fPIC  -o $@  $<

	