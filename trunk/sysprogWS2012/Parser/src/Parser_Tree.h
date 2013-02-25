#ifndef ParserTree_H_
#define ParserTree_H_
#include "NodeProg.h"
#include "Buffer.h"

class Tree {
	/** Zeiger auf den ersten Knoten des Baums. */
	NodeProg *root;

public:
	/** Erzeugt einen neuen Baum. */
	Tree(void);

	/** Loescht den Baum und gibt beanspruchten Heap-Speicher wieder frei. */
	~Tree(void);

	/** .
	@param node Ausgangsknoten des Baums, entspricht Programmeinstiegspunkt.
	*/
	void setRoot(NodeProg *node);

	/** .
	@param
	@return
	*/
	NodeProg *getRoot();

	/** Gibt den Baum rekursiv in verstaendlicher Sprache aus. */
	void dump();

	/** Fuehrt fuer den erzeugten Baum eine Typpruefung durch.
	@param output Zeiger auf den zu verwendenden Ausgabepuffer.
	@return Gibt zurueck, ob die Typpruefung erfolgreich war.
	*/
	bool typeCheck(Buffer *output);

	/** Erzeugt Code aus der Baumstruktur.
	@param output Zeiger auf das zu verwendende Ausgabe-Interface.
	*/
	void makeCode(Buffer *output);
};

#endif


