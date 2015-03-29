

# Übersicht #

# Public Funktionen #
## Buffer(char**, char**, unsigned int) ##
Konstruktor, erstlt den Buffer.

Parameter:
  * nputFile: Pfad der Datei aus der gelesen wird.
  * outputFile: Pfad der Ausgabe Datei. **nicht mehr relevant, wird entfernt!**
  * BufferSize: Größe des Imput-Buffers
## virtual ~Buffer() ##
Destruktor
## char getNextChar() ##
Gibt das nächste Zeichen des Buffer's zurück, Dabei wird die BufferPointerPos erhöht.

Ist das Ende einer Datei erreicht wird `\000` zurückgegeben.
## void ungetChar(int) ##
Bewegt den Bufferponiter um den Übergabewert nach links (Bufferponiter-Übergabewert)
Bsp.: Bufferinhalt Hallo (Ponter an Pos 5(o))
Wenn wir nun das 'H' bekommen wollen, muss der der Bufferpointer um 6 nach links bewegt werden, da bei getNextChar der Bufferpointer erst erhöt wird, anschließend das Zeichen ausgegegeben!
=> muss nochmal überdacht werden, vermutlich wird erst das Zeichen ausgegeben, anschließed erhöt

## int getCurrentColumn() ##
## int getCurrentRow() ##
## bool isEOF() ##
## void RegisterMessageHandler(OutputHandlerBase**) ##
## void RegisterErrorHandler(OutputHandlerBase**) ##
## void writeMessage(char**) ##
## void writeMessage(char) ##
## void writeError(char**) ##
## void writeToke(void) ##
## void CloseAll() ##

# Funktionen #

# Known Issues #
  * Buffer.h vereint ein und ausgabe (vll umbenennen in IOBUffer
  * Exceptions funktionieren noch nicht
  * ungetChar
  * Fehlerbehandlung
  * InputBuffer und FileHandlerRead zusammenfassen!