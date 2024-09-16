#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	int i, len = strlen(str);
	char tmp;

	for (i = 0; i < len / 2; i++) 
	{
	tmp = str[i];
	str[i] = str[len - i - 1];
	str[len - i - 1] = tmp;
	}
}

