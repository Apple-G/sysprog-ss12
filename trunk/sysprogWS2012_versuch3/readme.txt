Das Projekt wurde in 4 Teilprojekte aufgeteilt:

	- Automat
	- Buffer
	- Symboltabelle
	
	- Scanner

Jedes Teilprojekt hat die Verzeichnisstruktur:
	- debug		enthaelt Objektfiles zum Testen
	- lib		enthaelt Objektfiles zum Erstellen der shared library des Teilprojekts
	- src		enthaelt den Source-Code

	jedes Teilprojekt enthaelt ein eigenes Makefile und eine eigene Main-Klasse, um die Funktionalitaet zu testen.
	


Das Makefile im obersten Verzeichnis loescht alle shared libraries und erstellt alle neu.



Aufbau des Makefiles
	Definition der Variablen
	
	Targets zum Bauen des Tests
	
	Targets zum Erstellen der shared library


Aufbau der Targets

# 	 target: dependencies
# 	 [tab] system_command


# Compilation commands:
#    classA.o: classA.cpp
#    [tab] g++ -c classA.cpp -o classA.o
    
#    classB.o: classB.cpp
#    [tab] g++ -c classB.cpp -o classB.o


# Link command:
#    my_program: classA.o classB.o
#    [tab] c++ classA.o classB.o -o my_program

# options:
#		-c			Kompilieren ohne zu linken. 
#		-g 			debugging infos erzeugen
#		-o file     object-file file erzeugen 
