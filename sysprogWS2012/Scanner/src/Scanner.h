/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "Automat.h"
#include "Buffer.h"
#include "Symboltable.h"

/**
 * Dient als Schnittstelle zwischen Buffer, Automat und der Symboltabelle.
 * Sie vereint diese und besitzt die Logik des Scanners. Er erstellt die Token mit Hilfe
 * der Eingabedatei und fügt sie in die Symboltabelle ein bzw. gibt eine Textdatei aus.
 */

class Scanner {
private:
	Symboltable* table;
	Buffer* buffer;
	Automat* automat;

public:
	Scanner(char*, char*);
	virtual ~Scanner(void);
	bool checkFile();
};

#endif /* SCANNER_H_ */
