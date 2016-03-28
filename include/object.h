#ifndef _OBJECT_SCHEMER
#define _OBJECT_SCHEMER

#include <string>
#include <iostream>
#include <sstream>
#include <ast/defformals.h>
#include <ast/body.h>
#include <env.h>
#include <excpetion.h>

class Object {
public:
	virtual std::string toString() =0;
};

class Number : public Object {

	int value;	
public:

	Number(int v = 0): value(v) {
	}

	int getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		std::ostringstream os;
		os<<value;
		return os.str();
	}
};


class Bool : public Object {

	bool value;	
public:

	Bool(bool v = false): value(v) {
	}

	bool getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		return "Bool object\n";
	}
};


class String : public Object {

	std::string value;	

public:

	String(std::string v ): value(v) {
	}

	std::string getValue() {
		return value;
	}

	virtual std::string toString() override {
		return "String object\n";
	}
};


class Function : public Object {
public:
	DefFormals *def;
	Body *b;
	std::shared_ptr<Environment> env;

	Function(DefFormals *d,Body *body,std::shared_ptr<Environment> e)
	:def(d),b(body),env(e) {

	}

	virtual DefFormals* parameters() =0;
	virtual Body* body() =0;
	virtual std::shared_ptr<Environment> makeEnv() =0;
};

class PrimFunction : public Function {
public:
	PrimFunction(DefFormals *d,Body *body,std::shared_ptr<Environment> e)
	:Function(d,body,e) {
	}

	DefFormals* parameters() {
		return def;
	}

	Body* body() {
		throw *new SchemeError("PrimFunction call body()\n");
	}

	std::shared_ptr<Environment> makeEnv() {
		return std::shared_ptr<Environment>(new Environment(env));
	}

	virtual std::string toString() override {
		return "PrimFunction object\n";
	}

};

class NormalFunction : public Function {
public:
	NormalFunction(DefFormals *d,Body *body,std::shared_ptr<Environment> e)
	:Function(d,body,e) {
	}

	DefFormals* parameters() {
		return def;
	}

	Body* body() {
		return b;
	}

	std::shared_ptr<Environment> makeEnv() {
		return std::shared_ptr<Environment>(new Environment(env));
	}

	virtual std::string toString() override {
		return "NormalFunction object\n";
	}

};
#endif/*_OBJECT_SCHEMER*/
