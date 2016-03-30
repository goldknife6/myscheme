#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>


#include "env.h"
#include "excpetion.h"


class Object {
	bool makred;
public:
	Object():makred(false) {
	}
	virtual std::string toString() =0;
};

class NumberObject : public Object {
	int value;	
public:
	NumberObject(int v): value(v) {
	}
	virtual std::string toString() override {
	}

};
/*
class Id : public Object {
	std::string value;	
public:
	NumberObject(int v = 0): value(v) {
	}
};*/

class BooleanObject : public Object {
	bool value;	
public:
	BooleanObject(bool v): value(v) {
	}
	virtual std::string toString() override {
	}
};


class StringObject : public Object {
	std::string value;	
public:
	StringObject(std::string v): value(v) {
	}

	virtual std::string toString() override {
	}
};


class FunctionObject : public Object {
public:

};

class PrimFunction : public FunctionObject {
public:
	

};

class NormalFunction : public FunctionObject {
	std::string name;
public:
	

};
#endif/*_OBJECT_SCHEMER*/
