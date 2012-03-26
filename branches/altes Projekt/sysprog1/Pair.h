#pragma once
template <class type>
class Pair {
public:
	char*    key;
	type      value;
	Pair(){
	};
	Pair(char* key, type value){
		this->key = key;
		this->value = value;
	}
};
