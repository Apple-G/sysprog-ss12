#
#	baut das komplette Scanner Projekt
#


AUTOMATDIR = Automat

BUFFERDIR = Buffer

PARSERDIR = Parser

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

SHAREDLIB = sharedlib


all:	symboltableLib bufferLib automatLib scannerLib testScanner testParser testBuffer testAutomat testSymboltable
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
	
	

#libs

parserLib:
	$(MAKE) -C $(PARSERDIR) ParserLib

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib
	
bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

scannerLib: 
	$(MAKE) -C $(SCANNERDIR) ScannerLib

	
symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib
#Testcase

testScanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

testParser:
	$(MAKE) -C $(PARSERDIR) makeTestParser


testBuffer:
	$(MAKE) -C $(BUFFERDIR) makeTestBuffer
	
testAutomat:
	$(MAKE) -C $(AUTOMATDIR) makeTestAutomat
	
testSymboltable:
	$(MAKE) -C $(SYMBOLTABLEDIR) makeTestSymboltable
	
