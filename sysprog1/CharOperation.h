#pragma once
static int getCharLength(char* word){
	int length = 0;
		while (word[length] != '\0'){
			length++;
		}
		return length;
}	

static char* copyChar(char* word){
	char* temp = new char[getCharLength(word)];
	for (int i = 0; i<getCharLength(word); i++){
		temp[i] = word[i];
	}
	temp[getCharLength(word)]='\0';
	return temp;
}