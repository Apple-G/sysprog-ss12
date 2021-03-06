#ifndef BUFFER_H_
#define BUFFER_H_
#include "OutBuffer_OutputBuffer.h"
#include "OutBuffer_OutputHandlerBase.h"
#include "OutBuffer_OutputFileHandler.h"
#include "InBuffer_InputBuffer.h"
/*
 * Buffer.h
 * Buffer ist für die Ein und Ausgabe zuständig.
 *
 */

class Buffer {
private:
	/*
	 * Ausgabe Buffer
	 */
	OutputBuffer *output_;

	/*
	 * Eingabe Buffer
	 */
	InputBuffer *input_;

public:
	/*
	 * Initialisiert eine neuen Buffer.
	 */
	Buffer();

	/*
	 * Initialisiert eine neuen Buffer.
	 * @param fileInPath Pfad der einzulesenden Datei
	 */
	Buffer(char*);
	/*
	 * Initialisiert eine neuen Buffer.
	 * @param fileInPath Pfad der einzulesenden Datei
	 * @param bufferSize Größe des Ein- und Ausgabe Buffers
	 */
	Buffer(char*, unsigned int);

	/*
	 * Initialisiert eine neuen Buffer.
	 * @param fileInPath Pfad der einzulesenden Datei
	 * @param fileOutPath Pfad der ausgabe Datei
	 * @param bufferSize Größe des Ein- und Ausgabe Buffers
	 */
	Buffer(char*, char*, unsigned int);

	/*
	 * Löscht den Buffer
	 */
	virtual ~Buffer();

	/*
	 * gibt das nächste Zeichen im Buffer zurück, Position wird zuvor verändert.
	 *
	 * @return Nächstes Zeichen oder \000 => beim Fehler
	 */
	char getNextChar();

	/*
	 * bewgt den Pointer des Buffers um die angegebene Anzahl zurück und gibt das Zeichen an dieser Position zurück
	 * @param number Anzahl der Pointerbewgungen
	 */
	char ungetChar(unsigned int);

	/*
	 * gibt die aktuelle Position des aktuellen Zeichens zurück
	 * @return
	 */
	long getCurrentColumn();

	/*
	 * gibt die aktuelle Zeile des aktuellen Zeichens zurück
	 * @return
	 */
	long getCurrentRow();

	/*
	 * Ist True beim erreichen des Datei Endes
	 * @return End of File
	 */
	bool isEOF();

	/*
	 * Zum Registrieren eines Ausgabe Messages Handler
	 * @param handler
	 */
	void RegisterMessageHandler(OutputHandlerBase*);

	/*
	 * Zum Registrieren eines Error Messages Handler
	 * @param handler
	 */
	void RegisterErrorHandler(OutputHandlerBase*);

	/*
	 * schreibt eine Zeichenkette in die registrierten OutputHandler
	 */
	void writeMessage(char*);

	/*
	 * schreibt ein Zeichen in die registrierten OutputHandler
	 */
	void writeMessage(char);

	/*
	 * schreibt eine Errormeldung in die registrierten OutputHandler
	 */
	void writeError(char*);

	/*
	 * schreibt den Inhalt des Buffers und schließt alle offenen Dateien
	 */
	void CloseAll();
};

#endif /* BUFFER_H_ */
