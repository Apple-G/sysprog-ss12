/*
 * CharHelper.cpp
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */
#include <stdio.h>
#include "CharHelper.h"

char* CharHelper::convertInt(int number) {
	char* temp;
	temp = new char[256];

	if(number < 10 && number >= 0)
	{
		sprintf(temp, " %d", number);
	}
	else
	{
		sprintf(temp, "%d", number);
	}
	return temp;
}

char* CharHelper::convertLong(long number) {
	char* temp;
	temp = new char[256];

	if(number < 10 && number >= 0)
	{
		sprintf(temp, " %d", number);
	}
	else
	{
		sprintf(temp, "%d", number);
	}
	return temp;
}

int CharHelper::getLenght(char* string)
{
	int count = 0;
	char* temp = string;
	while (*temp != 0)
	{
		count++;
		temp++;
	}
	return count;
}
