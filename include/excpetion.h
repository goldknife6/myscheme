#ifndef _EXCEPTION_SCHEMER
#define _EXCEPTION_SCHEMER

#include <string>
#include <iostream>

class SchemeException : public std::runtime_error {
public:
	SchemeException(const std::string &s)
	: std::runtime_error(s) {
	}
	virtual void printMsg() {
		std::cout<<what()<<std::endl;
	}
};

class UnboundException : public SchemeException {
public:
	UnboundException(const std::string &s)
	: SchemeException("\n;Unbound variable: " + s + "\n") {
	}

};

class NotAppException : public SchemeException {
public:
	NotAppException(const std::string &s)
	: SchemeException("\nThe object "+ s + " is not applicable.\n") {
	}

};

class SchemeError : public std::logic_error {
public:
	SchemeError(const std::string &s)
	: std::logic_error(s) {
	}
};
#endif/*_EXCEPTION_SCHEMER*/
