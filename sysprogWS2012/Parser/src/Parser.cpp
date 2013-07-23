#include "Parser.h"
#include "CharHelper.h"
#include "CodeGeneratorVisitor.h"
#include "TypeCheckVisitor.h"


Parser::Parser(Scanner* scanner, Buffer* buffer) {
	this->scanner = scanner;
	this->tree = new Tree();
	this->writer = buffer;

	this->typeChecker = new TypeCheckVisitor(buffer);
	this->codeGenerator = new CodeGeneratorVisitor(buffer);
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

void Parser::errorOutput(char* message, int row, int column) {
	this->writer->writeError(message);
	this->writer->writeError(" (Row ");
	this->writer->writeError(CharHelper::convertInt(row));
	this->writer->writeError(", Column: ");
	this->writer->writeError(CharHelper::convertInt(column));
	this->writer->writeError(")\n");
}

Tree* Parser::parse() {

	//this->scanner->checkFile();
	this->tree->setRoot(this->prog());

	if (!this->typeChecker->completedWithoutErrors()) {
		fprintf(stderr, "Semantic check returned errors.\n");
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
		Token *tempToken = this->readNextToken();
		if (tempToken->getType() == Token::SEMICOLON) {
			// DECLS
			declarations->addChild(this->decls());
		} 
		else {
			errorOutput("';' expected",tempToken->getRow(),tempToken->getColumn());
			throw 1;
		}
	}
	return declarations;
}

NodeDecl* Parser::decl() {
	NodeDecl* declaration;
	Token *temp = this->readNextToken();
	
	// Epsilon Fall fuer DECLS
	if (temp == 0) {
		return 0;
	}

	// int ARRAY identifer
	// int
	if (temp->getType() == Token::INT) {
		// int Schlüsselwort ist abgebildet durch Knotentyp
		//ARRAY
		declaration = new NodeDecl();
		declaration->addChild(this->array_());

		//identifier
		temp = this->readNextToken();
		if (temp->getType() == Token::IDENTIFIER) {
			declaration->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem(), temp->getSymboltableEntry()));
		}
		else {
			errorOutput("Identifier expected", temp->getRow(), temp->getColumn());
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
	if (temp->getType() == Token::L_SQUAREBRACE) {
		// INTEGER
		temp = this->readNextToken();
		if (temp->getType() == Token::INTEGER) {
			integer = new NodeInteger(temp->getNumber(), temp->getRow(), temp->getColumn());

			// ]
			temp = this->readNextToken();
			if (temp->getType() == Token::R_SQUAREBRACE) {
				array_ = new NodeArray();
				array_->addChild(integer);

				return array_;
			}
			else {
				delete integer;
				errorOutput("']' expected", temp->getRow(), temp->getColumn());
				return 0;
			}
		}
		else {
			errorOutput("Integer expected", temp->getRow(), temp->getColumn());
			return 0;
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
	if (temp->getType() == Token::SEMICOLON) {
		// STATEMENTS
		statements->addChild(this->statements());
	}
	else {
		errorOutput("';' expected", temp->getRow(), temp->getColumn());
		//return 0;
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
		case Token::IDENTIFIER:
			assign = new NodeStatementAssign();

			//identifier
			identifier = new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem(), temp->getSymboltableEntry());
			assign->addChild(identifier);

			//INDEX
			assign->addChild(this->index());

			// =
			temp = this->readNextToken();
			if (temp->getType() == Token::EQUALS) {
				// EXP
				assign->addChild(this->exp());
			}
			else {
				delete assign;
				errorOutput(" '=' expected", temp->getRow(), temp->getColumn());
				//return 0;
			}

			newNode = assign;
			break;

		// print(EXP)
		case Token::PRINT:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::L_PARENTHESIS) {
				print = new NodeStatementPrint();

				// EXP
				print->addChild(this->exp());
				// )
				temp = this->readNextToken();
				if (temp->getType() != Token::R_PARENTHESIS) {
					delete print;
					errorOutput("')' expected", temp->getRow(), temp->getColumn());
					return 0;
				}
			}
			else {
				errorOutput("'(' expected", temp->getRow(), temp->getColumn());
				//return 0;
			}

			newNode = print;
			break;

		// read(IDENTIFIER INDEX)
		case Token::READ:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::L_PARENTHESIS) {
				read = new NodeStatementRead();

				// IDENTIFIER
				temp = this->readNextToken();
				if (temp->getType() == Token::IDENTIFIER) {
					read->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem(), temp->getSymboltableEntry()));
					// INDEX
					read->addChild(this->index());

					// )
					temp = this->readNextToken();
					if (temp->getType() != Token::R_PARENTHESIS) {
						delete read;
						errorOutput("')' expected", temp->getRow(), temp->getColumn());
					}
					newNode = read;
				}
				else {
					delete read;
					errorOutput("Identifier expected", temp->getRow(), temp->getColumn());
				}
			}
			else {
				errorOutput("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// {STATEMENTS}
		case Token::L_BRACE:
			block = new NodeStatementBlock();

			// STATEMENTS
			block->addChild(this->statements());
			// }
			temp = this->readNextToken();
			if (temp->getType() != Token::R_BRACE) {
				delete block;
				errorOutput("'}' expected", temp->getRow(), temp->getColumn());
			}

			newNode = block;
			break;

		// IF (EXP) STATEMENT else STATEMENT
		case Token::IF:
			temp = this->readNextToken();
			// (
			if (temp->getType() == Token::L_PARENTHESIS) {
				ifElse = new NodeStatementIfElse();

				// EXP
				ifElse->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::R_PARENTHESIS) {
					//STATEMENT
					ifElse->setIfStatement(this->statement());

					//ELSE
					temp = this->readNextToken();
					if (temp->getType() == Token::ELSE) {
						//STATEMENT
						ifElse->setElseStatement(this->statement());
					}
					else {
						delete ifElse;
						errorOutput("else expected", temp->getRow(), temp->getColumn());
					}
					newNode = ifElse;
				}
				else {
					delete ifElse;
					errorOutput("')' expected", temp->getRow(), temp->getColumn());
				}
			}
			else {
				errorOutput("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// while(EXP) STATEMENT
		case Token::WHILE:
			// (
			temp = this->readNextToken();
			if (temp->getType() == Token::L_PARENTHESIS) {
				whileStatement = new NodeStatementWhile();

				// EXP
				whileStatement->addChild(this->exp());

				// )
				temp = this->readNextToken();
				if (temp->getType() == Token::R_PARENTHESIS) {
					//STATEMENT
					whileStatement->addChild(this->statement());
				}
				else {
					delete whileStatement;
					errorOutput("')' expected", temp->getRow(), temp->getColumn());
				}

				newNode = whileStatement;
			}
			else {
				errorOutput("'(' expected", temp->getRow(), temp->getColumn());
			}
			break;

		// Leere Statements sind nicht erlaubt!
		case Token::SEMICOLON:
			errorOutput("Empty Statement is not accepted!", temp->getRow(), temp->getColumn());
			break;

		// Statement in einem Declarations-Block
		case Token::INT:
			errorOutput("Statement expected", temp->getRow(), temp->getColumn());
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
	NodeExp2Exp* expression;
	NodeExp2IdentifierIndex* indexNode;
	NodeExp2Integer* integerNode;
	NodeExp2NegativeExp* negativeExpNode;
	NodeExp2NotExp* notExpNode;

	Token *temp = this->readNextToken();

	switch (temp->getType()) {
		// (EXP)
		case Token::L_PARENTHESIS:
			// EXP
			expression = new NodeExp2Exp();
			expression->addChild(this->exp());

			// )
			temp = this->readNextToken();
			if (temp->getType() != Token::R_PARENTHESIS) {
				errorOutput("')' expected", temp->getRow(), temp->getColumn());
			}
			return expression;

		// IDENTIFIER INDEX
		case Token::IDENTIFIER:
			indexNode = new NodeExp2IdentifierIndex();
			indexNode->addChild(new NodeIdentifier(temp->getRow(), temp->getColumn(), temp->getLexem(), temp->getSymboltableEntry()));

			// INDEX
			indexNode->addChild(this->index());
			return indexNode;

		// INTEGER
		case Token::INTEGER:
			integerNode = new NodeExp2Integer();
			integerNode->addChild(new NodeInteger(temp->getNumber(), temp->getRow(), temp->getColumn()));
			return integerNode;

		// - EXP
		case Token::MINUS:
			// EXP
			negativeExpNode = new NodeExp2NegativeExp();
			negativeExpNode->addChild(this->exp());
			return negativeExpNode;

		// ! EXP
		case Token::EXCLAMATIONMARK:
			// EXP2
			notExpNode = new NodeExp2NotExp();
			notExpNode->addChild(this->exp2());
			return notExpNode;

		default:
			errorOutput("Illegal expression.", temp->getRow(), temp->getColumn());
	}

	return 0;
}

NodeIndex* Parser::index() {
	// [EXP]
	// [
	NodeIndex *index;
	Token *temp = this->readNextToken();

	if (temp->getType() == Token::L_SQUAREBRACE) {
		// EXP
		index = new NodeIndex();
		index->addChild(this->exp());

		// ]
		temp = this->readNextToken();
		if (temp->getType() == Token::R_SQUAREBRACE) {
			return index;
		}
		else {
			delete index;
			errorOutput("']' expected", temp->getRow(), temp->getColumn());
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
		case Token::MINUS:
			opNodeType = Node::TYPE_OP_MINUS;
		break;

		// *
		case Token::ASTERISK:
			opNodeType = Node::TYPE_OP_MULTIPLY;
		break;

		// /
		case Token::SLASH:
			opNodeType = Node::TYPE_OP_DIVIDE;
		break;

		// <
		case Token::L_BRACKET:
			opNodeType = Node::TYPE_OP_SMALLER;
		break;

		// >
		case Token::R_BRACKET:
			opNodeType = Node::TYPE_OP_GREATER;
		break;

		// =
		case Token::EQUALS:
			opNodeType = Node::TYPE_OP_EQUAL;
		break;

		// <!>
		case Token::UNEQUAL:
			opNodeType = Node::TYPE_OP_UNEQUAL;
		break;

		// &
		case Token::AMPERSAND:
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
