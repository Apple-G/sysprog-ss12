/* retrun
 * Automat.cpp
 *
 */
#include "Automat.h"

//using namespace std;
//========================================================================

//*******************************************************
// Funktion:  Automat Konstruktor
// Parameter: Buffer *myBuffer
//*******************************************************
Automat::Automat(Buffer *myBuffer) {
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
bool Automat::isLetter(char currentChar) {
	return ((currentChar >= 'a' && currentChar <= 'z')
			|| (currentChar >= 'A' && currentChar <= 'Z'));

}
//========================================================================

//*******************************************************
// Funktion:  isNumber
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um einen Zahl handelt.
//*******************************************************
bool Automat::isNumber(char currentChar) {
	return (currentChar >= '0' && currentChar <= '9');
}
//========================================================================

//*******************************************************
// Funktion:  isSign
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um ein einzelnes, erlaubtes Zeichen handelt.
//*******************************************************
bool Automat::isSign(char currentChar) {
	return (currentChar == '+' || currentChar == '-' || currentChar == '('
			|| currentChar == '&' || currentChar == ';'
			|| currentChar == '{' || currentChar == '}' || currentChar == '['
			|| currentChar == ']' || currentChar == '=' || currentChar == ')');
}

//*******************************************************
// Funktion:  analyseSign
// Parameter: char currentChar
// Return:    Token::TokenType
// Notiz:     Gibt den TokenTyp eines einzelnen Signs zurück.
//*******************************************************
Token::TokenType Automat::analyseSign(char currentChar) {
	if (currentChar == '+') {
		return Token::PLUS;
	} else if (currentChar == '-') {
		return Token::MINUS;
	} else if (currentChar == '/') {
		return Token::SLASH;
	} else if (currentChar == '!') {
		return Token::EXCLAMATIONMARK;
	} else if (currentChar == '&') {
		return Token::AMPERSAND;
	} else if (currentChar == ';') {
		return Token::SEMICOLON;
	} else if (currentChar == '{') {
		return Token::L_BRACE;
	} else if (currentChar == '}') {
		return Token::R_BRACE;
	} else if (currentChar == '[') {
		return Token::L_SQUAREBRACE;
	} else if (currentChar == ']') {
		return Token::R_SQUAREBRACE;
	} else if (currentChar == '(') {
		return Token::L_PARENTHESIS;
	} else if (currentChar == '*') {
		return Token::ASTERISK;
	} else if (currentChar == ')') {
		return Token::R_PARENTHESIS;
	} else if (currentChar == '<') {
		return Token::L_BRACKET;
	} else if (currentChar == '=') {
		return Token::EQUALS;
	} else if (currentChar == '>') {
		return Token::R_BRACKET;
	} else
		return Token::UNKNOWN;
}
//========================================================================

//*******************************************************
// Funktion:  isDeliminter
// Parameter: char currentChar
// Return:    bool
// Notiz:     Prueft ob es sich um ein Trennzeichen handelt.
//*******************************************************
bool Automat::isDelimiter(char currentChar) {
	return (currentChar == '\t' || currentChar == '\n' || currentChar == ' ');
}
//========================================================================

//*******************************************************
// Funktion:  analyseChar
// Parameter: char currentChar
// Return:    int returnValue
// Notiz:     Symbolanalyse, die den Typ des Symbols zurueckgibt.
//*******************************************************
int Automat::analyseChar(char currentChar) {
	int returnValue;

	if (isLetter(currentChar)) {
		returnValue = INPUT_LETTER;
	} else if (isNumber(currentChar)) {
		returnValue = INPUT_NUMBER;
	} else if (currentChar == '/') {
		returnValue = INPUT_SLASH;
	} else if (currentChar == '*') {
		returnValue = INPUT_ASTERISK;
	} else if (currentChar == '<') {
		returnValue = INPUT_LESSTHAN;
	} else if (currentChar == '!') {
		returnValue = INPUT_EXCLAMATIONMARK;
	} else if (currentChar == '>') {
		returnValue = INPUT_GREATERTHAN;
	} else if (isSign(currentChar)) {
		returnValue = INPUT_SIGN;
	} else if (isDelimiter(currentChar)) {
		returnValue = INPUT_DELIMITER;
	} else {
		returnValue = INPUT_ERROR;
	} // error case

	return returnValue;
}
//========================================================================

//*******************************************************
// Funktion:  addCharToTempToken
// Parameter: char currentChar
// Return:    void
// Notiz:     Vergroessert den temporaeren Token und fuegt ihm das uebergebene Zeichen hinzu.
//*******************************************************
void Automat::addCharToTempToken(char currentChar) {
	tempTokenLength++;
	//if (tempTokenLength > 1) {
	extendTempToken();
	//}
	tempToken[tempTokenLength-1] = currentChar;
	tempToken[tempTokenLength] = '\0';

}
//========================================================================

//*******************************************************
// Funktion:  stepBack
// Parameter: unsigned int count
// Return:    void
// Notiz:     Verkleinert den temporaeren Token mit Hilfe von shrinkTempToken und sprint im Buffer einen Schritt zurueck.
//*******************************************************
void Automat::stepBack(unsigned int count) {
	if (count > 0) {
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
void Automat::extendTempToken() {

	char* biggerToken = (char*) malloc((tempTokenLength+1) * sizeof(char));

	int count = 0;
	while (*tempToken != '\0')
	{
		biggerToken[count] = *tempToken;
		tempToken++;
		count++;
	}

	tempToken = biggerToken;
}
//========================================================================

//*******************************************************
// Funktion:  shrinkTempToken
// Parameter: unsigned int count
// Return:    void
// Notiz:     Verkleinert den temporaeren Token um den Uebergabeparameter.
//*******************************************************
void Automat::shrinkTempToken(unsigned int count) {
	if (count > 0) {
		char* temp;
		temp = new char[tempTokenLength - count];
		for (unsigned int i = 0; i < tempTokenLength - count; i++) {
			temp[i] = tempToken[i];
		}
		temp[tempTokenLength - count] = '\0';

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
	int currentRow = 0;
	int currentColumn = 0;

	this->tempToken = new char[1];

	tempTokenLength = 0;
	currentState = STATE_START;
	Token returnToken;

	// holt naechstes Zeichen vom Puffer
	currentChar = myBuffer->getNextChar();
	currentRow = myBuffer->getCurrentRow();
	currentColumn = myBuffer->getCurrentColumn();

	// Hauptschleife
	while (!returnCondition) {

		// Aeusseres Switch besteht aus sieben Faellen (Zustaenden), jeder Fall beinhaltet ein weiteres Switch
		// mit zehn inneren Faellen, welche zeichenabhaengig bearbeitet werden
		switch (currentState) {

		// TODO: Überlegung, wie wir die zeile und reihe des tokens speichern!
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
			case INPUT_SLASH: {
				currentState = STATE_SLASH;
				addCharToTempToken(currentChar);
				returnToken.setType(analyseSign(currentChar));
				break;
			}
			case INPUT_ASTERISK: // *
			case INPUT_UNUSED: { // )
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(analyseSign(currentChar));
				break;
			}
			case INPUT_LESSTHAN: { // change of state <
				currentState = STATE_UNEQUAL;
				addCharToTempToken(currentChar);
				returnToken.setType(analyseSign(currentChar));
				break;
			}
			case INPUT_EXCLAMATIONMARK: // =
			case INPUT_GREATERTHAN: // >
			case INPUT_SIGN: { // sign
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(analyseSign(currentChar));
				break;
			}
			case INPUT_DELIMITER: { // delimiter
				// rekursiver aufruf leerzeichen enter etc werden also ignoriert.
				// wenn das erste zeichen ein delimiter ist(ist im state start), wird nexttoken resettet(neu aufgerufen)
				//TODO: raus???
				return nextToken();
				//break;
			}
			case INPUT_ERROR: {
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::UNKNOWN);
				break;
			}
			}
			break;
		}

		case STATE_IDENTIFIER: { // Zustand: Identifier
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER: { // identifier
				currentState = STATE_IDENTIFIER;
				addCharToTempToken(currentChar);
				break;
			}
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: {
				returnCondition = true;
				stepBack(1);
				returnToken.setType(Token::IDENTIFIER);
				break;
			}
			}
			break;
		}

		case STATE_INTEGER: { // Zustand: Integer
			switch (analyseChar(currentChar)) {
			case INPUT_NUMBER: {
				currentState = STATE_INTEGER;
				addCharToTempToken(currentChar);
				break;
			}
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR:
			case INPUT_LETTER: { // return integer and step back
				returnCondition = true;
				stepBack(1);
				returnToken.setNumber(strtol(tempToken, NULL, 10));
				returnToken.setType(Token::INTEGER);
				break;
			}
			}
			break;
		}

		case STATE_SLASH: { // Zustand: / slash
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: { // resturn sign with a step back
				returnCondition = true;
				stepBack(1);
				break;
			}
			case INPUT_ASTERISK: {
				currentState = STATE_COMMENTARY;
				break;
			}
			}
			break;
		}

		case STATE_COMMENTARY: { // Zustand: inside commentary
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: {
				break;
			}
			case INPUT_ASTERISK: {
				currentState = STATE_ASTERISK;
				break;
			}
			}
			break;
		}

		case STATE_ASTERISK: { // Zustand: * asterisk im Kommentar
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: {
				currentState = STATE_COMMENTARY;
				break;
			}
			case INPUT_ASTERISK:
				break;
			case INPUT_SLASH: { //End of Commentary
				currentState = STATE_START;
				tempTokenLength = 0;
				returnToken.setType(Token::UNKNOWN);
				break;
			}
			}
			break;
		}

		case STATE_UNEQUAL: { // Zustand: < smaller then
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_GREATERTHAN:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: { // return sign with a step back
				returnCondition = true;
				stepBack(1);
				break;
			case INPUT_EXCLAMATIONMARK: { // change of state <!
				currentState = STATE_UNEQUAL_CHECK;
				addCharToTempToken(currentChar);
				break;
			}
			}
			}
			break;
		}

		case STATE_UNEQUAL_CHECK: { // Zustand: <! smaller than
			switch (analyseChar(currentChar)) {
			case INPUT_LETTER:
			case INPUT_NUMBER:
			case INPUT_SLASH:
			case INPUT_ASTERISK:
			case INPUT_UNUSED:
			case INPUT_LESSTHAN:
			case INPUT_EXCLAMATIONMARK:
			case INPUT_SIGN:
			case INPUT_DELIMITER:
			case INPUT_ERROR: {
				//return sign (<) and step back (2)
				returnCondition = true;
				stepBack(2);
				break;
			}
			case INPUT_GREATERTHAN: { // return <!> OHNE schritt zurueck
				returnCondition = true;
				addCharToTempToken(currentChar);
				returnToken.setType(Token::UNEQUAL);
				break;
			}
			}
			break;
		}

		}
		if (!returnCondition)
		{
			currentChar = myBuffer->getNextChar();
		}
	} //end While

	//Wenn Dateiende ereicht soll leeres Token zurückgegeben werden.
	//Annahme das jede Datei mit '\n' und anschließend '\000' endet
	/*if (myBuffer->isEOF())
	{
		returnToken.setType(Token::UNKNOWN);
		return returnToken;
	}
*/
	// Setzt den Wert des Rueckgabetokens
	returnToken.setLexem(tempToken);

	// Setzt Spalte des Rueckgabetokens
	 returnToken.setColumn(currentColumn);

	 // Setzt Zeile des Rueckgabetokens
	 returnToken.setRow(currentRow);

	return returnToken;
}
