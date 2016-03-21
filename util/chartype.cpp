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

bool isWhiteSpace(char c)
{
	switch (c) {
	case ' ':
	case '\n':
	case '\t':
		return true;	
	default:
		return false;	
	}
}

bool isDelimiter(char c)
{
	if (isWhiteSpace(c))
		return true;

	switch (c) {
	case '(':
	case ')':
	case ';':
	case '"':
		return true;	
	default:
		return false;	
	}
}


bool isPeculiarIdentifer(char c)
{
	return c == '+' || c == '-';
}
bool isSign(char c)
{
	return isPeculiarIdentifer(c);
}


bool isBoolean(char c)
{
	return c == 'f' || c == 't';
}


bool isSpecialSubsequent(char c)
{
	switch (c) {
	case '+':
	case '-':
	case '.':
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
	return isInital(c) || isDigit(c) ||
		isSpecialSubsequent(c);
}
