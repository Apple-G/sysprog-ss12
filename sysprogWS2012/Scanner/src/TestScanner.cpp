#include "Scanner.h"
#include <iostream>

//*******************************************************
// Funktion:  main
// Parameter: int argc, char* argv[
// Return:    int
// Notiz:     initialisiert den Scanner, und startet die Analyse.
//*******************************************************
int main(int argc, char* argv[]) {
	if (argc < 2)
	return EXIT_FAILURE;
	clock_t begin = clock();
	Scanner* s = new Scanner(argv[1],argv[2]);
	if (s->checkFile()) {

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC*1000;
		std::cout<<std::endl;
		std::cout<<"Zeitmessung in Millisekunden: "<<elapsed_secs<<std::endl;
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}

}
