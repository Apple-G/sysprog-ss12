#pragma once
#include "Pair.h"
#include "ListElement.h"
using namespace std;


template <class type>
class Hashtable {
public:
	ListenElement<type>* table;	 				// Array mit Listen
	int size;									// Laenge des Arrays

	//--- Hashwert ermitteln ---
	int hashcode(char* key){	
		int ergebnis = 0;
		for (int i = 0; i <getCharLength(key); i++)
		{
			ergebnis += key[i];
		}
		return ergebnis;
	}	


	//--- Konstruktor ---
	Hashtable(int nsize){
		size = nsize;
		table = new ListenElement<type>[size];
	}

	//--- Destruktor -- 
	~Hashtable(){
		delete []table;
	}

	//--- Wert einfügen ---
	bool put(char* key, type value){
		int hashKey = hashcode(key) % size;
		if (contains(key)){
			if (compare(table[hashKey].front().key, key)){
				table[hashKey].front().value = value;
			}
			else{
				//cout<<"ERROR!!!";
			}
			return true;
		}
		else{
			Pair<type> newPair(key, value);
			table[hashKey].push_front(newPair);
			return false;
		}
	}

	//--- Wert zum Schluessel auslesen ---
	type get(char* key){
		type temp;
		int hashKey = hashcode(key) % size;
		if (contains(key)){
			return table[hashKey].front().value;
		}

	//	std::cout<<"ERROR! Key nicht gefunden";
		return temp;
	}

	//--- Ist der Schluessel vorhanden? ---
	bool contains(char* key){
		bool rueckgabe= false;
		int hashKey = hashcode(key) % size;
		for (int i=0; i<table[hashKey].size(); i++){
			if (compare(key, table[hashKey].front().key))
			{
				rueckgabe = true;
				i =  table[hashKey].size();
			}else {			
				table[hashKey].push_back( table[hashKey].front());
				table[hashKey].pop_front();
			}
		}
		return rueckgabe;
	}	

	bool compare(char* word1, char* word2){
		bool rueckgabe = true;
		int length = getCharLength(word1);
		if (getCharLength(word2) != length){
			rueckgabe = false;
		}
		else{
			for (int i=0; i<length; i++){
				if(word1[i] != word2[i]){
					rueckgabe = false;
					i = length;
				}
			}
		}
		return rueckgabe;
		
	}
};