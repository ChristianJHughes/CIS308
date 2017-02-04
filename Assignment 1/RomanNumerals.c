//Author: Christian Hughes
//CIS 308: Tuesday 2:30-4:20
//This program converts Roman Numerals into regular integers.

#include <stdio.h>
#include <string.h>

//Declare Functions.
int convert(char *s);
int romanNumeralValue(char *s);


int main()
{
	int val;
	char s[100];
	printf("Enter Roman Numerals (All Caps): ");
	fgets(s, 100, stdin);
	int len = strlen(s);
	s[len - 1] = '\0';
	val = convert(s);
	printf("%d\n", val);
}

int romanNumeralValue(char *s)
{
	int val;

	switch(*s)
	{
	case 'I':
		val = 1;
		break;
	case 'V':
		val = 5;
		break;
	case 'X':
		val = 10;
		break;
	case 'L':
		val = 50;
		break;
	case 'C':
		val = 100;
		break;
	case 'D':
		val = 500;
		break;
	case 'M':
		val = 1000;
		break;
	default:
		val = -1;
		break;
	}

	return val;
}

int convert(char *s)
{
	int len;
	len = strlen(s);

	int val;
        int remainder;

	if (len == 0)
	{
		return 0;
	}

        val = romanNumeralValue(s);
	if (len == 1)
	{
		return val;
	}
	else
	{
        remainder = convert(&(s[1]));
		if (romanNumeralValue(&(s[1])) > val)
		{
			val = remainder - val;

		}
		else
		{
			val += remainder;
		}
	}
	return val;
}
