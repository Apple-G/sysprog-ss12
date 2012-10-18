/**
 * Festlegung der verschiedenen Token Typen
 */

#ifndef TOKENTYPE_H_
#define TOKENTYPE_H_

namespace TokenTypes {
	enum TokenType
	{
		UNKNOWN,			// ErrorType	0
		INTEGER,			// Integer		1
		IDENTIFIER,			// Bezeichner	2
		PLUS,				// +			3
		MINUS,				// -			4
		SLASH,				// /			5
		ASTERISK,			// *			6
		L_BRACKET,			// <			7
		R_BRACKET,			// >			8
		EQUALS,				// =			9
		EXCLAMATIONMARK,	// !			10
		AMPERSAND,			// &			11
		SEMICOLON,			// ;			12
		L_PARENTHESIS,		// (			13
		R_PARENTHESIS,		// )			14
		L_BRACE,			// {			15
		R_BRACE,			// }			16
		L_SQUAREBRACE,		// [			17
		R_SQUAREBRACE,		// ]			18
		UNEQUAL,			// <=>			19
		PRINT,				// PRINT		20
		READ,				// READ			21
	};
}
#endif /* TOKENTYPE_H_ */
