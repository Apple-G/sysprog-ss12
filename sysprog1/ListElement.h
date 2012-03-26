#pragma once

template <class type>
class ListenElement{
private:
	typedef Pair<type> hashType;
	hashType *table;
	int arraySize, anzahlElemente;

public:
	//--- Konstruktor ---
	ListenElement(){
		arraySize = 2;
		anzahlElemente = 0;
		table = new hashType[arraySize];
	}

	//--- Destruktor --
	~ListenElement(){
		delete []table;
	}
	
	//---- Größe der Liste ---
	int size(){
		return anzahlElemente;
	}

	//--- Ein neues Element am Anfang anfügen ---
	void push_front(hashType value){
		if (anzahlElemente >= arraySize)
		{
			rearraySize(arraySize*2);
		}
		for (int i=anzahlElemente; i>0; i--){
			
			table[i] = table[i-1];
		}
			table[0] = value;
			anzahlElemente++;
	}

	//--- Ein neues Element am Ende anfügen ---
	void push_back(hashType value){
		if (anzahlElemente >= arraySize)
		{
			rearraySize(arraySize*2);
		}
		table[anzahlElemente] = value;
		anzahlElemente++;
	}

	//--- Das erste Element auslesen ---
	hashType& front(){
		if (!empty()){
			return table[0];
		}else { // Wenn keine Elemente vorhanden sind...scheiß Lösung!!....
			hashType temp;
			return temp;
		}
	}

	//--- Das letzte Element auslesen ---
	hashType& last(){
		if (!empty()){
			return table[anzahlElemente-1];
		}else { // Wenn keine Elemente vorhanden sind...scheiß Lösung!!....
			hashType temp;
			return temp;
		}
	}

	//--- Das erste Element auslesen ---
	void pop_front(){
		if (!empty()){
			for (int i=0; i<anzahlElemente-1; i++){
				table[i] = table[i+1];
			}
			anzahlElemente--;
			if (anzahlElemente < arraySize/2 && arraySize>2){
				rearraySize(arraySize/2);
			}
		}
	}

	//--- Das letzte Element auslesen ---
	void pop_back(){
		table[anzahlElemente-1] = null;
		anzahlElemente--;
		if (anzahlElemente < arraySize/2 && arraySize>2){
			rearraySize(arraySize/2);
		}
	}

	//--- Test, ob eine Liste leer ist ---
	bool empty(){
		if (anzahlElemente == 0){
			return true;
		}else{
			return false;
		}
	}


private:
	//--- ändert die Größe des Arrays ---
	void rearraySize (int nSize){
		hashType* temp;
		
		temp = new hashType[anzahlElemente+1];
		for (int i=0; i<anzahlElemente; i++){
			temp[i] = table[i];
		}
		//delete[] table;

		arraySize= nSize;
		table= new hashType[arraySize];
		for (int i=0; i<anzahlElemente; i++){
			table[i] = temp[i];
		}
		delete[] temp;

	}
};
