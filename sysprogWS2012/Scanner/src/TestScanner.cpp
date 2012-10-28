#include "Scanner.h"
//#include "Buffer.h"

//*******************************************************
// Funktion:  main
// Parameter: int argc, char* argv[
// Return:    int
// Notiz:     initialisiert den Scanner, und startet die Analyse.
//*******************************************************
int main(int argc, char* argv[]) {
	if (argc < 1)
	return EXIT_FAILURE;
	Scanner* s = new Scanner("test.txt",
			"out.txt");
	if (s->checkFile()) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}

}
