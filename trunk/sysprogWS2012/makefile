#
#	baut das komplette Scanner Projekt
#


AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

SHAREDLIB = sharedlib


all:	symboltableLib bufferLib automatLib scanner testBuffer testAutomat testSymboltable
	@echo "target all"

	

clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SHAREDLIB)/*
	rm -rf $(SCANNERDIR)/debug/*
	rm -rf $(BUFFERDIR)/debug/* #TODO: testbuffer löschen
	rm -rf $(AUTOMATDIR)/debug/* #TODO: notwendig?
	rm -rf $(SYMBOLTABLEDIR)/debug/* 
	
	

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib
	
bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib
	
symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib
#Testcase
testBuffer:
	$(MAKE) -C $(BUFFERDIR) makeTestBuffer
	
testAutomat:
	$(MAKE) -C $(AUTOMATDIR) makeTestAutomat
	
testSymboltable:
	$(MAKE) -C $(SYMBOLTABLEDIR) makeTestSymboltable
	


# scannerLib wird erst fuer den Parser Teil benoetigt	
#scannerLib:
#	$(MAKE) -C $(SCANNERDIR) ScannerLib
	
