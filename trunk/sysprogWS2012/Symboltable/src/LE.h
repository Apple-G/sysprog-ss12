#ifndef LE_H_
#define LE_H_

template <class T>
class LE
{
	T data;
	//Pointer auf nächstes Element
	LE* next;
	//Pointer auf vorheriges Element
	LE* prev;

public:
	/**
	* Initialisierung eines einzelnen Listenelements
	*
	* @param data Datenelement der Liste
	* @param next Pointer auf das Nachfolgerelement
	* @param prev Pointer auf das Vorgängerelement
	*/
	LE(T data, LE* next, LE* prev)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}

	/**
	* Getter für das vorherige Element der Liste
	*
	* @return vorheriges Element der Liste
	*/
	LE* getPrev()
	{
		return this->prev;
	}

	/**
	* Getter für das nächste Element der Liste
	*
	* @return nächstes Element der Liste
	*/
	LE* getNext()
	{
		return this->next;
	}

	/**
	* Setter für das nächste Element der Liste
	*
	* @param next Listenelement
	*/
	void setNext(LE* next)
	{
		this->next = next;
	}

	/**
	* Setter für das vorherige Element der Liste
	*
	* @param prev Listenelement
	*/
	void setPrev(LE* prev)
	{
		this->prev = prev;
	}

	/**
	* Getter für Daten des Listenelements
	*
	* @return Zeiger auf Daten des Listenelements
	*/
	T getData()
	{
		return this->data;
	}

	/**
	* Setter für Daten des Listenelements
	*
	* @param data des Listenelements
	*/
	void setData(T data)
	{
		this->data = data;
	}
};

#endif /* LE_H_ */
