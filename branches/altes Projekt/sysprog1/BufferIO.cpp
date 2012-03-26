#include "BufferIO.h"

//*******************************************************
// Funktion:  BufferIO
// Parameter:char* inFile, char* outFile
// Notiz:     Im Konstruktor werden alle Standarderte gesetzt.
//            Es wird die Ein- und Ausgabedatei übergeben.
//*******************************************************
BufferIO::BufferIO(char* inFile, char* outFile)
{
	this->bufferSize = 65536;
	this->outBufferSize = 65536;

	this->inFile = inFile;
	this->outFile = outFile;

	this->buffer = new char[bufferSize];
	this->documentPosition = 0;
	this->bufferPosition = 0;

	this->columnSize = 100;
	this->column = new int[columnSize];
	this->column[1] = 0;
	this->line = 1;

	this->outBuffer = new char[outBufferSize];
	this->outBuffer[0] = '\0';
	this->outBufferPosition = 0;
	
	this->endOfFile = false;
	this->getNewBuffer();

	std::cout<<"processing ..."<<std::endl;
}
//========================================================================

//*******************************************************
// Funktion:  ~BufferIO
// Parameter: void
// Notiz:     Destruktor
//*******************************************************
BufferIO::~BufferIO(void)
{
	delete[] buffer;
	delete[] outBuffer;
}
//========================================================================

//*******************************************************
// Funktion:  isLetter
// Parameter: -
// Return:    void
// Notiz:     Füllt die Puffer mit neuen Daten.
//*******************************************************
void BufferIO::getNewBuffer(){
	document.open (inFile);
	//lände der Dokumetns festlegen
	document.seekg (0, std::ios::end);
	documentLength = document.tellg();
	document.seekg (documentPosition);

	//Buffer einlesen
	document.read (buffer, bufferSize);
	documentPosition = document.tellg();
	document.close();		
}
//========================================================================

//*******************************************************
// Funktion:  getNextChar
// Parameter: -
// Return:    char
// Notiz:     Gibt das nächste Zeichen des Puffers zurück und füllt den Buffer mit neuen Zeichen.
//*******************************************************
char BufferIO::getNextChar(){
	char tempChar;
	// überprüft ob das Ende des Dokuments erreicht ist
	if (bufferPosition  + line-1 < documentLength){
		tempChar = buffer[bufferPosition%bufferSize];
		bufferPosition++;
		if (tempChar == '\n') {
			line++;
			if (line > columnSize){
				extendColumnArray();
			}
			column[line] = 0;
		}
		else{
			column[line]++;
		}
	}
	else{
		tempChar = EOF;
		endOfFile = true;
	}

	// ist das ende des Buffers erreicht wird er neu mit Daten gefüllt
	if (bufferPosition%bufferSize < (bufferPosition-1)%bufferSize){
		getNewBuffer();
	}
	return tempChar;
}
//========================================================================

//*******************************************************
// Funktion:  ungetChar
// Parameter: int number
// Return:    void
// Notiz:     Setzt die aktuelle Pufferposition um den Uebergabeparameter zurueck 
//*******************************************************
void BufferIO::ungetChar(int number){
	if (number < bufferSize){
		for (int i=0; i<number; i++){
			ungetCharOnce();
		}
	}
	else{
		std::cout<<"Error 'ungetChar("<<number<<")' nicht möglich."<<std::endl;
	}
}
//========================================================================

//*******************************************************
// Funktion:  ungetCharOnce
// Parameter: -
// Return:    void
// Notiz:     Hilfsfunktion von ungetChar. Verkleinert die Pufferposition um Eins.
//*******************************************************
void BufferIO::ungetCharOnce(){
	if ((bufferPosition-1)%bufferSize > bufferPosition%bufferSize){
		documentPosition = documentPosition-(2*bufferSize);
		if (documentPosition < 0){
			std::cout<<"Error: BufferIO::ungetCharOnce => documentPosition < 0"<<std::endl;
		}
		else{
			getNewBuffer();
		}
	}
	bufferPosition--;
	if (buffer[bufferPosition%bufferSize] == '\n'){
		line--;
	}
	else{
		column[line]--;
	}


}
//========================================================================

//*******************************************************
// Funktion:  out
// Parameter: char* word
// Return:    void
// Notiz:     Gibt den Übergabeparameter auf der Konsole aus.
//*******************************************************

void BufferIO::out(char* word){
	std::cout<<word<<std::endl;
}
//========================================================================

//*******************************************************
// Funktion:  errorOut
// Parameter: Token token
// Return:    void
// Notiz:     Gibt eine Fehlermeldung bei einem falschen Zeichen auf der Konsole aus.
//*******************************************************

void BufferIO::errorOut(Token token){
	// Error unknown Token
	std::cout<<"unknown Token Line: "<<token.getLine()<<" Column: "<<token.getColumn()<<"\t Symbol: "<<token.getValue()<<std::endl;
}
//========================================================================

//*******************************************************
// Funktion:  fileOut
// Parameter:char* out, unsigned int length
// Return:    void
// Notiz:     Speichert das übergebene CharArray im Puffer.
//*******************************************************

void BufferIO::fileOut(char* out, unsigned int length){

	while (length > (outBufferSize - outBufferPosition+1)){
		extendOutBuffer();	
	}

	for (int i=0; i<length; i++){
		outBuffer[outBufferPosition] = out[i];
		outBufferPosition++;
	}
	outBuffer[outBufferPosition]='\0';

}
//========================================================================

//*******************************************************
// Funktion:  writeToFile
// Parameter: -
// Return:    void
// Notiz:     Schreibt den Ausgabepuffer in die Ausgabedatei.
//*******************************************************
void BufferIO::writeToFile(){
	write.open(outFile);
	write<<outBuffer;
	write.close();
}
//========================================================================

//*******************************************************
// Funktion:  getLine
// Parameter: -
// Return:    int
// Notiz:     Gibt die Zeile des aktuellen Zeichens zurück.
//*******************************************************
int BufferIO::getLine(){
	return line;
}
//========================================================================

//*******************************************************
// Funktion:  getColumn
// Parameter: -
// Return:    int
// Notiz:     Gibt die Spalte des aktuellen Zeichens zurück.
//*******************************************************
int BufferIO::getColumn(){
	return column[line];
}
//========================================================================

//*******************************************************
// Funktion:  getEOF
// Parameter: -
// Return:    bool
// Notiz:     Gibt True zurück, wenn das Ende der Datei im Puffer erreicht ist.
//*******************************************************
bool BufferIO::getEOF(){
	return endOfFile;
}
//========================================================================

//*******************************************************
// Funktion:  extendColumnArray
// Parameter: 
// Return:    void
// Notiz:     verdoppelt die Größe des ColumnArray's.
//*******************************************************
void BufferIO::extendColumnArray(){

	int* temp = new int[columnSize*2];
	for (int i=1; i<columnSize; i++){
		temp[i] = column[i];
	}
	delete[] column;
	columnSize = columnSize*2;
	column = temp;
}
//========================================================================

//*******************************************************
// Funktion:  extendOutBuffer
// Parameter: -
// Return:    void
// Notiz:     Verdoppelt die Größe des Ausgabepuffers.
//*******************************************************
void BufferIO::extendOutBuffer(){


	char* temp = new char[outBufferSize*2];
	for (int i=0; i<outBufferSize; i++){
		temp[i] = outBuffer[i];
	}
	delete[] outBuffer; 
	outBufferSize = outBufferSize*2;
	outBuffer = temp;
}
