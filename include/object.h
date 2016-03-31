#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>
#include <map>

#include "excpetion.h"


class Object {
	bool marked = false;
public:
	virtual std::string toString() =0;
	bool getMarked() {
		return 	marked;
	}
	void setMarked() {
		marked = true;
	}
	void cleanMarked() {
		marked = false;
	}
};

class Environment : public Object {
	std::map<std::string,Object*> value;
	Environment* outerEnv;
public:
	Environment(Environment *env)
	:outerEnv(env) {
	}

	Object* get(std::string name) {
	}

	auto getIterBegin()->decltype(value.begin()) {
		return value.begin();
	}

	auto getIterEnd()->decltype(value.end()) {
		return value.end();
	}

	void put(std::string name,Object* obj) {
	}

	Environment *makeEnv() {
		return new Environment(outerEnv);
	}

	Environment *outer() {
		return outerEnv;
	}

	virtual std::string toString() override {
		throw *new SchemeError("Environment toString");
	}
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
	virtual Environment* getEnv()=0;
};

class PrimFunction : public FunctionObject {
public:
	

};

class NormalFunction : public FunctionObject {
	std::string name;
public:
	

};
#endif/*_OBJECT_SCHEMER*/
