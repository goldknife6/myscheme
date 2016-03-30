#ifndef _EXCEPTION_SCHEMER
#define _EXCEPTION_SCHEMER

#include <string>
#include <iostream>

class SchemeException : public std::runtime_error {
public:
	SchemeException(const std::string &s = "")
	: std::runtime_error(s) {
	}

	virtual void printMsg() {
		std::cout<<what()<<std::endl;
	}
};


class UnboundException : public SchemeException {
public:
	UnboundException(const std::string &s = "")
	: SchemeException("\n;Unbound variable: " + s + "\n") {
	}

};

class ArugNotMutchException : public SchemeException {
public:
	ArugNotMutchException(const std::string &s = "")
	: SchemeException("\n;ArugNotMutch: " + s) {
	}

};

class IllFormedException : public SchemeException {
public:
	IllFormedException(const std::string &s = "")
	: SchemeException("\n;Ill-formed special form: " + s + "\n") {
	}

};

class IllegalCharException : public SchemeException {
public:
	IllegalCharException(const std::string &s = "")
	: SchemeException("\n;Illegal character: " + s + "\n") {
	}

};

class OutOfMemException : public SchemeException {
public:
	OutOfMemException(const std::string &s = "")
	: SchemeException("\n;OutOfMemException: " + s + "\n") {
	}

};


class NotAppException : public SchemeException {
public:
	NotAppException(const std::string &s = "")
	: SchemeException("\nThe object "+ s + " is not applicable.\n") {
	}

};

class UnbalancedException : public SchemeException {
public:
	UnbalancedException(const std::string &s = "")
	: SchemeException("\nUnbalanced close parenthesis.\n") {
	}

};

class EOFException : public SchemeException {
public:
	EOFException(const std::string &s = "")
	: SchemeException("\nend of file.\n") {
	}

};

class SchemeError : public std::logic_error {
public:
	SchemeError(const std::string &s ="")
	: std::logic_error(s) {
	}
	virtual void printMsg() {
		std::cout<< "SchemeError "<<what()<<std::endl;
	}
};

class OutOfRangeException : public SchemeError {
public:
	OutOfRangeException(const std::string &s ="")
	: SchemeError(s) {
	}
	virtual void printMsg() {
		std::cout<< "OutOfRangeException "<<what()<<std::endl;
	}
};


class InvalidArgException : public SchemeError {
public:
	InvalidArgException(const std::string &s ="")
	: SchemeError(s) {
	}
	virtual void printMsg() {
		std::cout<< "InvalidArgException "<<what()<<std::endl;
	}
};
#endif/*_EXCEPTION_SCHEMER*/
