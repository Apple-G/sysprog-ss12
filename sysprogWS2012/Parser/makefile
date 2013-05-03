# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = 	$(OBJDIR)/Parser.o \
	$(OBJDIR)/Parser_Tree.o \
	$(OBJDIR)/TestParser.o \
	$(OBJDIR)/Visitor.o \
	$(OBJDIR)/CodeGeneratorVisitor.o \
	$(OBJDIR)/TypeCheckVisitor.o \
	$(OBJDIR)/Node.o 

## hier alle Object Files eintragen, die in der shared library enthalten sein sollen 
OBJSFORPARSERLIB =  \
	$(LIBDIR)/Parser.o \
	$(LIBDIR)/Parser_Tree.o 
	## Falls lib gebaut wird hier Nodes einfügen
	
	


#
#		Targets zum Bauen des Tests
#

CFLAGS=-I../Symboltable/src -I../Buffer/src -I../Scanner/src -I../Automat/src -I../Nodes
LDFLAGS=-L../sharedlib -lScanner -lAutomat -lBuffer -lSymboltable

makeTestParser: $(OBJS)
	@echo "MakeTestParser init"
	g++ -g $^ $(LDFLAGS) -o $(BINDIR)/ParserTest
	@echo "MakeTestParser finish"
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "  g++ $*.cpp"
	g++ $(CFLAGS) -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanParser:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestParser
	
	
#
# erstellen der shared library
#

ParserLib:$(OBJSFORPARSERLIB)
		g++ -shared $(LDFLAGS) -o $(SHAREDLIB)/libParser.so $^ 

	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ $*.cpp"
	g++ $(CFLAGS) -g  -c -fPIC  -o $@  $<