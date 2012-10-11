# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Buffer.o \
	$(OBJDIR)/TestBuffer.o
	#$(OBJDIR)/xx1.o \
	#$(OBJDIR)/xxn.o

## hier alle Object Files eintragen, die in der shared library enthalten sein sollen 
OBJSFORBUFFERLIB = $(LIBDIR)/Buffer.o #\


#
#		Targets zum Bauen des Tests
#

makeTestBuffer: BufferTest


BufferTest: $(OBJS)
	g++ -g $^ -o $(BINDIR)/BufferTest
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanBuffer:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) BufferTest
	

#	
# erstellen der shared library
#

BufferLib:$(OBJSFORBUFFERLIB)
		g++ -shared  -o $(SHAREDLIB)/libBuffer.so $^ 

	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ $*.cpp"
	g++ -g  -c -fPIC  -o $@  $<

	