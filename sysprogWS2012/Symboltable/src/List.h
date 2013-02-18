/**
 * Verkettete Liste, welche sowohl Ihren Vorgänger als auch Ihren
 * Nachfolger kennt.
 */
#ifndef __LIST__
#define __LIST__

#include "LE.h"
//#include <assert.h>

template<class T>
class List {
	LE<T>* firstLE;
	LE<T>* lastLE;

	unsigned int size;

public:
	/**
	 * Eine neue, leere List erzeugen.
	 * Die Liste ist leer, wenn first
	 * auf kein Element (0) verweist.
	 */
	List() {
		this->firstLE = 0;
		this->lastLE = 0;
		this->size = 0;
	}

	/**
	 * Die Liste fordert in pushBack selbst Speicher
	 * an, der hier vor dem Loeschen eines Listenobjektes
	 * wieder frei gegeben wird.
	 */
	~List() {
		clear();
	}

	/**
	 * Liste leeren.
	 */
	void clear() {
		while (firstLE != 0) {
			removeFirst();
		}
	}

	/**
	 * Das erste Listenelement loeschen.
	 */
	void removeFirst() {

		// Nur wenn die Liste nicht leer ist, wird
		// geloescht...
		if (firstLE != 0) {
			// Nachfolger des zu ersten Elementes merkern.
			LE<T>* nextFirstLE = firstLE->getNext();

			// Erstes Element löschen
			delete firstLE;

			// Gemerkter Nachfolger wird erstes Element
			firstLE = nextFirstLE;

			// Wenn die Liste aus nur einem Element bestand,
			// dann ist sie jetzt leer.
			if (firstLE == 0) {
				lastLE = 0;
			}

			// Laenge anpassen.
			size--;
		}
	}

	/**
	 * Ein neues Element an das Ende der Liste
	 * anhaengen.
	 */
	void pushBack(T value) {
		// Ein neues Listenelemente für den Wert erzeugen.
		// Das neue Element hat keinen Nachfolger.
		LE<T>* newLE = new LE<T>(value, 0, lastLE);

		// Wenn die Liste leer ist, wird das neue
		// Listenelement das erste der Liste.
		if (firstLE == 0) {
			firstLE = newLE;
		}

		// Sonst wird das neue Element hinter das
		// bisher letzte Element gehaengt.
		else {
			lastLE->setNext(newLE);
		}

		// Das neue Listenelement ist das letzte der
		// der Liste.
		lastLE = newLE;

		// Laenge erhoehen.
		size++;
	}

	/**
	 * Ein neues Element an den Anfang der Liste
	 * einfuegen.
	 */
	void pushFront(T value) {
		// Ein neues Listenelemente für den Wert erzeugen.
		// Das neue Element hat das bisherige erste Element
		// als Nachfolger.
		LE<T>* newLE = new LE<T>(value, firstLE);

		// Wenn die Liste leer ist, wird das neue
		// Listenelement das letzte der Liste.
		if (lastLE == 0) {
			lastLE = newLE;
		}

		// Das neue Listenelement ist das letzte der
		// der Liste.
		firstLE = newLE;

		// Laenge erhoehen.
		size++;
	}

	T getElementAt(int index) const {

		//Fehlerbehandlung, wenn index nicht existiert!
		/*	if (index < getSize())
		 {
		 return 0;
		 }*/
		//	assert(index < getSize());
		LE<T>* actualElement = firstLE;
		LE<T>* nextElement;

		for (int i = 0; i < index; i++) {
			nextElement = actualElement->getNext();
			actualElement = nextElement;
		}
		return actualElement->getData();
	}

	/**
	 * Erstes Element der Liste auslesen.
	 */
	LE<T>* front() const {
		if (firstLE != 0) {
			return firstLE;
		}
	}

	/**
	 * Letztes Element der Liste auslesen. Das
	 * Element wird per Kopie zurueckgegeben.
	 */
	T last() const {
		if (lastLE != 0) {
			return lastLE->data;
		}
	}

	/**
	 * Laenge ermitteln.
	 */
	int getSize() const {
		return size;
	}
};

#endif // __LIST__
