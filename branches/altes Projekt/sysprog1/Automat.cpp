
#include "Automat.h"

using namespace std;
//========================================================================

//*******************************************************
// Funktion:  Automat Konstruktor
// Parameter: BufferIO *myBuffer
//*******************************************************
Automat::Automat(BufferIO *myBuffer) {
	this->myBuffer = myBuffer;
	this->tempToken = new char[1];
}
//========================================================================

//*******************************************************
// Funktion:  isLetter
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um einen Buchstaben a-z bzw. A-Z handelt.
//*******************************************************
bool Automat::isLetter (char currentChar) {
	return ((currentChar >= 'a' && currentChar<='z') || (currentChar >= 'A' && currentChar <= 'Z' ));

}
//========================================================================

//*******************************************************
// Funktion:  isNumber
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um einen Zahl handelt.
//*******************************************************
bool Automat::isNumber (char currentChar) {
	return (currentChar >= '0' && currentChar <= '9');
}
//========================================================================

//*******************************************************
// Funktion:  isSign
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um ein erlaubtes Zeichen handelt.
//*******************************************************
bool Automat::isSign (char currentChar) {
	return (
		currentChar == '+' ||
		currentChar == '-' ||
		currentChar == '/' ||
		currentChar == '!' ||
		currentChar == '&' ||
		currentChar == ';' ||
		currentChar == '{' ||
		currentChar == '}' ||
		currentChar == '[' ||
		currentChar == ']'
		);
}
//========================================================================

//*******************************************************
// Funktion:  isDeliminter
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um ein Trennzeichen handelt.
//*******************************************************
bool Automat::isDelimiter(char currentChar) {
	return (
		currentChar == '\t' ||
		currentChar == '\n' ||
		currentChar == ' '
		);
}
//========================================================================

//*******************************************************
// Funktion:  analyseChar
// Parameter: char currentChar
// Return:    int returnValue
// Notiz:     Symbolanalyse, die den Typ des Symbols zurueckgibt.
//*******************************************************
int Automat::analyseChar (char currentChar) {
	int returnValue;

	if (isLetter(currentChar))			{ returnValue = 0; }
	else if (isNumber(currentChar))		{ returnValue = 1; }
	else if (currentChar == '(')		{ returnValue = 2; }
	else if (currentChar == '*')		{ returnValue = 3; }
	else if (currentChar == ')')		{ returnValue = 4; }
	else if (currentChar == '<')		{ returnValue = 5; }
	else if (currentChar == '=')		{ returnValue = 6; }
	else if (currentChar == '>')		{ returnValue = 7; }
	else if (isSign(currentChar))		{ returnValue = 8; }
	else if (isDelimiter(currentChar))	{ returnValue = 9; }
	else								{ returnValue = 10; } // error case

	return returnValue;
}
//========================================================================

//*******************************************************
// Funktion:  addCharToTempToken
// Parameter: char currentChar
// Return:    void
// Notiz:     Vergroessert den temporaeren Token und fuegt ihm das uebergebene Zeichen hinzu.
//*******************************************************
void Automat::addCharToTempToken (char currentChar) {
	//if (tempTokenLength > 1) {
	extendTempToken();
	//}
	tempToken[tempTokenLength] = currentChar;
	tempToken[tempTokenLength+1] = '\0';
	tempTokenLength++;
}
//========================================================================

//*******************************************************
// Funktion:  stepBack
// Parameter: unsigned int count
// Return:    void
// Notiz:     Verkleinert den temporaeren Token mit Hilfe von shrinkTempToken und sprint im Buffer einen Schritt zurueck.
//*******************************************************
void Automat::stepBack(unsigned int count){
	if (count>0){
		shrinkTempToken(count - 1);
		tempTokenLength = tempTokenLength - (count - 1);
		myBuffer->ungetChar(count);
	}
}
//========================================================================

//*******************************************************
// Funktion:  extendTempToken
// Parameter: 
// Return:    void
// Notiz:     Vergroessert den temporaeren Token um Eins.
//*******************************************************
void Automat::extendTempToken(){

	char* temp;

	temp = new char[tempTokenLength];
	for (int i = 0; i < tempTokenLength; i++){
		temp[i] = tempToken[i];
	}
	tempToken = temp;
}
//========================================================================

//*******************************************************
// Funktion:  shrinkTempToken
// Parameter: unsigned int count
// Return:    void
// Notiz:     Verkleinert den temporaeren Token um den Uebergabeparameter.
//*******************************************************
void Automat::shrinkTempToken(unsigned int count){
	if (count > 0){
		char* temp;
		temp = new char[tempTokenLength - count];
		for (int i = 0; i < tempTokenLength - count; i++){
			temp[i] = tempToken[i];
		}
		temp[tempTokenLength-count]='\0';

		tempToken = temp;
	}
}

//========================================================================

//*******************************************************
// Funktion:  nextToken
// Parameter: -
// Return:    Token
// Notiz:     Liest den naechsten Token vom Puffer ein, analysiert dessen Typ und gibt ein Tokenobjekt zurueck.
//*******************************************************
Token Automat::nextToken() {
	char currentChar;
	bool returnCondition = false;
	tempTokenLength = 0;
	currentState = 0;
	Token returnToken;


	// Hauptschleife
	while (!returnCondition && !myBuffer->getEOF()) {

		// holt naechstes Zeichen vom Puffer
		currentChar = myBuffer->getNextChar();

		// Aeusseres Switch besteht aus sieben Faellen (Zustaenden), jeder Fall beinhaltet ein weiteres Switch 
		// mit zehn inneren Faellen, welche zeichenabhaengig bearbeitet werden
		switch (currentState) {

		case 0: { // Zustand: Start
			switch (analyseChar(currentChar)) {
			case 0: { // identifier
				currentState = 1;
				addCharToTempToken(currentChar);
				break;
					}
			case 1: { // integer
				currentState = 2;
				addCharToTempToken(currentChar);
				break;
					}
			case 2 : { // change of state parenthesis (
				currentState = 3;
				addCharToTempToken(currentChar);
				break;
					 }
			case 3 : { // *
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case 4 : { // )
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case 5 : { // change of state <
				currentState = 6;
				addCharToTempToken(currentChar);
				break;
					 }
			case 6 : { // =
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case 7 : { // >
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case 8 : { // sign
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case 9 : { // delimiter
				break;
					 }
			case 10: {
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::TType::error);
				break;
					 } 
			}
			break;
				}


		case 1: { // Zustand: Identifier
			switch (analyseChar(currentChar)) {
			case 0: { // identifier
				currentState = 1;
				addCharToTempToken(currentChar);
				break;
					}
			case 1: { // identifier
				currentState = 1;
				addCharToTempToken(currentChar);
				break;
					}
			case 2 :
			case 3 :
			case 4 :
			case 5 :
			case 6 :
			case 7 :
			case 8 : { // return identifier (going a step back)
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			case 9 : { // return identifier (without going a step back)
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			case 10: {
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			}
			break;
				}

		case 2: { // Zustand: Integer
			switch (analyseChar(currentChar)) {
			case 0: { // return integer and step back
				returnCondition = true;
				stepBack(1);

				returnToken.setValue(atol(tempToken));
				returnToken.setType(Token::integer);
				break;
					}
			case 1: {
				currentState = 2;
				addCharToTempToken(currentChar);
				break;
					}
			case 2 :
			case 3 :
			case 4 :
			case 5 :
			case 6 :
			case 7 :
			case 8 : { // return integer and step back
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;
					 }
			case 9 : { // return integer without a step back
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;
					 }
			case 10: {
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;

					 } 
			}
			break;
				}

		case 3: { // Zustand: ( open parenthesis
			switch (analyseChar(currentChar)) {
			case 0:
			case 1:
			case 2 : { // resturn sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			case 3 : {
				currentState = 4;
				break;
					 }
			case 4 :
			case 5 :
			case 6 :
			case 7 :
			case 8 : { // resturn sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			case 9 : { // return sign without a step back
				returnCondition = true;

				returnToken.setType(Token::sign);
				break;
					 }
			case 10: {
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			}
			break;
				}

		case 4: { // Zustand: inside commentary
			switch (analyseChar(currentChar)) {
			case 0:
			case 1:
			case 2 : {
				break;
					 }
			case 3 : {
				currentState = 5;
				break;
					 }
			case 4 :
			case 5 :
			case 6 :
			case 7 :
			case 8 :
			case 9 : {
				break;
					 }
			case 10: {
				break;
					 }
			}
			break;
				}

		case 5: { // Zustand: * asterisk
			switch (analyseChar(currentChar)) {
			case 0:
			case 1:
			case 2 : {
				currentState = 4;
				break;
					 }
			case 3 : {
				break;
					 }
			case 4 : { //End of Commentary
				currentState = 0;
				tempTokenLength = 0;
				break;
					 }
			case 5 :
			case 6 :
			case 7 :
			case 8 :
			case 9 :
			case 10 : {
				currentState = 4;
				break;
					  }
			}
			break;
				}

		case 6: { // Zustand: < smaller then
			switch (analyseChar(currentChar)) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: { // return sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					}
			case 6: { // change of state <=
				currentState = 7;
				addCharToTempToken(currentChar);
				break;
					}
			case 7:
			case 8:
			case 9:
			case 10: { // return sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			}
			break;
				}

		case 7: { // Zustand: <= smaller then
			switch (analyseChar(currentChar)) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6: { // return sign (<) and step back (2)
				returnCondition = true;
				stepBack(2);

				returnToken.setType(Token::sign);
				break;
					}
			case 7: { // return <=> OHNE schritt zurueck
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					}
			case 8:
			case 9: { // return sign (<) and step back (2)
				returnCondition = true;
				stepBack(2);

				returnToken.setType(Token::sign);
				break;
					}
			case 10: {
				returnCondition = true;
				stepBack(2);

				returnToken.setType(Token::sign);
				break;
					 }
			}
			break;
				}

		}
	}

	// Setzt den Wert des Rueckgabetokens
	returnToken.setValue(tempToken);

	// Bestimmt Anfansspalte des Rueckgabetokens
	if (currentChar==EOF) {
		returnToken.setColumn(myBuffer->getColumn()-(tempTokenLength-2));;
	}
	else {
		returnToken.setColumn(myBuffer->getColumn()-(tempTokenLength-1));
	}

	// Setzt laenge des Rueckgabetokens
	returnToken.setLength(tempTokenLength);

	// Setzt Zeile des Rueckgabetokens
	returnToken.setLine(myBuffer->getLine());

	return returnToken;
}