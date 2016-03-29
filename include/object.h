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
		//std::cout<<toString()<<" created"<<std::endl;
	}

	int getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		std::ostringstream os;
		os<<value;
		return "Number object: "+os.str();
	}
	virtual ~Number() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
	}
};

class Id : public Object {

	std::string value;	
public:

	Id(std::string s): value(s) {
	}

	std::string getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		return "Id object: "+value+"";
	}
	virtual ~Id() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
	}
};

class Bool : public Object {

	bool value;	
public:

	Bool(bool v): value(v) {
	}

	bool getValue() {
		return value;
	}
	
	virtual std::string toString() override {
		if(value)
			return "Bool object: true";
		return "Bool object: false";
	}
	virtual ~Bool() {
		//std::cout<<toString()<<"destoryed"<<std::endl;
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
		return "String object: \""+value+"\"";
	}
	virtual ~String() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
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
	PrimFunction(DefFormals *def,std::shared_ptr<Environment> env)
	:Function(def,nullptr,env) {
	}

	DefFormals* parameters() {
		throw *new SchemeError("PrimFunction call parameters()\n");
	}

	Body* body() {
		throw *new SchemeError("PrimFunction call body()\n");
	}

	std::shared_ptr<Environment> makeEnv() {
		return std::shared_ptr<Environment>(new Environment(env));
	}

	virtual std::string toString() override {
		return "PrimFunction object";
	}
	virtual ~PrimFunction() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
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
		return "NormalFunction object";
	}
	virtual ~NormalFunction() {
		//std::cout<<toString()<<" destoryed"<<std::endl;
	}
};
#endif/*_OBJECT_SCHEMER*/
