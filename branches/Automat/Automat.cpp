
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
		currentChar == '(' ||
		currentChar == '=' ||
		currentChar == '&' ||
		currentChar == ';' ||
		currentChar == '{' ||
		currentChar == '}' ||
		currentChar == '[' ||
		currentChar == ']'
		); // TODO: noch ) hinzufügen
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

	if (isLetter(currentChar))			{ returnValue = INPUT_LETTER; }
	else if (isNumber(currentChar))		{ returnValue = INPUT_NUMBER; }
	else if (currentChar == '/')		{ returnValue = INPUT_SLASH; }
	else if (currentChar == '*')		{ returnValue = INPUT_ASTERISK; }
	else if (currentChar == ')')		{ returnValue = INPUT_UNUSED; } // TODO: noch rauswerfen
	else if (currentChar == '<')		{ returnValue = INPUT_LESSTHAN; }
	else if (currentChar == '!')		{ returnValue = INPUT_EXCLAMATIONMARK; }
	else if (currentChar == '>')		{ returnValue = INPUT_GREATERTHAN; }
	else if (isSign(currentChar))		{ returnValue = INPUT_SIGN; }
	else if (isDelimiter(currentChar))	{ returnValue = INPUT_DELIMITER; }
	else								{ returnValue = INPUT_ERROR; } // error case

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
	currentState = STATE_START;
	Token returnToken;


	// Hauptschleife
	while (!returnCondition && !myBuffer->getEOF()) {

		// holt naechstes Zeichen vom Puffer
		currentChar = myBuffer->getNextChar();

		// Aeusseres Switch besteht aus sieben Faellen (Zustaenden), jeder Fall beinhaltet ein weiteres Switch 
		// mit zehn inneren Faellen, welche zeichenabhaengig bearbeitet werden
		switch (currentState) {

		case STATE_START: { // Zustand: Start
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER: { // identifier
				currentState = STATE_IDENTIFIER;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_NUMBER: { // integer
				currentState = STATE_INTEGER;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_SLASH : { // change of state parenthesis (
				currentState = STATE_SLASH;
				addCharToTempToken(currentChar);
				break;
					 }
			case INPUT_ASTERISK : { // *
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_UNUSED : { // )
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_LESSTHAN : { // change of state <
				currentState = STATE_UNEQUAL;
				addCharToTempToken(currentChar);
				break;
					 }
			case INPUT_EXCLAMATIONMARK : { // !
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_GREATERTHAN : { // >
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_SIGN : { // sign
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_DELIMITER : { // delimiter
				break;
					 }
			case INPUT_ERROR: {
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::TType::error);
				break;
					 } 
			}
			break;
				}


		case STATE_IDENTIFIER: { // Zustand: Identifier
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER: { // identifier
				currentState = STATE_IDENTIFIER;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_NUMBER: { // identifier
				currentState = STATE_IDENTIFIER;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_SLASH :
			case INPUT_ASTERISK :
			case INPUT_UNUSED :
			case INPUT_LESSTHAN :
			case INPUT_EXCLAMATIONMARK :
			case INPUT_GREATERTHAN :
			case INPUT_SIGN : { // return identifier (going a step back)
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			case INPUT_DELIMITER : { // return identifier (without going a step back)
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			case INPUT_ERROR: {
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::identifier);
				break;
					 }
			}
			break;
				}

		case STATE_INTEGER: { // Zustand: Integer
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER: { // return integer and step back
				returnCondition = true;
				stepBack(1);

				returnToken.setValue(atol(tempToken));
				returnToken.setType(Token::integer);
				break;
					}
			case INPUT_NUMBER: {
				currentState = STATE_INTEGER;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_SLASH :
			case INPUT_ASTERISK :
			case INPUT_UNUSED :
			case INPUT_LESSTHAN :
			case INPUT_EXCLAMATIONMARK :
			case INPUT_GREATERTHAN :
			case INPUT_SIGN : { // return integer and step back
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;
					 }
			case INPUT_DELIMITER : { // return integer without a step back
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;
					 }
			case INPUT_ERROR: {
				returnCondition = true;
				stepBack(1);
				returnToken.setValue(atol(tempToken));

				returnToken.setType(Token::integer);
				break;

					 } 
			}
			break;
				}

		case STATE_SLASH: { // Zustand: / slash
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH : { // resturn sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_ASTERISK : {
				currentState = STATE_COMMENTARY;
				break;
					 }
			case INPUT_UNUSED :
			case INPUT_LESSTHAN :
			case INPUT_EXCLAMATIONMARK :
			case INPUT_GREATERTHAN :
			case INPUT_SIGN : { // resturn sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_DELIMITER : { // return sign without a step back
				returnCondition = true;

				returnToken.setType(Token::sign);
				break;
					 }
			case INPUT_ERROR: {
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			}
			break;
				}

		case STATE_COMMENTARY: { // Zustand: inside commentary
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH : {
				break;
					 }
			case INPUT_ASTERISK : {
				currentState = STATE_ASTERISK;
				break;
					 }
			case INPUT_UNUSED :
			case INPUT_LESSTHAN :
			case INPUT_EXCLAMATIONMARK :
			case INPUT_GREATERTHAN :
			case INPUT_SIGN :
			case INPUT_DELIMITER : {
				break;
					 }
			case INPUT_ERROR: {
				break;
					 }
			}
			break;
				}

		case STATE_ASTERISK: { // Zustand: * asterisk
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH : {
				currentState = STATE_COMMENTARY;
				break;
					 }
			case INPUT_ASTERISK : {
				break;
					 }
			case INPUT_UNUSED : { //End of Commentary
				currentState = STATE_START;
				tempTokenLength = 0;
				break;
					 }
			case INPUT_LESSTHAN :
			case INPUT_EXCLAMATIONMARK :
			case INPUT_GREATERTHAN :
			case INPUT_SIGN :
			case INPUT_DELIMITER :
			case INPUT_ERROR : {
				currentState = STATE_COMMENTARY;
				break;
					  }
			}
			break;
				}

		case STATE_UNEQUAL: { // Zustand: < unequal
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN: { // return sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					}
			case INPUT_EXCLAMATIONMARK: { // change of state <!
				currentState = STATE_UNEQUAL_CHECK;
				addCharToTempToken(currentChar);
				break;
					}
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: { // return sign with a step back
				returnCondition = true;
				stepBack(1);

				returnToken.setType(Token::sign);
				break;
					 }
			}
			break;
				}

		case STATE_UNEQUAL_CHECK: { // Zustand: <! unequal
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK: { // return sign (<) and step back (2)
				returnCondition = true;
				stepBack(2);

				returnToken.setType(Token::sign);
				break;
					}
			case INPUT_GREATERTHAN: { // return <=> OHNE schritt zurueck
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::sign);
				break;
					}
			case INPUT_SIGN:
			case INPUT_DELIMITER: { // return sign (<) and step back (2)
				returnCondition = true;
				stepBack(2);

				returnToken.setType(Token::sign);
				break;
					}
			case INPUT_ERROR: {
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
