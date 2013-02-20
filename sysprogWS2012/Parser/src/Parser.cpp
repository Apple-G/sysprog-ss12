#include "Parser.h"
#include "../TypeCheck/CodeGeneratorVisitor.h"
#include "../TypeCheck/TypeCheckVisitor.h"


Parser::Parser(char *inFile, char *scannerLog, OutputBuffer *semanticLog, OutputBuffer *outFile) {
	this->scanner = new Scanner(inFile, scannerLog);
	this->tree = new Tree();

	// Typecheck und Code-Generierung
	this->typeChecker = new TypeCheckVisitor(semanticLog);
	this->codeGenerator = new CodeGeneratorVisitor(outFile);
}

Parser::Parser(void) {
}


Parser::~Parser(void) {
	delete this->typeChecker;
	delete this->codeGenerator;
	delete this->tree;
	delete this->scanner;
}


Token* Parser::readNextToken() {
	try {
		if (!this->scanner->isEndOfFile()) {
			return this->scanner->getNextToken();
		}
		else {
			return 0;
		}
	}
	catch (EndOfFileException &e) {
		return 0;
	};
}

Tree* Parser::parse() {
	this->tree->setRoot(this->prog());

	if (!this->typeChecker->completedWithoutErrors()) {
		fprintf(stderr, "Semantic check returned errors, code cannot be generated!\nPlease check 'errorSemantics.log'.\n");
	}

	return this->tree;
}

NodeProg* Parser::prog() {
	NodeProg* root = new NodeProg();

	// DECLS STATEMENTS
	root->addChild(this->decls());
	root->addChild(this->statements());

	/* --> JETZT TYPPRÜFUNG UND CODEGEN - VERSCHRÄNKUNG */
	root->accept(this->typeChecker);
	root->accept(this->codeGenerator);

	return root;
}

NodeDecls* Parser::decls() {
	NodeDecls* declarations;

	// DECL; DECLS
	// DECL
	NodeDecl* declaration = this->decl();

	// Epsilon
	if (declaration == 0) {
		return 0;
	}
	else {
		declarations = new NodeDecls();
		declarations->addChild(declaration);

		/* --> JETZT TYPPRÜFUNG UND CODEGEN - VERSCHRÄNKUNG */
		declaration->accept(this->typeChecker);
		declaration->accept(this->codeGenerator);

		// ;
		Token *temp = this->readNextToken();
		if (temp->getType() == Token::TYPE_SEMICOLON) {
			// DECLS
			declarations->addChild(this->decls());
		} 
		else {
			throw SyntaxErrorException("';' expected", temp->getLine(), temp->getColumn());
		}
	}
	return declarations;
}

NodeDecl* Parser::decl() {
	NodeDecl* declaration;
	Token *temp = this->readNextToken();
	
	// Epsilon Fall für DECLS
	if (temp == 0) {
		return 0;
	}

	// int ARRAY identifer
	// int
	if (temp->getType() == Token::TYPE_INT) {
		// int Schlüsselwort ist abgebildet durch Knotentyp
		//ARRAY
		declaration = new NodeDecl();
		declaration->addChild(this->array_());

		//identifier
		temp = this->readNextToken();
		if (temp->getType() == Token::TYPE_IDENTIFIER) {
			declaration->addChild(new NodeIdentifier(temp->getInformation(), temp->getLine(), temp->getColumn(), this->scanner->getSymbolTable()));
		}
		else {
			throw SyntaxErrorException("Identifier expected", temp->getLine(), temp->getColumn());
		}
	}
	else {
		this->scanner->undo();
		return 0;
	}

	return declaration;
}


NodeArray* Parser::array_() {
	// [integer] | Epsilon
	NodeArray *array_;
	NodeInteger *integer;

	Token *temp = this->readNextToken();
	// [
	if (temp->getType() == Token::TYPE_SQUARE_BRACKET_OPEN) {
		// INTEGER
		temp = this->readNextToken();
		if (temp->getType() == Token::TYPE_INTEGER) {
			integer = new NodeInteger(temp->getInformation(), temp->getLine(), temp->getColumn());

			// ]
			temp = this->readNextToken();
			if (temp->getType() == Token::TYPE_SQUARE_BRACKET_CLOSE) {
				array_ = new NodeArray();
				array_->addChild(integer);

				return array_;
			}
			else {
				delete integer;
				throw SyntaxErrorException("']' expected", temp->getLine(), temp->getColumn());
			}
		}
		else {
			throw SyntaxErrorException("Integer expected", temp->getLine(), temp->getColumn());
		}
	}
	// Epsilon
	else {
		this->scanner->undo();
		return 0;
	}
}

NodeStatements* Parser::statements() {
	// STATEMENT; STATEMENTS | EPSILON

	// STATEMENT
	NodeStatement *statement = this->statement();

	// Epsilon
	if (statement == 0) {
		delete statement;
		return 0; // => Programmende!
	}

	NodeStatements* statements = new NodeStatements();
	statements->addChild(statement);

	/* --> JETZT TYPPRÜFUNG UND CODEGEN - VERSCHRÄNKUNG */
	// Nimmt man hier statements, werden viele NOPs erzeugt
	statement->accept(this->typeChecker);
	statement->accept(this->codeGenerator);

	// ;
	Token *temp = this->readNextToken();
	if (temp->getType() == Token::TYPE_SEMICOLON) {
		// STATEMENTS
		statements->addChild(this->statements());
	}
	else {
		throw SyntaxErrorException("';' expected", temp->getLine(), temp->getColumn());
	}

	return statements;
}

NodeStatement* Parser::statement() {
	NodeStatement *newNode; // used for return

	// Moegliche Auspraegungen des Statements
	NodeStatementAssign* assign;
	NodeStatementPrint* print;
	NodeStatementRead* read;
	NodeStatementBlock* block;
	NodeStatementIfElse* ifElse;
	NodeStatementWhile* whileStatement;

	NodeIdentifier *identifier;

	Token *temp = this->readNextToken();

	// Statements: Epsilon
	if (temp == 0) {
		return 0;
	}

	switch (temp->getType()) {
		// identifier INDEX = EXP
		case Token::TYPE_IDENTIFIER:
			assign = new NodeStatementAssign();

			//identifier
			identifier = new NodeIdentifier(temp->getInformation(), temp->getLine(), temp->getColumn(), this->scanner->getSymbolTable());
			assign->addChild(identifier);

			//INDEX
			assign->addChild(this->index());

			// =
			temp = this->readNextToken();
			if (temp->getType() == Token::TYPE_ASSIGN) {
				// EXP
				assign->addChild(this->exp());
			}
			else {
				delete assign;
				throw SyntaxErrorException(" '=' expected", temp->getLine(), temp->getColumn());
			}

			newNode = assign;
			break;

		// print(EXP)
		case Token::TYPE_PRINT:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TYPE_PARENTHESIS_OPEN) {
				print = new NodeStatementPrint();

				// EXP
				print->addChild(this->exp());
				// )
				temp = this->readNextToken();
				if (temp->getType() != Token::TYPE_PARENTHESIS_CLOSE) {
					delete print;
					throw SyntaxErrorException("')' expected", temp->getLine(), temp->getColumn());
				}
			}
			else {
				throw SyntaxErrorException("'(' expected", temp->getLine(), temp->getColumn());
			}

			newNode = print;
			break;

		// read(IDENTIFIER INDEX)
		case Token::TYPE_READ:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TYPE_PARENTHESIS_OPEN) {
				read = new NodeStatementRead();

				// IDENTIFIER
				temp = this->readNextToken();
				if (temp->getType() == Token::TYPE_IDENTIFIER) {
					read->addChild(new NodeIdentifier(temp->getInformation(), temp->getLine(), temp->getColumn(), this->scanner->getSymbolTable()));
					// INDEX
					read->addChild(this->index());

					// )
					temp = this->readNextToken();
					if (temp->getType() != Token::TYPE_PARENTHESIS_CLOSE) {
						delete read;
						throw SyntaxErrorException("')' expected", temp->getLine(), temp->getColumn());
					}
					newNode = read;
				}
				else {
					delete read;
					throw SyntaxErrorException("Identifier expected", temp->getLine(), temp->getColumn());
				}
			}
			else {
				throw SyntaxErrorException("'(' expected", temp->getLine(), temp->getColumn());
			}
			break;

		// {STATEMENTS}
		case Token::TYPE_CURLY_BRACKET_OPEN:
			block = new NodeStatementBlock();

			// STATEMENTS
			block->addChild(this->statements());
			// }
			temp = this->readNextToken();
			if (temp->getType() != Token::TYPE_CURLY_BRACKET_CLOSE) {
				delete block;
				throw SyntaxErrorException("'}' expected", temp->getLine(), temp->getColumn());
			}

			newNode = block;
			break;

		// IF (EXP) STATEMENT else STATEMENT
		case Token::TYPE_IF:
			temp = this->readNextToken();
			// (
			if (temp->getType() == Token::TYPE_PARENTHESIS_OPEN) {
				ifElse = new NodeStatementIfElse();

				// EXP
				ifElse->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::TYPE_PARENTHESIS_CLOSE) {
					//STATEMENT
					/* HIER KANN SPEICHERSCHROTT DURCH EXCEPTION ERZEUGT EINGEHANGEN WERDEN (z.B. fehlendes try/catch) */
					ifElse->setIfStatement(this->statement());

					//ELSE
					temp = this->readNextToken();
					if (temp->getType() == Token::TYPE_ELSE) {
						//STATEMENT
						ifElse->setElseStatement(this->statement());
					}
					else {
						delete ifElse;
						throw SyntaxErrorException("else expected", temp->getLine(), temp->getColumn());
					}
					newNode = ifElse;
				}
				else {
					delete ifElse;
					throw SyntaxErrorException("')' expected", temp->getLine(), temp->getColumn());
				}
			}
			else {
				throw SyntaxErrorException("'(' expected", temp->getLine(), temp->getColumn());
			}
			break;

		// while(EXP) STATEMENT
		case Token::TYPE_WHILE:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TYPE_PARENTHESIS_OPEN) {
				whileStatement = new NodeStatementWhile();

				// EXP
				whileStatement->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::TYPE_PARENTHESIS_CLOSE) {
					//STATEMENT
					whileStatement->addChild(this->statement());
				}
				else {
					delete whileStatement;
					throw SyntaxErrorException("')' expected", temp->getLine(), temp->getColumn());
				}

				newNode = whileStatement;
			}
			else {
				throw SyntaxErrorException("'(' expected", temp->getLine(), temp->getColumn());
			}
			break;

		// Leere Statements sind nicht erlaubt!
		case Token::TYPE_SEMICOLON:
			throw SyntaxErrorException("Empty Statement is not accepted!", temp->getLine(), temp->getColumn());

		// Statement in einem Declarations-Block
		case Token::TYPE_INT:
			throw SyntaxErrorException("Statement expected", temp->getLine(), temp->getColumn());
			break;

		// Nichts hat gepasst
		default:
			this->scanner->undo();
			return 0;
	} // end switch

	return newNode;
}

NodeExp* Parser::exp() {
	NodeExp* expression = new NodeExp();
	// EXP2 OP_EXP

	// EXP2
	expression->addChild(this->exp2());
	// OP_EXP
	expression->addChild(this->op_exp());

	return expression;
}

NodeExp2* Parser::exp2() {
	NodeExp2Exp* expression;
	NodeExp2IdentifierIndex* indexNode;
	NodeExp2Integer* integerNode;
	NodeExp2NegativeExp* negativeExpNode;
	NodeExp2NotExp* notExpNode;

	Token *temp = this->readNextToken();

	switch (temp->getType()) {
		// (EXP)
		case Token::TYPE_PARENTHESIS_OPEN:
			// EXP
			expression = new NodeExp2Exp();
			expression->addChild(this->exp());

			// )
			temp = this->readNextToken();
			if (temp->getType() != Token::TYPE_PARENTHESIS_CLOSE) {
				throw SyntaxErrorException("')' expected", temp->getLine(), temp->getColumn());
			}
			return expression;

		// IDENTIFIER INDEX
		case Token::TYPE_IDENTIFIER:
			indexNode = new NodeExp2IdentifierIndex();
			indexNode->addChild(new NodeIdentifier(temp->getInformation(), temp->getLine(), temp->getColumn(), this->scanner->getSymbolTable()));

			// INDEX
			indexNode->addChild(this->index());
			return indexNode;

		// INTEGER
		case Token::TYPE_INTEGER:
			integerNode = new NodeExp2Integer();
			integerNode->addChild(new NodeInteger(temp->getInformation(), temp->getLine(), temp->getColumn()));
			return integerNode;

		// - EXP
		case Token::TYPE_MINUS:
			// EXP
			negativeExpNode = new NodeExp2NegativeExp();
			negativeExpNode->addChild(this->exp());
			return negativeExpNode;

		// ! EXP
		case Token::TYPE_EXCLAMATION:
			// EXP2
			notExpNode = new NodeExp2NotExp();
			notExpNode->addChild(this->exp2());
			return notExpNode;

		default:
			throw SyntaxErrorException("Illegal expression.", temp->getLine(), temp->getColumn()); ;
	}

	return 0;
}

NodeIndex* Parser::index() {
	// [EXP]
	// [
	NodeIndex *index;
	Token *temp = this->readNextToken();

	if (temp->getType() == Token::TYPE_SQUARE_BRACKET_OPEN) {
		// EXP
		index = new NodeIndex();
		index->addChild(this->exp());

		// ]
		temp = this->readNextToken();
		if (temp->getType() == Token::TYPE_SQUARE_BRACKET_CLOSE) {
			return index;
		}
		else {
			delete index;
			throw SyntaxErrorException("']' expected", temp->getLine(), temp->getColumn());
		}
	}
	else {
		// Epsilon
		this->scanner->undo();
		return 0;
	}

}

NodeOpExp* Parser::op_exp() {
	// OP EXP
	NodeOpExp* node;
	NodeOp* opNode = this->op();

	if (opNode == 0) {
		return 0;
	}

	node = new NodeOpExp();

	// OP
	node->addChild(opNode);
	// EXP
	node->addChild(this->exp());

	return node;
}

NodeOp* Parser::op() {
	Token *temp = this->readNextToken();
	Node::TYPES opNodeType = Node::TYPE_NONE;

	switch (temp->getType()) {

		// +
		case Token::TYPE_PLUS:
			opNodeType = Node::TYPE_OP_PLUS;
		break;

		// -
		case Token::TYPE_MINUS:
			opNodeType = Node::TYPE_OP_MINUS;
		break;

		// *
		case Token::TYPE_MULTIPLY:
			opNodeType = Node::TYPE_OP_MULTIPLY;
		break;

		// /
		case Token::TYPE_DIVIDE:
			opNodeType = Node::TYPE_OP_DIVIDE;
		break;

		// <
		case Token::TYPE_SMALLER:
			opNodeType = Node::TYPE_OP_SMALLER;
		break;

		// >
		case Token::TYPE_GREATER:
			opNodeType = Node::TYPE_OP_GREATER;
		break;

		// =
		case Token::TYPE_ASSIGN:
			opNodeType = Node::TYPE_OP_EQUAL;
		break;

		// <=>
		case Token::TYPE_EQUIVALENCE:
			opNodeType = Node::TYPE_OP_UNEQUAL;
		break;

		// &
		case Token::TYPE_AMPERSAND:
			opNodeType = Node::TYPE_OP_AND;
		break;

		default:
			// OP_EXP: Epsilon
			this->scanner->undo();
			return 0;
		break;
	}

	return new NodeOp(opNodeType);
}

Tree* Parser::getTree() {
	return this->tree;
}