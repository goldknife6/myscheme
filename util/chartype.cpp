#include <cctype>

bool isSpecialInital(char c)
{
	switch (c) {
	case '!':
	case '$':
	case '&':
	case '*':
	case '/':
	case ':':
	case '<':
	case '=':
	case '>':
	case '?':
	case '^':
	case '_':
		return true;	
	default:
		return false;	
	}
}

bool isInital(char c)
{
	return isalpha(c) || isSpecialInital(c);
}

bool isDigit(char c)
{
	return isdigit(c);
}

bool isSubsequent(char c)
{
	return isInital(c) || isDigit(c);
}
