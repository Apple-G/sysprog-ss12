#include "Parser.h"

//#include "../TypeCheck/CodeGeneratorVisitor.h"
//#include "../TypeCheck/TypeCheckVisitor.h"

/*
Parser::Parser(char *inFile, char *scannerLog, OutputBuffer *semanticLog, OutputBuffer *outFile) {
	this->scanner = new Scanner(inFile, scannerLog);
	this->tree = new Tree();

	// Typecheck und Code-Generierung
//ToDo:
//	this->typeChecker = new TypeCheckVisitor(semanticLog);
//	this->codeGenerator = new CodeGeneratorVisitor(outFile);
}
*/
Parser::Parser(void) {
}


Parser::~Parser(void) {
	//delete this->typeChecker;
//	delete this->codeGenerator;
	delete this->tree;
	delete this->scanner;
}


Token* Parser::readNextToken() {
	if (!this->scanner->isEndOfFile()) {
		return this->scanner->getNextToken();
	} else {
		return 0;
	}
}


Tree* Parser::parse() {
	this->tree->setRoot(this->prog());

	//ToDo: TypeCheck
//	if (!this->typeChecker->completedWithoutErrors()) {
//		fprintf(stderr, "Semantic check returned errors, code cannot be generated!\nPlease check 'errorSemantics.log'.\n");
//	}

	return this->tree;
}

NodeProg* Parser::prog() {
	NodeProg* root = new NodeProg();

	// DECLS STATEMENTS
	root->addChild(this->decls());
	root->addChild(this->statements());

	/* --> JETZT TYPPRÜFUNG UND CODEGEN - VERSCHRÄNKUNG */
	//root->accept(this->typeChecker);
	//root->accept(this->codeGenerator);

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
		if (temp->getType() == Token::TokenType::SEMICOLON) {
			// DECLS
			declarations->addChild(this->decls());
		} 
		else {
		//	throw SyntaxErrorException("';' expected", temp->getRow(), temp->getColumn());
			//ToDo:
			printf("';' expected", temp->getRow(), temp->getColumn());
			throw exception();
		}
	}
	return declarations;
}

NodeDecl* Parser::decl() {
	NodeDecl* declaration;
	Token *temp = this->readNextToken();
	
	// Epsilon Fall f�r DECLS
	if (temp == 0) {
		return 0;
	}

	// int ARRAY identifer
	// int
	if (temp->getType() == Token::TokenType::INT) {
		// int Schlüsselwort ist abgebildet durch Knotentyp
		//ARRAY
		declaration = new NodeDecl();
		declaration->addChild(this->array_());

		//identifier
		temp = this->readNextToken();
		if (temp->getType() == Token::TokenType::IDENTIFIER) {
			declaration->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem()));
		}
		else {
			//ToDo: throw SyntaxErrorException("Identifier expected", temp->getRow(), temp->getColumn());
			printf("Identifier expected", temp->getRow(), temp->getColumn());
		}
	}
	else {
		this->scanner->ungetToken();
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
	if (temp->getType() == Token::TokenType::L_SQUAREBRACE) {
		// INTEGER
		temp = this->readNextToken();
		if (temp->getType() == Token::TokenType::INTEGER) {
			integer = new NodeInteger(temp->getNumber(), temp->getRow(), temp->getColumn());

			// ]
			temp = this->readNextToken();
			if (temp->getType() == Token::TokenType::R_SQUAREBRACE) {
				array_ = new NodeArray();
				array_->addChild(integer);

				return array_;
			}
			else {
				delete integer;
				//ToDo: throw SyntaxErrorException("']' expected", temp->getRow(), temp->getColumn());
				printf("']' expected", temp->getRow(), temp->getColumn());
			}
		}
		else {
			//ToDo: throw SyntaxErrorException("Integer expected", temp->getRow(), temp->getColumn());
			printf("Integer expected", temp->getRow(), temp->getColumn());
		}
	}
	// Epsilon
	else {
		this->scanner->ungetToken();
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
	if (temp->getType() == Token::TokenType::SEMICOLON) {
		// STATEMENTS
		statements->addChild(this->statements());
	}
	else {
		//ToDo: throw SyntaxErrorException("';' expected", temp->getRow(), temp->getColumn());
		printf("';' expected", temp->getRow(), temp->getColumn());
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
		case Token::TokenType::IDENTIFIER:
			assign = new NodeStatementAssign();

			//identifier
			identifier = new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem());
			assign->addChild(identifier);

			//INDEX
			assign->addChild(this->index());

			// =
			temp = this->readNextToken();
			if (temp->getType() == Token::TokenType::EQUALS) {
				// EXP
				assign->addChild(this->exp());
			}
			else {
				delete assign;
				//ToDo: throw SyntaxErrorException(" '=' expected", temp->getRow(), temp->getColumn());
				printf(" '=' expected", temp->getRow(), temp->getColumn());
			}

			newNode = assign;
			break;

		// print(EXP)
		case Token::TokenType::PRINT:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TokenType::L_PARENTHESIS) {
				print = new NodeStatementPrint();

				// EXP
				print->addChild(this->exp());
				// )
				temp = this->readNextToken();
				if (temp->getType() != Token::TokenType::R_PARENTHESIS) {
					delete print;
					//ToDo: throw SyntaxErrorException("')' expected", temp->getRow(), temp->getColumn());
					printf("')' expected", temp->getRow(), temp->getColumn());
				}
			}
			else {
				//ToDo: throw SyntaxErrorException("'(' expected", temp->getRow(), temp->getColumn());
				printf("'(' expected", temp->getRow(), temp->getColumn());
			}

			newNode = print;
			break;

		// read(IDENTIFIER INDEX)
		case Token::TokenType::READ:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TokenType::L_PARENTHESIS) {
				read = new NodeStatementRead();

				// IDENTIFIER
				temp = this->readNextToken();
				if (temp->getType() == Token::TokenType::IDENTIFIER) {
					read->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem()));
					// INDEX
					read->addChild(this->index());

					// )
					temp = this->readNextToken();
					if (temp->getType() != Token::TokenType::R_PARENTHESIS) {
						delete read;
						//ToDo: throw SyntaxErrorException("')' expected", temp->getRow(), temp->getColumn());
											printf("')' expected", temp->getRow(), temp->getColumn());
					}
					newNode = read;
				}
				else {
					delete read;
					//ToDo; throw SyntaxErrorException("Identifier expected", temp->getRow(), temp->getColumn());
					printf("Identifier expected", temp->getRow(), temp->getColumn());
				}
			}
			else {
				//ToDo: throw SyntaxErrorException("'(' expected", temp->getRow(), temp->getColumn());
				printf("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// {STATEMENTS}
		case Token::TokenType::L_BRACE:
			block = new NodeStatementBlock();

			// STATEMENTS
			block->addChild(this->statements());
			// }
			temp = this->readNextToken();
			if (temp->getType() != Token::TokenType::R_BRACE) {
				delete block;
				//ToDo: throw SyntaxErrorException("'}' expected", temp->getRow(), temp->getColumn());
				printf("'}' expected", temp->getRow(), temp->getColumn());
			}

			newNode = block;
			break;

		// IF (EXP) STATEMENT else STATEMENT
		case Token::TokenType::IF:
			temp = this->readNextToken();
			// (
			if (temp->getType() == Token::TokenType::L_PARENTHESIS) {
				ifElse = new NodeStatementIfElse();

				// EXP
				ifElse->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::TokenType::R_PARENTHESIS) {
					//STATEMENT
					ifElse->setIfStatement(this->statement());

					//ELSE
					temp = this->readNextToken();
					if (temp->getType() == Token::TokenType::ELSE) {
						//STATEMENT
						ifElse->setElseStatement(this->statement());
					}
					else {
						delete ifElse;
						//ToDo: throw SyntaxErrorException("else expected", temp->getRow(), temp->getColumn());
						printf("else expected", temp->getRow(), temp->getColumn());
					}
					newNode = ifElse;
				}
				else {
					delete ifElse;
					//ToDo: throw SyntaxErrorException("')' expected", temp->getRow(), temp->getColumn());
					printf("')' expected", temp->getRow(), temp->getColumn());
				}
			}
			else {
				//ToDo: throw SyntaxErrorException("'(' expected", temp->getRow(), temp->getColumn());
				printf("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// while(EXP) STATEMENT
		case Token::TokenType::WHILE:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::TokenType::L_PARENTHESIS) {
				whileStatement = new NodeStatementWhile();

				// EXP
				whileStatement->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::TokenType::R_PARENTHESIS) {
					//STATEMENT
					whileStatement->addChild(this->statement());
				}
				else {
					delete whileStatement;
					//ToDo: throw SyntaxErrorException("')' expected", temp->getRow(), temp->getColumn());
					printf("')' expected", temp->getRow(), temp->getColumn());
				}

				newNode = whileStatement;
			}
			else {
				//ToDo: throw SyntaxErrorException("'(' expected", temp->getRow(), temp->getColumn());
				printf("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// Leere Statements sind nicht erlaubt!
		case Token::TokenType::SEMICOLON:
			//ToDo: throw SyntaxErrorException("Empty Statement is not accepted!", temp->getRow(), temp->getColumn());
			printf("Empty Statement is not accepted!", temp->getRow(), temp->getColumn());
			break;

		// Statement in einem Declarations-Block
		case Token::TokenType::INT:
			//ToDo: throw SyntaxErrorException("Statement expected", temp->getRow(), temp->getColumn());
			printf("Statement expected", temp->getRow(), temp->getColumn());
			break;

		// Nichts hat gepasst
		default:
			this->scanner->ungetToken();
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
	NodeExp2Exp* expression;TokenType
	NodeExp2IdentifierIndex* indexNode;TokenType
	NodeExp2Integer* integerNode;
	NodeExp2NegativeExp* negativeExpNode;
	NodeExp2NotExp* notExpNode;

	Token *temp = this->readNextToken();

	switch (temp->getType()) {
		// (EXP)
		case Token::TokenType::L_PARENTHESIS:
			// EXP
			expression = new NodeExp2Exp();
			expression->addChild(this->exp());

			// )
			temp = this->readNextToken();
			if (temp->getType() != Token::TokenType::R_PARENTHESIS) {
				//ToDo: throw SyntaxErrorException("')' expected", temp->getRow(), temp->getColumn());
									printf("')' expected", temp->getRow(), temp->getColumn());
			}
			return expression;

		// IDENTIFIER INDEX
		case Token::TokenType::IDENTIFIER:
			indexNode = new NodeExp2IdentifierIndex();
			indexNode->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem()));

			// INDEX
			indexNode->addChild(this->index());
			return indexNode;

		// INTEGER
		case Token::TokenType::INTEGER:
			integerNode = new NodeExp2Integer();
			integerNode->addChild(new NodeInteger(temp->getNumber(), temp->getRow(), temp->getColumn()));
			return integerNode;

		// - EXP
		case Token::TokenType::MINUS:
			// EXP
			negativeExpNode = new NodeExp2NegativeExp();
			negativeExpNode->addChild(this->exp());
			return negativeExpNode;

		// ! EXP
		case Token::TokenType::EXCLAMATIONMARK:
			// EXP2
			notExpNode = new NodeExp2NotExp();
			notExpNode->addChild(this->exp2());
			return notExpNode;

		default:
			//ToDo: throw SyntaxErrorException("Illegal expression.", temp->getRow(), temp->getColumn());
			printf("Illegal expression.", temp->getRow(), temp->getColumn());
	}

	return 0;
}

NodeIndex* Parser::index() {
	// [EXP]
	// [
	NodeIndex *index;
	Token *temp = this->readNextToken();

	if (temp->getType() == Token::TokenType::L_SQUAREBRACE) {
		// EXP
		index = new NodeIndex();
		index->addChild(this->exp());

		// ]
		temp = this->readNextToken();
		if (temp->getType() == Token::TokenType::R_SQUAREBRACE) {
			return index;
		}
		else {
			delete index;
			//ToDo: throw SyntaxErrorException("']' expected", temp->getRow(), temp->getColumn());
			printf("']' expected", temp->getRow(), temp->getColumn());
		}
	}
	else {
		// Epsilon
		this->scanner->ungetToken();
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
		case Token::PLUS:
			opNodeType = Node::TYPE_OP_PLUS;
		break;

		// -
		case Token::TokenType::MINUS:
			opNodeType = Node::TYPE_OP_MINUS;
		break;

		// *
		case Token::TokenType::ASTERISK:
			opNodeType = Node::TYPE_OP_MULTIPLY;
		break;

		// /
		case Token::TokenType::SLASH:
			opNodeType = Node::TYPE_OP_DIVIDE;
		break;

		// <
		case Token::TokenType::L_BRACKET:
			opNodeType = Node::TYPE_OP_SMALLER;
		break;

		// >
		case Token::TokenType::R_BRACKET:
			opNodeType = Node::TYPE_OP_GREATER;
		break;

		// =
		case Token::TokenType::EQUALS:
			opNodeType = Node::TYPE_OP_EQUAL;
		break;

		// <!>
		case Token::TokenType::UNEQUAL:
			opNodeType = Node::TYPE_OP_UNEQUAL;
		break;

		// &
		case Token::TokenType::AMPERSAND:
			opNodeType = Node::TYPE_OP_AND;
		break;

		default:
			// OP_EXP: Epsilon
			this->scanner->ungetToken();
			return 0;
		break;
	}

	return new NodeOp(opNodeType);
}

Tree* Parser::getTree() {
	return this->tree;
}
